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
 * @name    レジスタデータサイズ
 */
/** @{ */
#define REGISTER_SIZE_SYSTEM_STATE                              1       /**< システムステート */
#define REGISTER_SIZE_SYSTEM_STATUS                             1       /**< システムステータス */
#define REGISTER_SIZE_SYSTEM_ERROR                              1       /**< システムエラー */
#define REGISTER_SIZE_SERVO_CTRL_MODE                           1       /**< サーボ制御モード */
#define REGISTER_SIZE_SERVO_POSITION_FACTOR                     1       /**< サーボ角度位置変換係数 */
#define REGISTER_SIZE_PAN_SERVO_REQUEST_ANGLE                   2       /**< 水平方向用サーボ，指示角度 */
#define REGISTER_SIZE_PAN_SERVO_REQUEST_POSITION                2       /**< 水平方向用サーボ，指示位置 */
#define REGISTER_SIZE_PAN_SERVO_NEUTRAL_POSITION                2       /**< 水平方向用サーボ，ニュートラル位置 */
#define REGISTER_SIZE_PAN_SERVO_MIN_POSITION                    2       /**< 水平方向用サーボ，最小位置 */
#define REGISTER_SIZE_PAN_SERVO_MAX_POSITION                    2       /**< 水平方向用サーボ，最大位置 */
#define REGISTER_SIZE_TILT_SERVO_REQUEST_ANGLE                  2       /**< 垂直方向用サーボ，指示角度 */
#define REGISTER_SIZE_TILT_SERVO_REQUEST_POSITION               2       /**< 垂直方向用サーボ，指示位置 */
#define REGISTER_SIZE_TILT_SERVO_NEUTRAL_POSITION               2       /**< 垂直方向用サーボ，ニュートラル位置 */
#define REGISTER_SIZE_TILT_SERVO_MIN_POSITION                   2       /**< 垂直方向用サーボ，最小位置 */
#define REGISTER_SIZE_TILT_SERVO_MAX_POSITION                   2       /**< 垂直方向用サーボ，最大位置 */
#define REGISTER_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT       1       /**< ステータスLEDの点滅周期，通信タイムアウト */
#define REGISTER_SIZE_ERROR_LED_BRINK_PERIOD                    1       /**< エラーLEDの点滅周期 */
#define REGISTER_SIZE_COM_TIMEOUT_LIMIT                         1       /**< 通信タイムアウト検出時間 */
/** @} */


/**
 * @name    レジスタインデックス
 */
/** @{ */
#define REGISTER_SYSTEM_STATE                                   0       /**< システムステート */
#define REGISTER_SYSTEM_STATUS                                  1       /**< システムステータス */
#define REGISTER_SYSTEM_ERROR                                   2       /**< システムエラー */
#define REGISTER_SERVO_CTRL_MODE                                3       /**< サーボ制御モード */
#define REGISTER_SERVO_POSITION_FACTOR                          4       /**< サーボ角度位置変換係数 */
#define REGISTER_PAN_SERVO_REQUEST_ANGLE                        5       /**< 水平方向用サーボ，指示角度 */
#define REGISTER_PAN_SERVO_REQUEST_POSITION                     6       /**< 水平方向用サーボ，指示位置 */
#define REGISTER_PAN_SERVO_NEUTRAL_POSITION                     7       /**< 水平方向用サーボ，ニュートラル位置 */
#define REGISTER_PAN_SERVO_MIN_POSITION                         8       /**< 水平方向用サーボ，最小位置 */
#define REGISTER_PAN_SERVO_MAX_POSITION                         9       /**< 水平方向用サーボ，最大位置 */
#define REGISTER_TILT_SERVO_REQUEST_ANGLE                       10      /**< 垂直方向用サーボ，指示角度 */
#define REGISTER_TILT_SERVO_REQUEST_POSITION                    11      /**< 垂直方向用サーボ，指示位置 */
#define REGISTER_TILT_SERVO_NEUTRAL_POSITION                    12      /**< 垂直方向用サーボ，ニュートラル位置 */
#define REGISTER_TILT_SERVO_MIN_POSITION                        13      /**< 垂直方向用サーボ，最小位置 */
#define REGISTER_TILT_SERVO_MAX_POSITION                        14      /**< 垂直方向用サーボ，最大位置 */
#define REGISTER_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT            15      /**< ステータスLEDの点滅周期，通信タイムアウト */
#define REGISTER_ERROR_LED_BRINK_PERIOD                         16      /**< エラーLEDの点滅周期 */
#define REGISTER_COM_TIMEOUT_LIMIT                              17      /**< 通信タイムアウト検出時間 */
#define REGISTER_INDEX_NUM                                      18      /**< レジスタインデックスの数 */
/** @} */


/**
 * @struct  register_st
 * @brief   レジスタ設定構造体
 */
struct register_st {
    uint8_t *addr;              /**< レジスタアドレス */
    uint8_t size;               /**< レジスタデータサイズ */
    bool write_enable;          /**< レジスタライトイネーブル */
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
