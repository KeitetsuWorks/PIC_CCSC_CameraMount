/**
 * @file        CameraMount_AppManager.c
 * @brief       カメラマウントコントローラ アプリケーションマネージャ
 * @author      Keitetsu
 * @date        2016/05/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "CameraMount_AppManager.h"
#include "CameraMount_System.h"
#include "CameraMount_CyclicHandler.h"
#include "CameraMount_FreeRunningTimer.h"
#include "CameraMount_LED.h"
#include "CameraMount_Servo.h"
#include "CameraMount_CommandIF.h"


/**
 * @name    アプリケーションマネージャ
 */
/*! @{ */
bool app_exec_request;                  /*!< アプリケーション実行要求 */
/*! @} */


void AppManager_init(void)
{
    app_exec_request = TRUE;
    
    return;
}


void AppManager_setAppExecRequest(void)
{
    app_exec_request = TRUE;
    
    return;
}


void AppManager_exec(void)
{
    if (app_exec_request == TRUE) {
        // アプリケーション実行要求をクリアする
        app_exec_request = FALSE;
        
        // システム制御タスク
        System_execTask();
        
        switch (System_getState()) {
            case SYSTEM_INITIALIZATION:
                // 割込み無効化
                disable_interrupts(GLOBAL);
                
                // 周期ハンドラの初期化
                CyclicHandler_init();
                
                // 周期実行アプリケーションの初期化
                FreeRunningTimer_init();
                
                // デバイス制御（システムステート依存）の初期化
                LED_init();
                Servo_init();
                
                // アプリケーションの初期化
                CommandIF_init();
                
                // 割込み有効化
                enable_interrupts(GLOBAL);
                
                // システム初期化完了
                System_clearInitializationRequest();
                break;
            case SYSTEM_RUN:
                // デバイス制御（システムステート依存）の実行
                LED_ctrl();
                
                // アプリケーションの実行
                CommandIF_execTask();
                break;
            case SYSTEM_HALT:
                // デバイス制御の実行
                LED_ctrl();
                
                // アプリケーションの実行
                CommandIF_execTask();
                break;
            default:
                break;
        }
    }
    
    return;
}
