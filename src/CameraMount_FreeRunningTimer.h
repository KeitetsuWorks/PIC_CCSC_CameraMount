/**
 * @file        CameraMount_FreeRunningTimer.h
 * @brief       カメラマウントコントローラ フリーランニングタイマ
 * @author      Keitetsu
 * @date        2017/05/02
 * @copyright   Copyright (c) 2017 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_FREERUNNINGTIMER_H__
#define __CAMERAMOUNT_FREERUNNINGTIMER_H__


/**
 * @name    1秒タイマの設定
 */
/*! @{ */
#define TIMER_1S_PERIOD         200     /*!< 5ミリ秒 * 200 = 1秒 */
/*! @} */


/**
 * @struct  timer_5ms_st
 * @brief   タイマ状態管理構造体（5ミリ秒）
 */
struct timer_5ms_st {
    bool status;            /*!< タイマ状態 */
    uint8_t start;          /*!< タイマ開始時間 */
};


/**
 * @struct  timer_1s_st
 * @brief   タイマ状態管理構造体（1秒）
 */
struct timer_1s_st {
    bool status;            /*!< タイマ状態 */
    uint8_t start;          /*!< タイマ開始時間 */
};


/**
 * @brief   フリーランニングタイマの初期化
 */
void FreeRunningTimer_init(void);


/**
 * @brief   フリーランニングタイマの更新
 */
void FreeRunningTimer_count(void);


/**
 * @brief   フリーランニングタイマ（5ミリ秒）の初期化
 */
void FreeRunningTimer_5ms_init(void);


/**
 * @brief   フリーランニングタイマ（5ミリ秒）の更新
 */
#inline
void FreeRunningTimer_5ms_count(void);


/**
 * @brief   タイムアウトの判定（5ミリ秒）
 * @param[in,out]   timer           タイマ状態管理構造体（5ミリ秒）
 * @param[in]       enable          タイマイネーブル
 * @param[in]       period          タイムアウト時間
 * @retval          FALSE           タイムアウトなし
 * @retval          TRUE            タイムアウト発生
 */
#inline
bool FreeRunningTimer_5ms_isTimeout(struct timer_5ms_st *timer, bool enable, uint8_t period);


/**
 * @brief   フリーランニングタイマ（1秒）の初期化
 */
void FreeRunningTimer_1s_init(void);


/**
 * @brief   フリーランニングタイマ（1秒）の更新
 */
#inline
void FreeRunningTimer_1s_count(void);


/**
 * @brief   タイムアウトの判定（1秒）
 * @param[in,out]   timer           タイマ状態管理構造体（1秒）
 * @param[in]       enable          タイマイネーブル
 * @param[in]       period          タイムアウト時間
 * @retval          FALSE           タイムアウトなし
 * @retval          TRUE            タイムアウト発生
 */
#inline
bool FreeRunningTimer_1s_isTimeout(struct timer_1s_st *timer, bool enable, uint8_t period);

#endif  // __CAMERAMOUNT_FREERUNNINGTIMER_H__
