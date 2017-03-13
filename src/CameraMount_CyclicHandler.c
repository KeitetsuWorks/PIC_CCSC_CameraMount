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
#include "CameraMount_LED.h"
#include "CameraMount_Servo.h"
#include "CameraMount_System.h"


/**
 * @name    周期ハンドラの実行制御
 */
/*! @{ */
uint8_t CyclicHandler_slot;             /*!< 実行スロット番号 */
/*! @} */


void CyclicHandler_init(void)
{
    CyclicHandler_slot = 0;
    
    // ペリフェラル設定
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
    
    // タイマ1の再開
    set_timer1(TIMER1_INITIAL_VALUE);
    
    // 割込み設定
    enable_interrupts(INT_TIMER1);
    
    return;
}


#int_TIMER1
void isr_TIMER1(void)
{
    // タイマ1の再開
    set_timer1(TIMER1_INITIAL_VALUE);
    
    // ウォッチドッグタイマの再開
    restart_wdt();
    
    // タスクの実行
    switch (CyclicHandler_slot) {
        case 0:
            System_execTask();
            LED_ctrl();
            break;
        case 1:
            PanServo_ctrl();
            break;
        case 2:
            System_execTask();
            break;
        case 3:
            TiltServo_ctrl();
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
