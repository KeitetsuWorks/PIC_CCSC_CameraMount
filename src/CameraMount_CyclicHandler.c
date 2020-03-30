/**
 * @file        CameraMount_CyclicHandler.c
 * @brief       カメラマウントコントローラ 周期ハンドラ
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "CameraMount_CyclicHandler.h"
#include "CameraMount_FreeRunningTimer.h"


/**
 * @name    周期ハンドラの実行制御
 */
/** @{ */
uint8_t CyclicHandler_slot;             /**< 実行スロット番号 */
/** @} */


void CyclicHandler_init(void)
{
    CyclicHandler_slot = 0;
    
    // ペリフェラル設定
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_128);
    
    // タイマ0の開始
    set_timer0(TIMER0_INITIAL_VALUE);
    
    // 割込み設定
    enable_interrupts(INT_RTCC);
    
    return;
}


#int_RTCC
void isr_TIMER0(void)
{
    // タイマ0の再開
    set_timer0(TIMER0_INITIAL_VALUE);
    
    // ウォッチドッグタイマの再開
    restart_wdt();
    
    // タスクの実行
    switch (CyclicHandler_slot) {
        case 0:
            // アプリケーション実行要求をセット
            AppManager_setAppExecRequest();
            
            // フリーランニングタイマの更新
            FreeRunningTimer_count();
            break;
        case 1:
            // アプリケーション実行要求をセット
            AppManager_setAppExecRequest();
            
            // フリーランニングタイマの更新
            FreeRunningTimer_count();
            break;
        case 2:
            // アプリケーション実行要求をセット
            AppManager_setAppExecRequest();
            
            // フリーランニングタイマの更新
            FreeRunningTimer_count();
            break;
        case 3:
            // アプリケーション実行要求をセット
            AppManager_setAppExecRequest();
            
            // フリーランニングタイマの更新
            FreeRunningTimer_count();
            break;
        default:
            break;
    }
    
    CyclicHandler_slot++;
    if (CyclicHandler_slot >= CYCLICHANDLER_SLOT_NUM) {
        CyclicHandler_slot = 0;
    }
    
    return;
}
