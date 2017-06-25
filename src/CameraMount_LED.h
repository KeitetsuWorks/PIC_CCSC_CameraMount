/**
 * @file        CameraMount_LED.h
 * @brief       カメラマウントコントローラ LED制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_LED_H__
#define __CAMERAMOUNT_LED_H__


/**
 * @brief   LEDを初期化する
 */
void LED_init(void);


/**
 * @brief   LEDの点灯状態を更新する
 */
void LED_ctrl(void);

#endif  // __CAMERAMOUNT_LED_H__
