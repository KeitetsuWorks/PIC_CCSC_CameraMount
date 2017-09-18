/**
 * @file        CameraMount_LED.c
 * @brief       カメラマウントコントローラ LED制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "CameraMount_LED.h"
#include "CameraMount_System.h"
#include "CameraMount_FreeRunningTimer.h"
#include "CameraMount_EEPROM.h"


uint8_t LED_system_state_prev;                  /*!< 前のシステムステート */


/**
 * @name    電源LEDの制御変数
 */
/*! @{ */
bool PowerLED_ctrl_flag;                        /*!< 電源LEDの制御フラグ */
/*! @} */


/**
 * @name    ステータスLEDの制御変数
 */
/*! @{ */
bool StatusLED_ctrl_flag;                       /*!< ステータスLEDの制御フラグ */
struct timer_5ms_st StatusLED_timer;            /*!< ステータスLEDの制御タイマ */
uint8_t StatusLED_brink_period_COM_TIMEOUT;     /*!< ステータスLEDの点滅周期，通信タイムアウト */
/*! @} */


/**
 * @name    エラーLEDの制御変数
 */
/*! @{ */
bool ErrorLED_ctrl_flag;                        /*!< エラーLEDの制御フラグ */
struct timer_5ms_st ErrorLED_timer;             /*!< エラーLEDの制御タイマ */
uint8_t ErrorLED_brink_period;                  /*!< エラーLEDの点滅周期 */
/*! @} */


/**
 * @brief   電源LEDを初期化する
 */
static void PowerLED_init(void);


/**
 * @brief   電源LEDの点灯状態を更新する
 */
static void PowerLED_ctrl(void);


/**
 * @brief   電源LEDを点灯する
 */
#inline
static void PowerLED_on(void);


/**
 * @brief   電源LEDを消灯する
 */
#inline
static void PowerLED_off(void);


/**
 * @brief   ステータスLEDを初期化する
 */
static void StatusLED_init(void);


/**
 * @brief   ステータスLEDの点灯状態を更新する
 */
static void StatusLED_ctrl(void);


/**
 * @brief   ステータスLEDを点灯する
 */
#inline
static void StatusLED_on(void);


/**
 * @brief   ステータスLEDを消灯する
 */
#inline
static void StatusLED_off(void);


/**
 * @brief   エラーLEDを初期化する
 */
static void ErrorLED_init(void);


/**
 * @brief   エラーLEDの点灯状態を更新する
 */
static void ErrorLED_ctrl(void);


/**
 * @brief   エラーLEDを点灯する
 */
#inline
static void ErrorLED_on(void);


/**
 * @brief   エラーLEDを消灯する
 */
#inline
static void ErrorLED_off(void);


void LED_init(void)
{
    LED_system_state_prev = SYSTEM_INITIALIZATION;
    
    PowerLED_init();
    StatusLED_init();
    ErrorLED_init();

    return;
}


void LED_ctrl(void)
{
    uint8_t system_state;
    
    system_state = System_getState();
    
    PowerLED_ctrl();
    StatusLED_ctrl();
    ErrorLED_ctrl();
    
    LED_system_state_prev = system_state;

    return;
}


static void PowerLED_init(void)
{
    PowerLED_on();
    
    return;
}


static void PowerLED_ctrl(void)
{
    return;
}


#inline
static void PowerLED_on(void)
{
    output_high(POWER_LED_PIN);
    PowerLED_ctrl_flag = ON;
    
    return;
}


#inline
static void PowerLED_off(void)
{
    output_low(POWER_LED_PIN);
    PowerLED_ctrl_flag = OFF;
    
    return;
}


static void StatusLED_init(void)
{
    EEPROM_read(EEPROM_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT, &StatusLED_brink_period_COM_TIMEOUT);
    FreeRunningTimer_5ms_isTimeout(&StatusLED_timer, FALSE, StatusLED_brink_period_COM_TIMEOUT);
    
    StatusLED_off();
    
    return;
}


