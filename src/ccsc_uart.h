/**
 * @file        ccsc_uart.h
 * @brief       UART処理，リングバッファ
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CCSC_UART_H__
#define __CCSC_UART_H__


/**
 * @name    リングバッファのサイズ
 */
/*! @{ */
#define UART_TX_BUFFER_SIZE     0x07        /*!< 送信リングバッファのサイズ */
#define UART_RX_BUFFER_SIZE     0x07        /*!< 受信リングバッファのサイズ */
/*! @} */


/**
 * @brief   送信リングバッファを初期化する
 */
void uart_tx_initBuffer(void);


/**
 * @brief   送信割込みを有効化する
 */
void uart_tx_enable(void);


/**
 * @brief   送信割込みを無効化する
 */
void uart_tx_disable(void);


/**
 * @brief   送信待ちデータの有無を確認する
 * @retval          TRUE                送信待ちデータあり
 * @retval          FALSE               送信待ちデータなし
 */
#inline
bool uart_tx_hasTransmitData(void);


/**
 * @brief   送信リングバッファの空き領域の有無を確認する
 * @retval          TRUE                空き領域なし
 * @retval          FALSE               空き領域あり
 */
#inline
bool uart_tx_isFull(void);


/**
 * @brief   送信リングバッファに送信データを追加
 * @param[in]       uart_tx_data        送信データ
 */
#inline
void uart_tx_addTransmitData(uint8_t uart_tx_data);


/**
 * @brief   送信割込み処理
 */
#separate
void uart_tx_isr_TBE(void);


/**
 * @brief   受信リングバッファを初期化する
 */
void uart_rx_initBuffer(void);


/**
 * @brief   受信割込みを有効化する
 */
void uart_rx_enable(void);


/**
 * @brief   受信割込みを無効化する
 */
void uart_rx_disable(void);


/**
 * @brief   受信データ有無の確認
 * @retval          TRUE                受信データあり
 * @retval          FALSE               受信データなし
 */
bool uart_rx_isReceived(void);


/**
 * @brief   受信リングバッファの空き領域の有無を確認する
 * @retval          TRUE                空き領域なし
 * @retval          FALSE               空き領域あり
 */
bool uart_rx_isFull(void);


/**
 * @brief   受信データ取得
 * @return          受信データ
 */
uint8_t uart_rx_getReceivedData(void);


/**
 * @brief   受信割込み処理
 */
#separate
void uart_rx_isr_RDA(void);

#endif  // __CCSC_UART_H__
