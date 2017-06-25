/**
 * @file        CameraMount_AppManager.h
 * @brief       カメラマウントコントローラ アプリケーションマネージャ
 * @author      Keitetsu
 * @date        2016/05/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_APPMANAGER_H__
#define __CAMERAMOUNT_APPMANAGER_H__


/**
 * @brief   アプリケーションマネージャを初期化する
 */
void AppManager_init(void);


/**
 * @brief   アプリケーション実行要求をセットする
 */
void AppManager_setAppExecRequest(void);


/**
 * @brief   アプリケーションを実行する
 */
void AppManager_exec(void);

#endif  // __CAMERAMOUNT_APPMANAGER_H__