static void StatusLED_ctrl(void)
{
    bool retval;
    
    switch (System_getState()) {
        case SYSTEM_INITIALIZATION: // 初期化中
            FreeRunningTimer_5ms_isTimeout(&StatusLED_timer, FALSE, StatusLED_brink_period_COM_TIMEOUT);
            
            StatusLED_on();
            break;
        case SYSTEM_RUN:            // 動作中
        case SYSTEM_HALT:           // 停止中
            if ((System_getStatus() & SYSTEM_STATUS_COM_TIMEOUT) != 0x00) {
                retval = FreeRunningTimer_5ms_isTimeout(&StatusLED_timer, TRUE, StatusLED_brink_period_COM_TIMEOUT);
                if (retval == TRUE) {
                    FreeRunningTimer_5ms_isTimeout(&StatusLED_timer, FALSE, StatusLED_brink_period_COM_TIMEOUT);
                    
                    if (StatusLED_ctrl_flag == ON) {
                        StatusLED_off();
                    }
                    else {
                        StatusLED_on();
                    }
                    FreeRunningTimer_5ms_isTimeout(&StatusLED_timer, TRUE, StatusLED_brink_period_COM_TIMEOUT);
                }
            }
            else {
                FreeRunningTimer_5ms_isTimeout(&StatusLED_timer, FALSE, StatusLED_brink_period_COM_TIMEOUT);
                
                StatusLED_on();
            }
            break;
        default:
            FreeRunningTimer_5ms_isTimeout(&StatusLED_timer, FALSE, StatusLED_brink_period_COM_TIMEOUT);
            
            StatusLED_off();
            break;
    }

    return;
}


#inline
static void StatusLED_on(void)
{
    output_high(STATUS_LED_PIN);
    StatusLED_ctrl_flag = ON;
    
    return;
}


#inline
static void StatusLED_off(void)
{
    output_low(STATUS_LED_PIN);
    StatusLED_ctrl_flag = OFF;
    
    return;
}


static void ErrorLED_init(void)
{
    EEPROM_read(EEPROM_ERROR_LED_BRINK_PERIOD, &ErrorLED_brink_period);
    FreeRunningTimer_5ms_isTimeout(&ErrorLED_timer, FALSE, ErrorLED_brink_period);
    
    ErrorLED_off();
    
    return;
}


static void ErrorLED_ctrl(void)
{
    bool retval;
    
    switch (System_getState()) {
        case SYSTEM_INITIALIZATION: // 初期化中
            FreeRunningTimer_5ms_isTimeout(&ErrorLED_timer, FALSE, ErrorLED_brink_period);
            
            ErrorLED_off();
            break;
        case SYSTEM_RUN:            // 動作中
        case SYSTEM_HALT:           // 停止中
            if (System_getError() != 0x00) {
                retval = FreeRunningTimer_5ms_isTimeout(&ErrorLED_timer, TRUE, ErrorLED_brink_period);
                if (retval == TRUE) {
                    FreeRunningTimer_5ms_isTimeout(&ErrorLED_timer, FALSE, ErrorLED_brink_period);
                    
                    if (ErrorLED_ctrl_flag == ON) {
                        ErrorLED_off();
                    }
                    else {
                        ErrorLED_on();
                    }
                    FreeRunningTimer_5ms_isTimeout(&ErrorLED_timer, TRUE, ErrorLED_brink_period);
                }
            }
            else {
                FreeRunningTimer_5ms_isTimeout(&ErrorLED_timer, FALSE, ErrorLED_brink_period);
                
                ErrorLED_off();
            }
            break;
        default:
            FreeRunningTimer_5ms_isTimeout(&ErrorLED_timer, FALSE, ErrorLED_brink_period);
            
            ErrorLED_off();
            break;
    }

    return;
}


#inline
static void ErrorLED_on(void)
{
    output_high(ERROR_LED_PIN);
    ErrorLED_ctrl_flag = ON;
    
    return;
}


#inline
static void ErrorLED_off(void)
{
    output_low(ERROR_LED_PIN);
    ErrorLED_ctrl_flag = OFF;
    
    return;
}
