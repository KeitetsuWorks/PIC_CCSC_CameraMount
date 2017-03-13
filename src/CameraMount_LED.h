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
 * @name    電源LEDの設定
 */
/*! @{ */
#define POWER_LED_BRIGHTNESS_MIN                    16          /*!< 電源LEDの最小PWMデューティ */
#define POWER_LED_BRIGHTNESS_MAX                    511         /*!< 電源LEDの最大PWMデューティ */
#define POWER_LED_BRIGHTNESS_STEP                   4           /*!< 電源LEDのPWMデューティの増減幅 */
/*! @} */


/**
 * @name    ステータスLEDの設定
 */
/*! @{ */
#define STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         50          /*!< ステータスLEDの点滅間隔，通信タイムアウト，1000ミリ秒 */
/*! @} */


/**
 * @name    エラーLEDの設定
 */
/*! @{ */
#define ERROR_LED_BRINK_PERIOD                      25          /*!< エラーLEDの点滅間隔，500ミリ秒 */
/*! @} */


/**
 * @brief   LEDを初期化する
 */
void LED_init(void);


/**
 * @brief   LEDの点灯状態を更新する
 */
void LED_ctrl(void);

#endif  // __CAMERAMOUNT_LED_H__
