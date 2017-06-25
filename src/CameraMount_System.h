/**
 * @file        CameraMount_System.h
 * @brief       カメラマウントコントローラ システム制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_SYSTEM_H__
#define __CAMERAMOUNT_SYSTEM_H__


/**
 * @name    システムステータスフラグ
 */
/*! @{ */
#define SYSTEM_STATUS_WDT_TIMEOUT               0x01    /*!< ウォッチドッグタイムアウト */
#define SYSTEM_STATUS_COM_TIMEOUT               0x02    /*!< 通信タイムアウト */
/*! @} */


/**
 * @name    システムエラーフラグ
 */
/*! @{ */
#define SYSTEM_ERROR_INVALID_COMMAND            0x01    /*!< 無効なコマンド */
/*! @} */


/**
 * @name    カメラマウントコントローラのシステムステート
 */
/*! @{ */
#define SYSTEM_INITIALIZATION                   0       /*!< 初期化中 */
#define SYSTEM_RUN                              1       /*!< 動作中 */
#define SYSTEM_HALT                             2       /*!< 停止中 */
#define SYSTEM_STATE_NUM                        3       /*!< システムステートの数 */
/*! @} */


/**
 * @brief   現在のシステムステートを取得する
 * @return          現在のシステムステート
 */
#inline
uint8_t System_getState(void);


/**
 * @brief   システムステータスを取得する
 * @return          システムステータス
 */
#inline
uint8_t System_getStatus(void);


/**
 * @brief   システムステータスフラグをセットする
 * @param[in]       system_status_flag  システムステータスフラグ
 */
void System_setStatus(uint8_t system_status_flag);


/**
 * @brief   システムエラーを取得する
 * @return          システムエラー
 */
#inline
uint8_t System_getError(void);


/**
 * @brief   システムエラーフラグをセットする
 * @param[in]       system_error_flag   システムエラーフラグ
 */
void System_setError(uint8_t system_error_flag);


/**
 * @brief   システム初期化要求をセットする
 */
void System_setInitializationRequest(void);


/**
 * @brief   システム初期化要求をクリアする
 */
void System_clearInitializationRequest(void);


/**
 * @brief   システム制御を初期化する
 */
void System_init(void);


/**
 * @brief   システム制御タスクを実行する
 */
void System_execTask(void);

#endif  // __CAMERAMOUNT_SYSTEM_H__
