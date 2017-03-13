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
 * @name    システムコマンド
 */
/*! @{ */
#define SYSTEM_COMMAND_LENGTH_MAX               6       /*!< 最大コマンド長 */
#define SYSTEM_COMMAND_MASK_OPCODE              0xF0    /*!< コマンドマスク: オペコード */
#define SYSTEM_COMMAND_MASK_LENGTH              0x0F    /*!< コマンドマスク: コマンド長 */
#define SYSTEM_COMMAND_RESET                    0x0     /*!< オペコード: ソフトウェアリセット */
#define SYSTEM_COMMAND_INITIALIZE               0x1     /*!< オペコード: システム初期化 */
#define SYSTEM_COMMAND_GET_VERSION              0x2     /*!< オペコード: バージョン情報取得 */
#define SYSTEM_COMMAND_READ_REGISTER            0x4     /*!< オペコード: レジスタ読込み */
#define SYSTEM_COMMAND_WRITE_REGISTER           0x5     /*!< オペコード: レジスタ書込み */
#define SYSTEM_COMMAND_READ_EEPROM              0x6     /*!< オペコード: EEPROM読込み */
#define SYSTEM_COMMAND_WRITE_EEPROM             0x7     /*!< オペコード: EEPROM書込み */
/*! @} */


/**
 * @name    システムレスポンス
 */
/*! @{ */
#define SYSTEM_RESPONSE_LENGTH_MAX              6       /*!< 最大レスポンス長 */
/*! @} */


/**
 * @name    システムステータス
 */
/*! @{ */
#define SYSTEM_STATUS_WDT_TIMEOUT               0x01    /*!< ウォッチドッグタイムアウト */
#define SYSTEM_STATUS_COM_TIMEOUT               0x02    /*!< 通信タイムアウト */
/*! @} */


/**
 * @name    システムエラー
 */
/*! @{ */
#define SYSTEM_ERROR_INVALID_COMMAND            0x01    /*!< 無効なコマンド */
/*! @} */


/**
 * @enum    system_state_e
 * @brief   カメラマウントコントローラのシステムステート
 */
enum system_state_e {
    SYSTEM_INITIALIZATION = 0,  /*!< 初期化中 */
    SYSTEM_RUN,                 /*!< 動作中 */
    SYSTEM_HALT,                /*!< 停止中 */
    SYSTEM_STATE_E_NUM          /*!< CMS_STATE_E_NUMの列挙数 */
};


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
 * @brief   システムエラーを取得する
 * @return          システムエラー
 */
#inline
uint8_t System_getError(void);


/**
 * @brief   システムを初期化する
 */
void System_init(void);


/**
 * @brief   システムタスクを実行する
 */
void System_execTask(void);

#endif  // __CAMERAMOUNT_SYSTEM_H__
