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
 * @name    レジスタインデックス
 */
/*! @{ */
#define REGISTER_SYSTEM_STATE                                   0       /*!< 現在のシステムステート */
#define REGISTER_SYSTEM_STATUS                                  1       /*!< システムステータス */
#define REGISTER_SYSTEM_ERROR                                   2       /*!< システムエラー */
#define REGISTER_PAN_SERVO_REQUEST_POSITION                     3       /*!< 水平方向用サーボ，指示位置 */
#define REGISTER_PAN_SERVO_NEUTRAL_POSITION                     4       /*!< 水平方向用サーボ，ニュートラル位置 */
#define REGISTER_PAN_SERVO_MIN_POSITION                         5       /*!< 水平方向用サーボ，最小位置 */
#define REGISTER_PAN_SERVO_MAX_POSITION                         6       /*!< 水平方向用サーボ，最大位置 */
#define REGISTER_TILT_SERVO_REQUEST_POSITION                    7       /*!< 垂直方向用サーボ，指示位置 */
#define REGISTER_TILT_SERVO_NEUTRAL_POSITION                    8       /*!< 垂直方向用サーボ，ニュートラル位置 */
#define REGISTER_TILT_SERVO_MIN_POSITION                        9       /*!< 垂直方向用サーボ，最小位置 */
#define REGISTER_TILT_SERVO_MAX_POSITION                        10      /*!< 垂直方向用サーボ，最大位置 */
#define REGISTER_POWER_LED_BRIGHTNESS_MIN                       11      /*!< 電源LEDの最小PWMデューティ */
#define REGISTER_POWER_LED_BRIGHTNESS_MAX                       12      /*!< 電源LEDの最大PWMデューティ */
#define REGISTER_POWER_LED_BRIGHTNESS_STEP                      13      /*!< 電源LEDのPWMデューティの増減幅 */
#define REGISTER_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT            14      /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define REGISTER_ERROR_LED_BRINK_PERIOD                         15      /*!< エラーLEDの点滅周期 */
#define REGISTER_COM_TIMEOUT_LIMIT                              16      /*!< 通信タイムアウト検出時間 */
#define REGISTER_INDEX_NUM                                      17      /*!< レジスタインデックスの数 */
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
