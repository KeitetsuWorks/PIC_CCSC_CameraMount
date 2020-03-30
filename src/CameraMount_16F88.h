/**
 * @file        CameraMount_16F88.h
 * @brief       カメラマウントコントローラ 16F88用設定
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_16F88_H__
#define __CAMERAMOUNT_16F88_H__

#include <16F88.h>

#fuses HS, WDT, PUT, NOMCLR, BROWNOUT, NOLVP, NOCPD, NOWRT, NODEBUG, CCPB3, NOPROTECT, NOFCMEN, NOIESO

#device ADC=10
#device WRITE_EEPROM=ASYNC

#use delay(clock=20000000)
#use rs232(baud = 9600, parity = N, xmit = PIN_B5, rcv = PIN_B2, bits = 8)


#define PAN_SERVO_PIN           PIN_A0  /**< RA0，水平方向用サーボピン */
#define TILT_SERVO_PIN          PIN_A1  /**< RA1，垂直方向用サーボピン */
#define STATUS_LED_PIN          PIN_A2  /**< RA2，ステータスLEDピン */
#define ERROR_LED_PIN           PIN_A3  /**< RA3，エラーLEDピン */
#define POWER_LED_PIN           PIN_B0  /**< RB0，電源LEDピン */

#endif  // __CAMERAMOUNT_16F88_H__
