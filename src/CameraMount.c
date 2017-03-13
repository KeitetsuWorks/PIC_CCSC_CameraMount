/**
 * @file        CameraMount.c
 * @brief       カメラマウントコントローラ
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "CameraMount.h"


#include "ccsc_uart.c"

#include "CameraMount_LED.c"
#include "CameraMount_Servo.c"

#include "CameraMount_System.c"
#include "CameraMount_Register.c"
#include "CameraMount_EEPROM.c"
#include "CameraMount_CyclicHandler.c"
#include "CameraMount_Main.c"
