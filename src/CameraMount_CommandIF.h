/**
 * @file        CameraMount_CommandIF.h
 * @brief       カメラマウントコントローラ コマンドインタフェース
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_COMMANDIF_H__
#define __CAMERAMOUNT_COMMANDIF_H__


/**
 * @brief   コマンドインタフェースを初期化する
 */
void CommandIF_init(void);


/**
 * @brief   コマンドインタフェースタスクを実行する
 */
void CommandIF_execTask(void);

#endif  // __CAMERAMOUNT_COMMANDIF_H__
