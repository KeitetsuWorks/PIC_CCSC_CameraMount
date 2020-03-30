/**
 * @file        CameraMount_System.c
 * @brief       カメラマウントコントローラ システム制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "CameraMount_System.h"
#include "CameraMount_Version.h"
#include "CameraMount_Register.h"
#include "CameraMount_EEPROM.h"


/**
 * @name    システム管理
 */
/** @{ */
uint8_t System_state;                   /**< 現在のシステムステート */
uint8_t System_status;                  /**< システムステータス */
uint8_t System_error;                   /**< システムエラー */
bool System_initialization_request;     /**< システム初期化要求 */
/** @} */


/**
 * @brief   INITステートのシステムタスクを実行する
 */
static void System_execTask_INITIALIZATION(void);


/**
 * @brief   RUNステートのシステムタスクを実行する
 */
static void System_execTask_RUN(void);


/**
 * @brief   HALTステートのシステムタスクを実行する
 */
static void System_execTask_HALT(void);


#inline
uint8_t System_getState(void)
{
    return System_state;
}


#inline
uint8_t System_getStatus(void)
{
    return System_status;
}


void System_setStatus(uint8_t system_status_flag)
{
    System_status |= system_status_flag;
    
    return;
}


#inline
uint8_t System_getError(void)
{
    return System_error;
}


void System_setError(uint8_t system_error_flag)
{
    System_error |= system_error_flag;
    
    return;
}


void System_setInitializationRequest(void)
{
    System_initialization_request = TRUE;
    
    return;
}


void System_clearInitializationRequest(void)
{
    System_initialization_request = FALSE;
    
    return;
}


void System_init(void)
{
    System_state = SYSTEM_INITIALIZATION;
    
    System_status = 0x00;
    switch (restart_cause()) {
        case WDT_TIMEOUT:
            System_status |= SYSTEM_STATUS_WDT_TIMEOUT;
            break;
        case NORMAL_POWER_UP:
        default:
            break;
    }
    
    System_error = 0x00;
    
    System_initialization_request = TRUE;
    
    return;
}


void System_execTask(void)
{
    switch (System_state) {
        case SYSTEM_INITIALIZATION:
            System_execTask_INITIALIZATION();
            break;
        case SYSTEM_RUN:
            System_execTask_RUN();
            break;
        case SYSTEM_HALT:
            System_execTask_HALT();
            break;
        default:
            break;
    }
    
    return;
}


static void System_execTask_INITIALIZATION(void)
{
    if (System_initialization_request == TRUE) {
        System_state = SYSTEM_INITIALIZATION;
    }
    else if (System_error != 0) {
        System_state = SYSTEM_HALT;
    }
    else {
        System_state = SYSTEM_RUN;
    }
    
    return;
}


static void System_execTask_RUN(void)
{
    if (System_initialization_request == TRUE) {
        System_state = SYSTEM_INITIALIZATION;
    }
    else if (System_error != 0) {
        System_state = SYSTEM_HALT;
    }
    else {
        System_state = SYSTEM_RUN;
    }
    
    return;
}


static void System_execTask_HALT(void)
{
    if (System_initialization_request == TRUE) {
        System_state = SYSTEM_INITIALIZATION;
    }
    else {
        System_state = SYSTEM_HALT;
    }
    
    return;
}
