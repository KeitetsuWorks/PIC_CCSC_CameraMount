/**
 * @file        ccsc_uart.c
 * @brief       UART処理，リングバッファ
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "ccsc_uart.h"


/**
 * @name    送信リングバッファ
 */
/*! @{ */
uint8_t uart_tx_buffer[UART_TX_BUFFER_SIZE];    /*!< 送信リングバッファ */
uint8_t uart_tx_buffer_read_index;              /*!< 読込みインデックス */
uint8_t uart_tx_buffer_write_index;             /*!< 書込みインデックス */
uint8_t uart_tx_buffer_count;                   /*!< 格納データ数 */
/*! @} */


/**
 * @name    受信リングバッファ
 */
uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];   /*!< 受信リングバッファ */
uint8_t uart_rx_buffer_read_index;             /*!< 読込みインデックス */
uint8_t uart_rx_buffer_write_index;            /*!< 書込みインデックス */
uint8_t uart_rx_buffer_count;                  /*!< 格納データ数 */
/*! @} */


void uart_tx_initBuffer(void)
{
    uart_tx_buffer_read_index = 0;
    uart_tx_buffer_write_index = 0;
    uart_tx_buffer_count = 0;
    
    return;
}


void uart_tx_enable(void)
{
    enable_interrupts(INT_TBE);
    
    return;
}


void uart_tx_disable(void)
{
    disable_interrupts(INT_TBE);
    
    return;
}


#inline
bool uart_tx_hasTransmitData(void)
{
    bool uart_tx_buffer_status;
    
    if (uart_tx_buffer_count != 0) {
        uart_tx_buffer_status = TRUE;
    }
    else {
        uart_tx_buffer_status = FALSE;
    }
    
    return uart_tx_buffer_status;
}


#inline
bool uart_tx_isFull(void)
{
    bool uart_tx_buffer_full;
    
    if (uart_tx_buffer_count >= UART_TX_BUFFER_SIZE) {
        uart_tx_buffer_full = TRUE;
    }
    else {
        uart_tx_buffer_full = FALSE;
    }
    
    return uart_tx_buffer_full;
}


#inline
void uart_tx_addTransmitData(uint8_t uart_tx_data)
{
    // 送信リングバッファが空くまで待機
    while (uart_tx_isFull() == TRUE) {
    }
    
    // 送信待ちデータの追加
    uart_tx_disable();
    uart_tx_buffer[uart_tx_buffer_write_index] = uart_tx_data;
    uart_tx_buffer_write_index = (uart_tx_buffer_write_index + 1) % UART_TX_BUFFER_SIZE;
    uart_tx_buffer_count++;
    uart_tx_enable();
    
    return;
}


#org 0x0800, 0x084F DEFAULT
#int_TBE
void uart_tx_isr_TBE(void)
{
    // 1Byte送信
    putc(uart_tx_buffer[uart_tx_buffer_read_index]);
    uart_tx_buffer_read_index = (uart_tx_buffer_read_index + 1) % UART_TX_BUFFER_SIZE;
    uart_tx_buffer_count--;
    
    if (uart_tx_hasTransmitData() == FALSE) {
        uart_tx_disable();
    }
    
    return;
}
#org DEFAULT


void uart_rx_initBuffer(void)
{
    uart_rx_buffer_read_index = 0;
    uart_rx_buffer_write_index = 0;
    uart_rx_buffer_count = 0;
    
    return;
}


void uart_rx_enable(void)
{
    enable_interrupts(INT_RDA);
    
    return;
}


void uart_rx_disable(void)
{
    disable_interrupts(INT_RDA);
    
    return;
}


bool uart_rx_isReceived(void)
{
    bool uart_rx_buffer_status;
    
    if (uart_rx_buffer_count != 0) {
        uart_rx_buffer_status = TRUE;
    }
    else {
        uart_rx_buffer_status = FALSE;
    }
    
    return uart_rx_buffer_status;
}


bool uart_rx_isFull(void)
{
    bool uart_rx_buffer_full;
    
    if (uart_rx_buffer_count >= UART_RX_BUFFER_SIZE) {
        uart_rx_buffer_full = TRUE;
    }
    else {
        uart_rx_buffer_full = FALSE;
    }
    
    return uart_rx_buffer_full;
}


uint8_t uart_rx_getReceivedData(void)
{
    uint8_t uart_rx_data;
    
    // 受信待ち
    while (uart_rx_isReceived() != TRUE) {
    }
    
    uart_rx_disable();
    uart_rx_data = uart_rx_buffer[uart_rx_buffer_read_index];
    uart_rx_buffer_read_index = (uart_rx_buffer_read_index + 1) % UART_RX_BUFFER_SIZE;
    uart_rx_buffer_count--;
    uart_rx_enable();
    
    return uart_rx_data;
}


#org 0x0850, 0x087F DEFAULT
#int_RDA
void uart_rx_isr_RDA(void)
{
    if (uart_rx_isFull() != TRUE) {
        uart_rx_buffer[uart_rx_buffer_write_index] = getc();
        uart_rx_buffer_write_index = (uart_rx_buffer_write_index + 1) % UART_RX_BUFFER_SIZE;
        uart_rx_buffer_count++;
    }
    
    return;
}
#org DEFAULT
