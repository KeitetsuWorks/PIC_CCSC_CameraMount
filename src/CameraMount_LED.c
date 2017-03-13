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


uint8_t LED_system_state_prev;                  /*!< 前のシステムステート */


/**
 * @name    電源LEDの制御変数
 */
/*! @{ */
bool PowerLED_ctrl_flag;                        /*!< 電源LEDの制御フラグ */
uint16_t PowerLED_brightness;                   /*!< 電源LEDのPWMデューティ */
uint16_t PowerLED_brightness_min;               /*!< 電源LEDの最小PWMデューティ */
uint16_t PowerLED_brightness_max;               /*!< 電源LEDの最大PWMデューティ */
uint8_t PowerLED_brightness_step;               /*!< 電源LEDのPWMデューティの増減幅 */
/*! @} */


/**
 * @name    ステータスLEDの制御変数
 */
/*! @{ */
bool StatusLED_ctrl_flag;                       /*!< ステータスLEDの制御フラグ */
uint8_t StatusLED_timer;                        /*!< ステータスLEDの制御タイマ */
uint8_t StatusLED_brink_period_COM_TIMEOUT;     /*!< ステータスLEDの点滅周期，通信タイムアウト */
/*! @} */


/**
 * @name    エラーLEDの制御変数
 */
/*! @{ */
bool ErrorLED_ctrl_flag;                        /*!< エラーLEDの制御フラグ */
uint8_t ErrorLED_timer;                         /*!< エラーLEDの制御タイマ */
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
 * @brief   電源LEDの輝度を設定する
 */
#inline
static void PowerLED_setBrightness(uint16_t brightness);


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
    PowerLED_brightness_min = POWER_LED_BRIGHTNESS_MIN;
    PowerLED_brightness_max = POWER_LED_BRIGHTNESS_MAX;
    PowerLED_brightness_step = POWER_LED_BRIGHTNESS_STEP;
    
    PowerLED_brightness = PowerLED_brightness_min;
    PowerLED_ctrl_flag = TRUE;
    PowerLED_setBrightness(PowerLED_brightness);
    
    return;
}


static void PowerLED_ctrl(void)
{
    if (PowerLED_ctrl_flag == TRUE) {
        PowerLED_brightness += PowerLED_brightness_step;
        if (PowerLED_brightness >= PowerLED_brightness_max) {
            PowerLED_brightness = PowerLED_brightness_max;
            PowerLED_ctrl_flag = FALSE;
        }
    }
    else {
        PowerLED_brightness -= PowerLED_brightness_step;
        if (PowerLED_brightness <= PowerLED_brightness_min) {
            PowerLED_brightness = PowerLED_brightness_min;
            PowerLED_ctrl_flag = TRUE;
        }
    }
    
    PowerLED_setBrightness(PowerLED_brightness);
    
    return;
}


#inline
static void PowerLED_setBrightness(uint16_t brightness)
{
    set_pwm1_duty(brightness);
    
    return;
}


static void StatusLED_init(void)
{
    StatusLED_timer = 0;
    StatusLED_brink_period_COM_TIMEOUT = STATUS_LED_BRINK_PERIOD_COM_TIMEOUT;
    
    StatusLED_off();
    
    return;
}


static void StatusLED_ctrl(void)
{
    switch (System_getState()) {
        case SYSTEM_INITIALIZATION: // 初期化中
            StatusLED_timer = 0;
            
            StatusLED_on();
            break;
        case SYSTEM_RUN:            // 動作中
        case SYSTEM_HALT:           // 停止中
            if ((System_getStatus() & SYSTEM_STATUS_COM_TIMEOUT) != 0x00) {
                if (StatusLED_timer >= StatusLED_brink_period_COM_TIMEOUT) {
                    StatusLED_timer = 0;
                    
                    if (StatusLED_ctrl_flag == ON) {
                        StatusLED_off();
                    }
                    else {
                        StatusLED_on();
                    }
                }
                else {
                    StatusLED_timer++;
                }
            }
            else {
                StatusLED_timer = 0;
                
                StatusLED_on();
            }
            break;
        default:
            StatusLED_timer = 0;
            
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
    ErrorLED_timer = 0;
    ErrorLED_brink_period = ERROR_LED_BRINK_PERIOD;
    
    ErrorLED_off();
    
    return;
}


static void ErrorLED_ctrl(void)
{
    switch (System_getState()) {
        case SYSTEM_INITIALIZATION: // 初期化中
            ErrorLED_timer = 0;
            
            ErrorLED_off();
            break;
        case SYSTEM_RUN:            // 動作中
        case SYSTEM_HALT:           // 停止中
            if (System_getError() != 0x00) {
                if (ErrorLED_timer >= ErrorLED_brink_period) {
                    ErrorLED_timer = 0;
                    
                    if (ErrorLED_ctrl_flag == ON) {
                        ErrorLED_off();
                    }
                    else {
                        ErrorLED_on();
                    }
                }
                else {
                    ErrorLED_timer++;
                }
            }
            else {
                ErrorLED_timer = 0;
                
                ErrorLED_off();
            }
            break;
        default:
            ErrorLED_timer = 0;
            
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
