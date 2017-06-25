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
#include "CameraMount_EEPROM.h"


/**
 * @brief   水平方向用サーボのサーボ制御信号（パルス信号）を開始する
 */
static void PanServo_beginPulse(void);


/**
 * @brief   水平方向用サーボのサーボ制御信号（パルス信号）を終了する
 */
static void PanServo_endPulse(void);


/**
 * @brief   垂直方向用サーボのサーボ制御信号（パルス信号）を開始する
 */
static void TiltServo_beginPulse(void);


/**
 * @brief   垂直方向用サーボのサーボ制御信号（パルス信号）を終了する
 */
static void TiltServo_endPulse(void);


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


uint8_t Servo_channel;                  /*!< サーボ制御チャンネル */
struct servo_t PanServo;                /*!< 水平方向用サーボ */
struct servo_t TiltServo;               /*!< 垂直方向用サーボ */


void Servo_init(void)
{
    Servo_channel = 0;
    
    EEPROM_read(EEPROM_PAN_SERVO_NEUTRAL_POSITION, &(PanServo.neutral_position));
    EEPROM_read(EEPROM_PAN_SERVO_MIN_POSITION, &(PanServo.min_position));
    EEPROM_read(EEPROM_PAN_SERVO_MAX_POSITION, &(PanServo.max_position));
    PanServo.request_position = PanServo.neutral_position;
    EEPROM_read(EEPROM_TILT_SERVO_NEUTRAL_POSITION, &(TiltServo.neutral_position));
    EEPROM_read(EEPROM_TILT_SERVO_MIN_POSITION, &(TiltServo.min_position));
    EEPROM_read(EEPROM_TILT_SERVO_MAX_POSITION, &(TiltServo.max_position));
    TiltServo.request_position = TiltServo.neutral_position;
    
    // ペリフェラル設定
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
    setup_ccp1(CCP_COMPARE_INT);
    
    // タイマ1の開始
    set_timer1(TIMER1_INITIAL_VALUE);
    
    // 割込み設定
    enable_interrupts(INT_TIMER1);
    enable_interrupts(INT_CCP1);
    
    return;
}


#int_TIMER1
void isr_TIMER1(void)
{
    // サーボ制御信号（パルス信号）の開始
    switch (Servo_channel) {
        case SERVO_CHANNEL_PAN:
            PanServo_beginPulse();
            break;
        case SERVO_CHANNEL_TILT:
            TiltServo_beginPulse();
            break;
        default:
            break;
    }
    
    return;
}


#int_CCP1
void isr_CCP1(void)
{
    // サーボ制御信号（パルス信号）の終了
    switch (Servo_channel) {
        case SERVO_CHANNEL_PAN:
            PanServo_endPulse();
            break;
        case SERVO_CHANNEL_TILT:
            TiltServo_endPulse();
            break;
        default:
            break;
    }
    
    Servo_channel++;
    if (Servo_channel >= SERVO_CHANNEL_NUM) {
        Servo_channel = 0;
    }
    
    return;
}


static void PanServo_beginPulse(void)
{
    uint16_t pan_servo_position;
    
    // タイマ1の再開
    set_timer1(TIMER1_INITIAL_VALUE);
    
    PanServo_onPin();
    
    switch (System_getState()) {
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
    
    CCP_1 = pan_servo_position;
    
    return;
}


static void PanServo_endPulse(void)
{
    PanServo_offPin();
    
    return;
}


static void TiltServo_beginPulse(void)
{
    uint16_t tilt_servo_position;
    
    // タイマ1の再開
    set_timer1(TIMER1_INITIAL_VALUE);
    
    TiltServo_onPin();
    
    switch (System_getState()) {
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
    
    CCP_1 = tilt_servo_position;
    
    return;
}


static void TiltServo_endPulse(void)
{
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
