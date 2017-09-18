/**
 * @file        CameraMount_CommandIF.c
 * @brief       カメラマウントコントローラ コマンドインタフェース
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

#include "CameraMount_CommandIF.h"
#include "CameraMount_Version.h"
#include "CameraMount_System.h"
#include "CameraMount_FreeRunningTimer.h"
#include "CameraMount_Register.h"
#include "CameraMount_EEPROM.h"


/**
 * @name    コマンド
 */
/*! @{ */
#define COMMAND_LENGTH_MAX              6       /*!< 最大コマンド長 */
#define COMMAND_MASK_OPCODE             0xF0    /*!< コマンドマスク: オペコード */
#define COMMAND_MASK_LENGTH             0x0F    /*!< コマンドマスク: コマンド長 */
#define COMMAND_RESET                   0x0     /*!< オペコード: ソフトウェアリセット */
#define COMMAND_INITIALIZE              0x1     /*!< オペコード: システム初期化 */
#define COMMAND_GET_VERSION             0x2     /*!< オペコード: バージョン情報取得 */
#define COMMAND_READ_REGISTER           0x4     /*!< オペコード: レジスタ読込み */
#define COMMAND_WRITE_REGISTER          0x5     /*!< オペコード: レジスタ書込み */
#define COMMAND_READ_EEPROM             0x6     /*!< オペコード: EEPROM読込み */
#define COMMAND_WRITE_EEPROM            0x7     /*!< オペコード: EEPROM書込み */
/*! @} */


/**
 * @name    レスポンス
 */
/*! @{ */
#define RESPONSE_LENGTH_MAX             6       /*!< 最大レスポンス長 */
/*! @} */


/**
 * @name    コマンド
 */
/*! @{ */
static uint8_t command[COMMAND_LENGTH_MAX];     /*!< コマンド */
static uint8_t command_length;                  /*!< コマンド長 */
static uint8_t command_recieved_bytes;          /*!< コマンド受信長 */
/*! @} */


/**
 * @name    レスポンス
 */
/*! @{ */
static uint8_t response[RESPONSE_LENGTH_MAX];   /*!< レスポンス */
static uint8_t response_length;                 /*!< レスポンス長 */
/*! @} */


/**
 * @name    通信タイムアウト検出用タイマ 
 */
/*! @{ */
static struct timer_1s_st com_timeout_timer;    /*!< 通信タイムアウト検出用タイマ */
static uint8_t com_timeout_limit;               /*!< 通信タイムアウト検出時間，1秒単位 */
/*! @} */


/**
 * @brief   コマンド制御を初期化する
 */
#inline
static void CommandIF_initCommandCtrl(void);


/**
 * @brief   コマンドを取得する
 * @retval          TRUE                受信完了し，取得成功
 * @retval          FALSE               受信待機中または受信中のため，取得失敗
 */
#inline
static bool CommandIF_fetchCommand(void);


/**
 * @brief   コマンドのオペコードを取得する
 * @return          オペコード
 */
#inline
static uint8_t CommandIF_getCommandOpcode(void);


/**
 * @brief   コマンドのコマンド長を取得する
 * @return          コマンド長
 */
#inline
static uint8_t CommandIF_getCommandLength(void);


/**
 * @brief   コマンドを実行する
 */
#inline
static void CommandIF_execCommand(void);


/**
 * @brief   レスポンス制御を初期化する
 */
#inline
static void CommandIF_initResponseCtrl(void);


/**
 * @brief   レスポンスを送信する
 */
static void CommandIF_sendResponse(void);


#inline
static void CommandIF_initCommandCtrl(void)
{
    command_length = 1;
    command_recieved_bytes = 0;
    
    return;
}


#inline
static bool CommandIF_fetchCommand(void)
{
    bool result;
    
    while ((uart_rx_isReceived() == TRUE) && (command_recieved_bytes < command_length)) {
        command[command_recieved_bytes] = uart_rx_getReceivedData();
        command_recieved_bytes++;
        
        if (command_recieved_bytes == 1) {
            command_length = CommandIF_getCommandLength();
        }
    }
    
    if (command_recieved_bytes == command_length) {
        result = TRUE;
    }
    else {
        result = FALSE;
    }
    
    return result;
}


#inline
static uint8_t CommandIF_getCommandOpcode(void)
{
    return ((command[0] & COMMAND_MASK_OPCODE) >> 4);
}


#inline
static uint8_t CommandIF_getCommandLength(void)
{
    return (command[0] & COMMAND_MASK_LENGTH);
}


