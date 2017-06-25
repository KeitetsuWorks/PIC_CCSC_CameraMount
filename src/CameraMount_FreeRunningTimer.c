/**
 * @file        CameraMount_FreeRunningTimer.c
 * @brief       カメラマウントコントローラ フリーランニングタイマ
 * @author      Keitetsu
 * @date        2017/05/02
 * @copyright   Copyright (c) 2017 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "CameraMount_FreeRunningTimer.h"


/**
 * @name    フリーランニングタイマ
 */
/*! @{ */
static uint8_t FreeRunningTimer_5ms;            /*!< フリーランニングタイマ（5ミリ秒） */
static uint8_t FreeRunningTimer_1s;             /*!< フリーランニングタイマ（1秒） */
/*! @} */


/**
 * @name    1秒タイマ
 */
/*! @{ */
static struct timer_5ms_t timer_1s;             /*!< 1秒タイマ */
/*! @} */


void FreeRunningTimer_init(void)
{
    FreeRunningTimer_5ms_init();
    FreeRunningTimer_1s_init();
    
    return;
}


void FreeRunningTimer_count(void)
{
    FreeRunningTimer_5ms_count();
    FreeRunningTimer_1s_count();
    
    return;
}


void FreeRunningTimer_5ms_init(void)
{
    FreeRunningTimer_5ms = 0;
    
    return;
}


#inline
void FreeRunningTimer_5ms_count(void)
{
    FreeRunningTimer_5ms++;
    
    return;
}


#inline
bool FreeRunningTimer_5ms_isTimeout(struct timer_5ms_t *timer, bool enable, uint8_t period)
{
    bool timeout;
    uint8_t interval;
    
    timeout = FALSE;
    
    if (enable == TRUE) {
        if (timer->status == TRUE) {
            interval = FreeRunningTimer_5ms - timer->start;
            if (interval >= period) {
                timeout = TRUE;
            }
        }
        else {
            timer->status = TRUE;
            timer->start = FreeRunningTimer_5ms;
        }
    }
    else {
        timer->status = FALSE;
        timer->start = 0;
    }
    
    return timeout;
}


void FreeRunningTimer_1s_init(void)
{
    FreeRunningTimer_5ms_isTimeout(&timer_1s, FALSE, TIMER_1S_PERIOD);
    
    FreeRunningTimer_1s = 0;
    FreeRunningTimer_5ms_isTimeout(&timer_1s, TRUE, TIMER_1S_PERIOD);
    
    return;
}


#inline
void FreeRunningTimer_1s_count(void)
{
    bool retval;
    
    retval = FreeRunningTimer_5ms_isTimeout(&timer_1s, TRUE, TIMER_1S_PERIOD);
    if (retval == TRUE){
        FreeRunningTimer_5ms_isTimeout(&timer_1s, FALSE, TIMER_1S_PERIOD);
        
        FreeRunningTimer_1s++;
        FreeRunningTimer_5ms_isTimeout(&timer_1s, TRUE, TIMER_1S_PERIOD);
    }
    
    return;
}


#inline
bool FreeRunningTimer_1s_isTimeout(struct timer_1s_t *timer, bool enable, uint8_t period)
{
    bool timeout;
    uint8_t interval;
    
    timeout = FALSE;
    
    if (enable == TRUE) {
        if (timer->status == TRUE) {
            interval = FreeRunningTimer_1s - timer->start;
            if (interval >= period) {
                timeout = TRUE;
            }
        }
        else {
            timer->status = TRUE;
            timer->start = FreeRunningTimer_1s;
        }
    }
    else {
        timer->status = FALSE;
        timer->start = 0;
    }
    
    return timeout;
}
