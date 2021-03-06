/**
 * @file        DevelopmentBoard_16F877A.h
 * @brief       カメラマウントコントローラ 16F877A開発ボード用設定
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __DEVELOPMENTBOARD_16F877A_H__
#define __DEVELOPMENTBOARD_16F877A_H__

#include <16F877A.h>

#fuses HS, WDT, PUT, NODEBUG, NOPROTECT, BROWNOUT, NOLVP, NOCPD, NOWRT

#device ADC=10
#device WRITE_EEPROM=ASYNC

#use delay(clock = 20000000)
#use rs232(baud = 9600, parity = N, xmit = PIN_C6, rcv = PIN_C7, bits = 8)


#define PAN_SERVO_PIN           PIN_A0  /**< RA0，水平方向用サーボピン */
#define TILT_SERVO_PIN          PIN_A1  /**< RA1，垂直方向用サーボピン */
#define STATUS_LED_PIN          PIN_C0  /**< RC0，ステータスLEDピン */
#define ERROR_LED_PIN           PIN_C3  /**< RC3，エラーLEDピン */
#define POWER_LED_PIN           PIN_C4  /**< RC4，電源LEDピン */

#endif  // __DEVELOPMENTBOARD_16F877A_H__
