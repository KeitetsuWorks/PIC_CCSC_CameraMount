/**
 * @file        CameraMount_System.c
 * @brief       カメラマウントコントローラ システム制御
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

#include "CameraMount_System.h"
#include "CameraMount_Version.h"
#include "CameraMount_Servo.h"
#include "CameraMount_Register.h"
#include "CameraMount_EEPROM.h"


/**
 * @name    システム管理
 */
/*! @{ */
uint8_t System_state;                   /*!< 現在のシステムステート */
uint8_t System_state_next;              /*!< 次のシステムステート */

uint8_t System_status;                  /*!< システムステータス */
uint8_t System_error;                   /*!< システムエラー */

bool System_initialization_request;     /*!< システム初期化要求 */

uint16_t com_timeout_limit;             /*!< 通信タイムアウト検出時間，10ミリ秒単位 */
uint16_t com_timeout_timer;             /*!< 通信タイムアウト検出用タイマ */
/*! @} */


/**
 * @name    システムコマンド
 */
/*! @{ */
uint8_t System_command[SYSTEM_COMMAND_LENGTH_MAX];      /*!< システムコマンド */
uint8_t System_command_length;                          /*!< システムコマンド長 */
uint8_t System_command_recieved_bytes;                  /*!< システムコマンド受信長 */
/*! @} */


/**
 * @name    システムレスポンス
 */
/*! @{ */
uint8_t System_response[SYSTEM_RESPONSE_LENGTH_MAX];    /*!< システムレスポンス */
uint8_t System_response_length;                         /*!< システムレスポンス長 */
/*! @} */


/**
 * @brief   システムコマンド制御を初期化する
 */
#inline
static void System_initCommandCtrl(void);


/**
 * @brief   システムコマンドを取得する
 * @retval          TRUE                受信完了し，取得成功
 * @retval          FALSE               受信待機中または受信中のため，取得失敗
 */
static bool System_fetchCommand(void);


/**
 * @brief   システムコマンドのオペコードを取得する
 * @return          オペコード
 */
#inline
static uint8_t System_getCommandOpcode(void);


/**
 * @brief   システムコマンドのコマンド長を取得する
 * @return          コマンド長
 */
#inline
static uint8_t System_getCommandLength(void);


/**
 * @brief   システムコマンドを実行する
 */
static void System_execCommand(void);


/**
 * @brief   システムレスポンス制御を初期化する
 */
#inline
static void System_initResponseCtrl(void);


/**
 * @brief   システムレスポンスを送信する
 */
static void System_sendResponse(void);


/**
 * @brief   INITステートのシステムタスクを実行する
 */
static void System_execTask_INITIALIZATION(void);


/**
 * @brief   RUNステートのシステムタスクを実行する
 */
static void System_execTask_RUN(void);


/**
 * @brief   HALTステートのシステムタスクを実行する
 */
static void System_execTask_HALT(void);


#inline
uint8_t System_getState(void)
{
    return System_state;
}


#inline
uint8_t System_getStatus(void)
{
    return System_status;
}


#inline
uint8_t System_getError(void)
{
    return System_error;
}


void System_init(void)
{
    System_state = SYSTEM_INITIALIZATION;
    System_state_next = SYSTEM_INITIALIZATION;
    
    System_status = 0x00;
    switch (restart_cause()) {
        case WDT_TIMEOUT:
            System_status |= SYSTEM_STATUS_WDT_TIMEOUT;
            break;
        case NORMAL_POWER_UP:
        default:
            break;
    }
    
    System_error = 0x00;
    
    System_initialization_request = TRUE;
    
    return;
}


void System_execTask(void)
{
    // システムステートの更新
    System_state = System_state_next;
    
    switch (System_state) {
        case SYSTEM_INITIALIZATION:
            System_execTask_INITIALIZATION();
            break;
        case SYSTEM_RUN:
            System_execTask_RUN();
            break;
        case SYSTEM_HALT:
            System_execTask_HALT();
            break;
        default:
            break;
    }
    
    return;
}


