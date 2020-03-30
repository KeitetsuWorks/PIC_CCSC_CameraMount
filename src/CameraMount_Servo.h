/**
 * @file        CameraMount_Servo.h
 * @brief       カメラマウントコントローラ サーボ制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_SERVO_H__
#define __CAMERAMOUNT_SERVO_H__


/**
 * @name    タイマ1の設定
 */
/** @{ */
#define TIMER1_INITIAL_VALUE        59286   /**< 10ミリ秒 */
/** @} */


/**
 * @name    サーボ制御モード
 */
/** @{ */
#define SERVO_CTRL_MODE_POSITION    0       /**< 位置指示モード */
#define SERVO_CTRL_MODE_ANGLE       1       /**< 角度指示モード */
#define SERVO_CTRL_MODE_NUM         2       /**< サーボ制御モード数 */
/** @} */


/**
 * @name    サーボ制御チャンネル
 */
/** @{ */
#define SERVO_CHANNEL_PAN           0       /**< 水平方向用サーボ */
#define SERVO_CHANNEL_TILT          1       /**< 垂直方向用サーボ */
#define SERVO_CHANNEL_NUM           2       /**< サーボ制御チャンネル数 */
/** @} */


/**
 * @struct  servo_st
 * @brief   サーボ制御管理構造体
 */
struct servo_st {
    int16_t request_angle;      /**< 指示角度 */
    uint16_t request_position;  /**< 指示位置 */
    uint16_t neutral_position;  /**< ニュートラル位置 */
    uint16_t min_position;      /**< 最小位置 */
    uint16_t max_position;      /**< 最大位置 */
};


/**
 * @brief   サーボ制御の初期化
 */
void Servo_init(void);


/**
 * @brief   サーボ制御信号（パルス信号）の開始ハンドラ処理（タイマ1割込み処理）
 */
void isr_TIMER1(void);


/**
 * @brief   サーボ制御信号（パルス信号）の終了ハンドラ処理（CCP1割込み処理）
 */
void isr_CCP1(void);

#endif  // __CAMERAMOUNT_SERVO_H__