#inline
static void CommandIF_execCommand(void)
{
    CommandIF_initResponseCtrl();
    
    switch (CommandIF_getCommandOpcode()) {
        case COMMAND_RESET:
            reset_cpu();
            break;
        case COMMAND_INITIALIZE:
            System_setInitializationRequest();
            break;
        case COMMAND_GET_VERSION:
            response[1] = CAMERAMOUNT_VERSION;
            response[2] = CAMERAMOUNT_REVISION;
            response[0] = System_getError();
            response_length = 3;
            CommandIF_sendResponse();
            break;
        case COMMAND_READ_REGISTER:
            response[1] = Register_read(command[1], &(response[2]));
            if ((response[1] + 2) > RESPONSE_LENGTH_MAX) {
                System_setError(SYSTEM_ERROR_INVALID_COMMAND);
                
                response[0] = System_getError();
                response_length = 2;
                CommandIF_sendResponse();
            }
            else {
                response[0] = System_getError();
                response_length = response[1] + 2;
                CommandIF_sendResponse();
            }
            break;
        case COMMAND_WRITE_REGISTER:
            if (Register_getSize(command[1]) != (CommandIF_getCommandLength() - 2)) {
                System_setError(SYSTEM_ERROR_INVALID_COMMAND);
                
                response[0] = System_getError();
                response_length = 1;
                CommandIF_sendResponse();
            }
            else {
                response[1] = Register_write(command[1], &(command[2]));
                response[0] = System_getError();
                response_length = 2;
                CommandIF_sendResponse();
            }
            break;
        case COMMAND_READ_EEPROM:
            response[1] = EEPROM_read(command[1], &(response[2]));
            if ((response[1] + 2) > RESPONSE_LENGTH_MAX) {
                System_setError(SYSTEM_ERROR_INVALID_COMMAND);
                
                response[0] = System_getError();
                response_length = 2;
                CommandIF_sendResponse();
            }
            else {
                response[0] = System_getError();
                response_length = response[1] + 2;
                CommandIF_sendResponse();
            }
            break;
        case COMMAND_WRITE_EEPROM:
            if (EEPROM_getSize(command[1]) != (CommandIF_getCommandLength() - 2)) {
                System_setError(SYSTEM_ERROR_INVALID_COMMAND);
                
                response[0] = System_getError();
                response_length = 1;
                CommandIF_sendResponse();
            }
            else {
                response[1] = EEPROM_write(command[1], &(command[2]));
                response[0] = System_getError();
                response_length = 2;
                CommandIF_sendResponse();
            }
            break;
        default:
            System_setError(SYSTEM_ERROR_INVALID_COMMAND);
            
            response[0] = System_getError();
            response_length = 1;
            CommandIF_sendResponse();
            break;
    }
    
    return;
}


#inline
static void CommandIF_initResponseCtrl(void)
{
    response_length = 0;
    
    return;
}


static void CommandIF_sendResponse(void)
{
    uint8_t response_send_bytes;
    
    response_send_bytes = 0;
    while (response_send_bytes < response_length) {
        uart_tx_addTransmitData(response[response_send_bytes]);
        response_send_bytes++;
    }
    
    return;
}


void CommandIF_init(void)
{
    CommandIF_initCommandCtrl();
    CommandIF_initResponseCtrl();
    
    uart_tx_initBuffer();
    uart_rx_initBuffer();
    uart_rx_enable();
    
    EEPROM_read(EEPROM_COM_TIMEOUT_LIMIT, &com_timeout_limit);
    FreeRunningTimer_1s_isTimeout(&com_timeout_timer, FALSE, com_timeout_limit);
    
    return;
}


void CommandIF_execTask(void)
{
    bool retval;
    
    retval = CommandIF_fetchCommand();
    if (retval == TRUE) {
        CommandIF_execCommand();
        
        CommandIF_initCommandCtrl();
        
        FreeRunningTimer_1s_isTimeout(&com_timeout_timer, FALSE, com_timeout_limit);
    }
    
    retval = FreeRunningTimer_1s_isTimeout(&com_timeout_timer, TRUE, com_timeout_limit);
    if (retval == TRUE) {
        FreeRunningTimer_1s_isTimeout(&com_timeout_timer, FALSE, com_timeout_limit);
        
        System_setStatus(SYSTEM_STATUS_COM_TIMEOUT);
        
        CommandIF_initCommandCtrl();
        CommandIF_initResponseCtrl();
        
        uart_tx_initBuffer();
        uart_rx_initBuffer();
        
        FreeRunningTimer_1s_isTimeout(&com_timeout_timer, TRUE, com_timeout_limit);
    }
    
    return;
}