#inline
static void System_initCommandCtrl(void)
{
    System_command_length = 1;
    System_command_recieved_bytes = 0;
    
    return;
}


static bool System_fetchCommand(void)
{
    bool result;
    
    while ((uart_rx_isReceived() == TRUE) && (System_command_recieved_bytes < System_command_length)) {
        System_command[System_command_recieved_bytes] = uart_rx_getReceivedData();
        System_command_recieved_bytes++;
        
        if (System_command_recieved_bytes == 1) {
            System_command_length = System_getCommandLength();
        }
    }
    
    if (System_command_recieved_bytes == System_command_length) {
        result = TRUE;
    }
    else {
        result = FALSE;
    }
    
    return result;
}


#inline
static uint8_t System_getCommandOpcode(void)
{
    return ((System_command[0] & SYSTEM_COMMAND_MASK_OPCODE) >> 4);
}


#inline
static uint8_t System_getCommandLength(void)
{
    return (System_command[0] & SYSTEM_COMMAND_MASK_LENGTH);
}


static void System_execCommand(void)
{
    System_initResponseCtrl();
    
    switch (System_getCommandOpcode()) {
        case SYSTEM_COMMAND_RESET:
            reset_cpu();
            break;
        case SYSTEM_COMMAND_INITIALIZE:
            System_initialization_request = TRUE;
            break;
        case SYSTEM_COMMAND_GET_VERSION:
            System_response[1] = CAMERAMOUNT_VERSION;
            System_response[2] = CAMERAMOUNT_REVISION;
            System_response[0] = System_error;
            System_response_length = 3;
            System_sendResponse();
            break;
        case SYSTEM_COMMAND_READ_REGISTER:
            System_response[1] = Register_read(System_command[1], &(System_response[2]));
            if ((System_response[1] + 2) > SYSTEM_RESPONSE_LENGTH_MAX) {
                System_error |= SYSTEM_ERROR_INVALID_COMMAND;
                System_response[0] = System_error;
                System_response_length = 2;
                System_sendResponse();
            }
            else {
                System_response[0] = System_error;
                System_response_length = System_response[1] + 2;
                System_sendResponse();
            }
            break;
        case SYSTEM_COMMAND_WRITE_REGISTER:
            if (Register_getSize(System_command[1]) != (System_getCommandLength() - 2)) {
                System_error |= SYSTEM_ERROR_INVALID_COMMAND;
                System_response[0] = System_error;
                System_response_length = 1;
                System_sendResponse();
            }
            else {
                System_response[1] = Register_write(System_command[1], &(System_command[2]));
                System_response[0] = System_error;
                System_response_length = 2;
                System_sendResponse();
            }
            break;
        case SYSTEM_COMMAND_READ_EEPROM:
            System_response[1] = EEPROM_read(System_command[1], &(System_response[2]));
            if ((System_response[1] + 2) > SYSTEM_RESPONSE_LENGTH_MAX) {
                System_error |= SYSTEM_ERROR_INVALID_COMMAND;
                System_response[0] = System_error;
                System_response_length = 2;
                System_sendResponse();
            }
            else {
                System_response[0] = System_error;
                System_response_length = System_response[1] + 2;
                System_sendResponse();
            }
            break;
        case SYSTEM_COMMAND_WRITE_EEPROM:
            if (EEPROM_getSize(System_command[1]) != (System_getCommandLength() - 2)) {
                System_error |= SYSTEM_ERROR_INVALID_COMMAND;
                System_response[0] = System_error;
                System_response_length = 1;
                System_sendResponse();
            }
            else {
                System_response[1] = EEPROM_write(System_command[1], &(System_command[2]));
                System_response[0] = System_error;
                System_response_length = 2;
                System_sendResponse();
            }
            break;
        default:
            System_error |= SYSTEM_ERROR_INVALID_COMMAND;
            System_response[0] = System_error;
            System_response_length = 1;
            System_sendResponse();
            break;
    }
    
    return;
}


#inline
static void System_initResponseCtrl(void)
{
    System_response_length = 0;
    
    return;
}


