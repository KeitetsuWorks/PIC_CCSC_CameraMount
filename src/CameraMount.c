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


// システム
#include "CameraMount_System.c"
#include "CameraMount_AppManager.c"


// アプリケーション
#include "CameraMount_CyclicHandler.c"
#include "CameraMount_FreeRunningTimer.c"
#include "CameraMount_LED.c"
#include "CameraMount_Servo.c"
#include "CameraMount_CommandIF.c"


// 共通ライブラリ
#include "ccsc_uart.c"


// ベース
#include "CameraMount_Register.c"
#include "CameraMount_EEPROM.c"
#include "CameraMount_Main.c"
