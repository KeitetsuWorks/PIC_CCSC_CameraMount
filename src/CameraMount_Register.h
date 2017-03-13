/**
 * @file        CameraMount_Register.h
 * @brief       カメラマウントコントローラ レジスタ制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_REGISTER_H__
#define __CAMERAMOUNT_REGISTER_H__


/**
 * @enum    register_index_e
 * @brief   レジスタインデックス
 */
/*! @{ */
enum register_index_e {
    REGISTER_SYSTEM_STATE = 0x00,                           /*!< 現在のシステムステート */
    REGISTER_SYSTEM_STATUS,                                 /*!< システムステータス */
    REGISTER_SYSTEM_ERROR,                                  /*!< システムエラー */
    REGISTER_PAN_SERVO_REQUEST_POSITION,                    /*!< 水平方向用サーボ，指示位置 */
    REGISTER_PAN_SERVO_NEUTRAL_POSITION,                    /*!< 水平方向用サーボ，ニュートラル位置 */
    REGISTER_PAN_SERVO_MIN_POSITION,                        /*!< 水平方向用サーボ，最小位置 */
    REGISTER_PAN_SERVO_MAX_POSITION,                        /*!< 水平方向用サーボ，最大位置 */
    REGISTER_TILT_SERVO_REQUEST_POSITION,                   /*!< 垂直方向用サーボ，指示位置 */
    REGISTER_TILT_SERVO_NEUTRAL_POSITION,                   /*!< 垂直方向用サーボ，ニュートラル位置 */
    REGISTER_TILT_SERVO_MIN_POSITION,                       /*!< 垂直方向用サーボ，最小位置 */
    REGISTER_TILT_SERVO_MAX_POSITION,                       /*!< 垂直方向用サーボ，最大位置 */
    REGISTER_POWER_LED_BRIGHTNESS_MIN,                      /*!< 電源LEDの最小PWMデューティ */
    REGISTER_POWER_LED_BRIGHTNESS_MAX,                      /*!< 電源LEDの最大PWMデューティ */
    REGISTER_POWER_LED_BRIGHTNESS_STEP,                     /*!< 電源LEDのPWMデューティの増減幅 */
    REGISTER_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT,           /*!< ステータスLEDの点滅周期，通信タイムアウト */
    REGISTER_ERROR_LED_BRINK_PERIOD,                        /*!< エラーLEDの点滅周期 */
    REGISTER_COM_TIMEOUT_LIMIT,                             /*!< 通信タイムアウト検出時間 */
    REGISTER_INDEX_E_NUM                                    /*!< register_index_eの列挙数 */
};
/*! @} */


/**
 * @struct  register_t
 * @brief   レジスタ設定構造体
 */
struct register_t {
    uint8_t *addr;              /*!< レジスタアドレス */
    uint8_t size;               /*!< レジスタデータサイズ */
    bool write_enable;          /*!< レジスタライトイネーブル */
};


/**
 * @brief   レジスタデータサイズ取得処理
 * @param[in]       index               レジスタインデックス
 * @return          レジスタデータサイズ
 */
uint8_t Register_getSize(uint8_t index);


/**
 * @brief   レジスタ読込み処理
 * @param[in]       index               レジスタインデックス
 * @param[out]      data                レジスタ読込みデータ
 * @return          レジスタ読込みサイズ
 */
uint8_t Register_read(
    uint8_t index,
    void *data);


/**
 * @brief   レジスタ書込み処理
 * @param[in]       index               レジスタインデックス
 * @param[in]       data                レジスタ書込みデータ
 * @return          レジスタ書込みサイズ
 */
uint8_t Register_write(
    uint8_t index,
    void *data);

#endif  // __CAMERAMOUNT_REGISTER_H__