static void System_sendResponse(void)
{
    uint8_t System_response_send_bytes;
    
    System_response_send_bytes = 0;
    while (System_response_send_bytes < System_response_length) {
        uart_tx_addTransmitData(System_response[System_response_send_bytes]);
        System_response_send_bytes++;
    }
    
    return;
}


static void System_execTask_INITIALIZATION(void)
{
    System_initialization_request = FALSE;
    
    EEPROM_init();
    
    EEPROM_read(EEPROM_PAN_SERVO_NEUTRAL_POSITION, &(PanServo.neutral_position));
    EEPROM_read(EEPROM_PAN_SERVO_MIN_POSITION, &(PanServo.min_position));
    EEPROM_read(EEPROM_PAN_SERVO_MAX_POSITION, &(PanServo.max_position));
    PanServo.request_position = PanServo.neutral_position;
    EEPROM_read(EEPROM_TILT_SERVO_NEUTRAL_POSITION, &(TiltServo.neutral_position));
    EEPROM_read(EEPROM_TILT_SERVO_MIN_POSITION, &(TiltServo.min_position));
    EEPROM_read(EEPROM_TILT_SERVO_MAX_POSITION, &(TiltServo.max_position));
    TiltServo.request_position = TiltServo.neutral_position;
    EEPROM_read(EEPROM_POWER_LED_BRIGHTNESS_MIN, &PowerLED_brightness_min);
    EEPROM_read(EEPROM_POWER_LED_BRIGHTNESS_MAX, &PowerLED_brightness_max);
    EEPROM_read(EEPROM_POWER_LED_BRIGHTNESS_STEP, &PowerLED_brightness_step);
    EEPROM_read(EEPROM_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT, &StatusLED_brink_period_COM_TIMEOUT);
    EEPROM_read(EEPROM_ERROR_LED_BRINK_PERIOD, &ErrorLED_brink_period);
    EEPROM_read(EEPROM_COM_TIMEOUT_LIMIT, &com_timeout_limit);
    
    System_initCommandCtrl();
    System_initResponseCtrl();
    uart_tx_initBuffer();
    uart_rx_initBuffer();
    uart_rx_enable();
    com_timeout_timer = 0;
    
    if (System_error != 0) {
        System_state_next = SYSTEM_HALT;
    }
    else {
        System_state_next = SYSTEM_RUN;
    }
    
    return;
}


static void System_execTask_RUN(void)
{
    bool retval;
    
    retval = System_fetchCommand();
    if (retval == TRUE) {
        System_execCommand();
        System_initCommandCtrl();
        com_timeout_timer = 0;
    }
    else {
        com_timeout_timer++;
    }
    
    if (com_timeout_timer >= com_timeout_limit) {
        System_status |= SYSTEM_STATUS_COM_TIMEOUT;
        System_initCommandCtrl();
        System_initResponseCtrl();
        uart_tx_initBuffer();
        uart_rx_initBuffer();
        com_timeout_timer = 0;
    }
    
    if (System_error != 0) {
        System_state_next = SYSTEM_HALT;
    }
    else if (System_initialization_request == TRUE) {
        System_state_next = SYSTEM_INITIALIZATION;
    }
    else {
        System_state_next = SYSTEM_RUN;
    }
    
    return;
}


static void System_execTask_HALT(void)
{
    bool retval;
    
    retval = System_fetchCommand();
    if (retval == TRUE) {
        System_execCommand();
        System_initCommandCtrl();
        com_timeout_timer = 0;
    }
    else {
        com_timeout_timer++;
    }
    
    if (com_timeout_timer >= com_timeout_limit) {
        System_status |= SYSTEM_STATUS_COM_TIMEOUT;
        System_initCommandCtrl();
        System_initResponseCtrl();
        uart_tx_initBuffer();
        uart_rx_initBuffer();
        com_timeout_timer = 0;
    }
    
    if (System_initialization_request == TRUE) {
        System_state_next = SYSTEM_INITIALIZATION;
    }
    else {
        System_state_next = SYSTEM_HALT;
    }
    
    return;
}
