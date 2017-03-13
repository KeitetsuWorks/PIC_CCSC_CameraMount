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
 * @struct  servo_t
 * @brief   サーボ制御管理構造体
 */
struct servo_t {
    uint8_t request_position;   /*!< 指示位置 */
    uint8_t neutral_position;   /*!< ニュートラル位置 */
    uint8_t min_position;       /*!< 最小位置 */
    uint8_t max_position;       /*!< 最大位置 */
};


/**
 * @brief   サーボ制御の初期化
 */
void Servo_init(void);


/**
 * @brief   水平方向用サーボ制御関数
 */
void PanServo_ctrl(void);


/**
 * @brief   垂直方向用サーボ制御関数
 */
void TiltServo_ctrl(void);

#endif  // __CAMERAMOUNT_SERVO_H__
