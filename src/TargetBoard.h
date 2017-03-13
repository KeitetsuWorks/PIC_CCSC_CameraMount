/**
 * @file        TargetBoard.h
 * @brief       カメラマウントコントローラ ターゲットボード設定
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __TARGETBOARD_H__
#define __TARGETBOARD_H__

#if _DEVELOPMENTBOARD == 1
#include <DevelopmentBoard_16F877A.h>
#else
#include <CameraMount_16F88.h>
#endif

#endif  // __TARGETBOARD_H__
