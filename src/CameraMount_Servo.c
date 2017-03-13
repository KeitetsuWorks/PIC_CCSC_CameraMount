/**
 * @file        CameraMount_Servo.c
 * @brief       カメラマウントコントローラ サーボ制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "CameraMount_Servo.h"
#include "CameraMount_System.h"


/**
 * @brief   水平方向用サーボ制御ピンをONする
 */
#inline
static void PanServo_onPin(void);


/**
 * @brief   水平方向用サーボ制御ピンをOFFする
 */
#inline
static void PanServo_offPin(void);


/**
 * @brief   垂直方向用サーボ制御ピンをONする
 */
#inline
static void TiltServo_onPin(void);


/**
 * @brief   垂直方向用サーボ制御ピンをOFFする
 */
#inline
static void TiltServo_offPin(void);


struct servo_t PanServo;                /*!< 水平方向用サーボ */
struct servo_t TiltServo;               /*!< 垂直方向用サーボ */


void Servo_init(void)
{
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_64);
    
    return;
}


void PanServo_ctrl(void)
{
    uint8_t system_state;
    uint8_t pan_servo_position;
    
    system_state = System_getState();
    
    switch (system_state) {
        case SYSTEM_RUN:            // 動作中
            pan_servo_position = PanServo.request_position;
            break;
        case SYSTEM_HALT:           // 停止中
            pan_servo_position = PanServo.neutral_position;
            break;
        case SYSTEM_INITIALIZATION: // 初期化中
        default:
            pan_servo_position = PanServo.neutral_position;
            break;
    }
    
    if (pan_servo_position < PanServo.min_position) {
        pan_servo_position = PanServo.min_position;
    }
    else if (pan_servo_position > PanServo.max_position) {
        pan_servo_position = PanServo.max_position;
    }
    
    set_timer0(TIMER0_INITIAL_VALUE);
    PanServo_onPin();
    while (get_timer0() < pan_servo_position) {
    }
    PanServo_offPin();
    
    return;
}


void TiltServo_ctrl(void)
{
    uint8_t system_state;
    uint8_t tilt_servo_position;
    
    system_state = System_getState();
    
    switch (system_state) {
        case SYSTEM_RUN:            // 動作中
            tilt_servo_position = TiltServo.request_position;
            break;
        case SYSTEM_HALT:           // 停止中
            tilt_servo_position = TiltServo.neutral_position;
            break;
        case SYSTEM_INITIALIZATION: // 初期化中
        default:
            tilt_servo_position = TiltServo.neutral_position;
            break;
    }
    
    if (tilt_servo_position < TiltServo.min_position) {
        tilt_servo_position = TiltServo.min_position;
    }
    else if (tilt_servo_position > TiltServo.max_position) {
        tilt_servo_position = TiltServo.max_position;
    }
    
    set_timer0(TIMER0_INITIAL_VALUE);
    TiltServo_onPin();
    while (get_timer0() < tilt_servo_position) {
    }
    TiltServo_offPin();
    
    return;
}


#inline
static void PanServo_onPin(void)
{
    output_high(PAN_SERVO_PIN);
    
    return;
}


#inline
static void PanServo_offPin(void)
{
    output_low(PAN_SERVO_PIN);
    
    return;
}


#inline
static void TiltServo_onPin(void)
{
    output_high(TILT_SERVO_PIN);
    
    return;
}


#inline
static void TiltServo_offPin(void)
{
    output_low(TILT_SERVO_PIN);
    
    return;
}
