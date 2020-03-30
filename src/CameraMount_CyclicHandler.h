/**
 * @file        CameraMount_CyclicHandler.h
 * @brief       カメラマウントコントローラ 周期ハンドラ
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_CYCLICHANDLER_H__
#define __CAMERAMOUNT_CYCLICHANDLER_H__


/**
 * @name    タイマ0の設定
 */
/** @{ */
#define TIMER0_INITIAL_VALUE    61      /**< 5ミリ秒 */
/** @} */


/**
 * @name    周期ハンドラの実行制御
 */
/** @{ */
#define CYCLICHANDLER_SLOT_NUM  4       /**< 実行スロット数 */
/** @} */


/**
 * @brief   周期ハンドラの初期化（タイマ0割込みの初期化）
 */
void CyclicHandler_init(void);


/**
 * @brief   周期ハンドラ処理（タイマ0割込み処理）
 */
void isr_TIMER0(void);

#endif  // __CAMERAMOUNT_CYCLICHANDLER_H__
