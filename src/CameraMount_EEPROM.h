/**
 * @file        CameraMount_EEPROM.h
 * @brief       カメラマウントコントローラ EEPROM制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_EEPROM_H__
#define __CAMERAMOUNT_EEPROM_H__


/**
 * @name    EEPROMアドレス
 */
/*! @{ */
#define EEPROM_ADDR_SERVO_INITIAL_CTRL_MODE                     0x00    /*!< サーボ制御モード，初期モード */
#define EEPROM_ADDR_SERVO_POSITION_FACTOR                       0x01    /*!< サーボ角度位置変換係数 */
#define EEPROM_ADDR_PAN_SERVO_INITIAL_ANGLE_L                   0x02    /*!< 水平方向用サーボ，初期角度，下位8bit */
#define EEPROM_ADDR_PAN_SERVO_INITIAL_ANGLE_H                   0x03    /*!< 水平方向用サーボ，初期角度，上位8bit */
#define EEPROM_ADDR_PAN_SERVO_NEUTRAL_POSITION_L                0x04    /*!< 水平方向用サーボ，ニュートラル位置，下位8bit */
#define EEPROM_ADDR_PAN_SERVO_NEUTRAL_POSITION_H                0x05    /*!< 水平方向用サーボ，ニュートラル位置，上位8bit */
#define EEPROM_ADDR_PAN_SERVO_MIN_POSITION_L                    0x06    /*!< 水平方向用サーボ，最小位置，下位8bit */
#define EEPROM_ADDR_PAN_SERVO_MIN_POSITION_H                    0x07    /*!< 水平方向用サーボ，最小位置，上位8bit */
#define EEPROM_ADDR_PAN_SERVO_MAX_POSITION_L                    0x08    /*!< 水平方向用サーボ，最大位置，下位8bit */
#define EEPROM_ADDR_PAN_SERVO_MAX_POSITION_H                    0x09    /*!< 水平方向用サーボ，最大位置，上位8bit */
#define EEPROM_ADDR_TILT_SERVO_INITIAL_ANGLE_L                  0x0A    /*!< 垂直方向用サーボ，初期角度，下位8bit */
#define EEPROM_ADDR_TILT_SERVO_INITIAL_ANGLE_H                  0x0B    /*!< 垂直方向用サーボ，初期角度，上位8bit */
#define EEPROM_ADDR_TILT_SERVO_NEUTRAL_POSITION_L               0x0C    /*!< 垂直方向用サーボ，ニュートラル位置，下位8bit */
#define EEPROM_ADDR_TILT_SERVO_NEUTRAL_POSITION_H               0x0D    /*!< 垂直方向用サーボ，ニュートラル位置，上位8bit */
#define EEPROM_ADDR_TILT_SERVO_MIN_POSITION_L                   0x0E    /*!< 垂直方向用サーボ，最小位置，下位8bit */
#define EEPROM_ADDR_TILT_SERVO_MIN_POSITION_H                   0x0F    /*!< 垂直方向用サーボ，最小位置，上位8bit */
#define EEPROM_ADDR_TILT_SERVO_MAX_POSITION_L                   0x10    /*!< 垂直方向用サーボ，最大位置，下位8bit */
#define EEPROM_ADDR_TILT_SERVO_MAX_POSITION_H                   0x11    /*!< 垂直方向用サーボ，最大位置，上位8bit */
#define EEPROM_ADDR_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         0x12    /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_ADDR_ERROR_LED_BRINK_PERIOD                      0x13    /*!< エラーLEDの点滅周期 */
#define EEPROM_ADDR_COM_TIMEOUT_LIMIT                           0x14    /*!< 通信タイムアウト検出時間 */
/*! @} */


/**
 * @name    EEPROMデータ初期値
 */
/*! @{ */
#define EEPROM_INIT_SERVO_INITIAL_CTRL_MODE                     0x01    /*!< サーボ制御モード，初期モード */
#define EEPROM_INIT_SERVO_POSITION_FACTOR                       0x06    /*!< サーボ角度位置変換係数 */
#define EEPROM_INIT_PAN_SERVO_INITIAL_ANGLE_L                   0x00    /*!< 水平方向用サーボ，初期角度，下位8bit */
#define EEPROM_INIT_PAN_SERVO_INITIAL_ANGLE_H                   0x00    /*!< 水平方向用サーボ，初期角度，上位8bit */
#define EEPROM_INIT_PAN_SERVO_NEUTRAL_POSITION_L                0x40    /*!< 水平方向用サーボ，ニュートラル位置，下位8bit */
#define EEPROM_INIT_PAN_SERVO_NEUTRAL_POSITION_H                0xEB    /*!< 水平方向用サーボ，ニュートラル位置，上位8bit */
#define EEPROM_INIT_PAN_SERVO_MIN_POSITION_L                    0x4C    /*!< 水平方向用サーボ，最小位置，下位8bit */
#define EEPROM_INIT_PAN_SERVO_MIN_POSITION_H                    0xE9    /*!< 水平方向用サーボ，最小位置，上位8bit */
#define EEPROM_INIT_PAN_SERVO_MAX_POSITION_L                    0x34    /*!< 水平方向用サーボ，最大位置，下位8bit */
#define EEPROM_INIT_PAN_SERVO_MAX_POSITION_H                    0xED    /*!< 水平方向用サーボ，最大位置，上位8bit */
#define EEPROM_INIT_TILT_SERVO_INITIAL_ANGLE_L                  0x00    /*!< 垂直方向用サーボ，初期角度，下位8bit */
#define EEPROM_INIT_TILT_SERVO_INITIAL_ANGLE_H                  0x00    /*!< 垂直方向用サーボ，初期角度，上位8bit */
#define EEPROM_INIT_TILT_SERVO_NEUTRAL_POSITION_L               0x40    /*!< 垂直方向用サーボ，ニュートラル位置，下位8bit */
#define EEPROM_INIT_TILT_SERVO_NEUTRAL_POSITION_H               0xEB    /*!< 垂直方向用サーボ，ニュートラル位置，上位8bit */
#define EEPROM_INIT_TILT_SERVO_MIN_POSITION_L                   0x4C    /*!< 垂直方向用サーボ，最小位置，下位8bit */
#define EEPROM_INIT_TILT_SERVO_MIN_POSITION_H                   0xE9    /*!< 垂直方向用サーボ，最小位置，上位8bit */
#define EEPROM_INIT_TILT_SERVO_MAX_POSITION_L                   0x34    /*!< 垂直方向用サーボ，最大位置，下位8bit */
#define EEPROM_INIT_TILT_SERVO_MAX_POSITION_H                   0xED    /*!< 垂直方向用サーボ，最大位置，上位8bit */
#define EEPROM_INIT_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         200     /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_INIT_ERROR_LED_BRINK_PERIOD                      100     /*!< エラーLEDの点滅周期 */
#define EEPROM_INIT_COM_TIMEOUT_LIMIT                           60      /*!< 通信タイムアウト検出時間 */
/*! @} */


/**
 * @name    EEPROMデータサイズ
 */
/*! @{ */
#define EEPROM_SIZE_MAX                                         4       /*!< 最大サイズ */
#define EEPROM_SIZE_SERVO_INITIAL_CTRL_MODE                     1       /*!< サーボ制御モード，初期モード */
#define EEPROM_SIZE_SERVO_POSITION_FACTOR                       1       /*!< サーボ角度位置変換係数 */
#define EEPROM_SIZE_PAN_SERVO_INITIAL_ANGLE                     2       /*!< 水平方向用サーボ，初期角度 */
#define EEPROM_SIZE_PAN_SERVO_NEUTRAL_POSITION                  2       /*!< 水平方向用サーボ，ニュートラル位置 */
#define EEPROM_SIZE_PAN_SERVO_MIN_POSITION                      2       /*!< 水平方向用サーボ，最小位置 */
#define EEPROM_SIZE_PAN_SERVO_MAX_POSITION                      2       /*!< 水平方向用サーボ，最大位置 */
#define EEPROM_SIZE_TILT_SERVO_INITIAL_ANGLE                    2       /*!< 垂直方向用サーボ，初期角度 */
#define EEPROM_SIZE_TILT_SERVO_NEUTRAL_POSITION                 2       /*!< 垂直方向用サーボ，ニュートラル位置 */
#define EEPROM_SIZE_TILT_SERVO_MIN_POSITION                     2       /*!< 垂直方向用サーボ，最小位置 */
#define EEPROM_SIZE_TILT_SERVO_MAX_POSITION                     2       /*!< 垂直方向用サーボ，最大位置 */
#define EEPROM_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         1       /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_SIZE_ERROR_LED_BRINK_PERIOD                      1       /*!< エラーLEDの点滅周期 */
#define EEPROM_SIZE_COM_TIMEOUT_LIMIT                           1       /*!< 通信タイムアウト検出時間 */
/*! @} */


/**
 * @name    EEPROMインデックス
 */
/*! @{ */
#define EEPROM_SERVO_INITIAL_CTRL_MODE                          0       /*!< サーボ制御モード，初期モード */
#define EEPROM_SERVO_POSITION_FACTOR                            1       /*!< サーボ角度位置変換係数 */
#define EEPROM_PAN_SERVO_INITIAL_ANGLE                          2       /*!< 水平方向用サーボ，初期角度 */
#define EEPROM_PAN_SERVO_NEUTRAL_POSITION                       3       /*!< 水平方向用サーボ，ニュートラル位置 */
#define EEPROM_PAN_SERVO_MIN_POSITION                           4       /*!< 水平方向用サーボ，最小位置 */
#define EEPROM_PAN_SERVO_MAX_POSITION                           5       /*!< 水平方向用サーボ，最大位置 */
#define EEPROM_TILT_SERVO_INITIAL_ANGLE                         6       /*!< 垂直方向用サーボ，初期角度 */
#define EEPROM_TILT_SERVO_NEUTRAL_POSITION                      7       /*!< 垂直方向用サーボ，ニュートラル位置 */
#define EEPROM_TILT_SERVO_MIN_POSITION                          8       /*!< 垂直方向用サーボ，最小位置 */
#define EEPROM_TILT_SERVO_MAX_POSITION                          9       /*!< 垂直方向用サーボ，最大位置 */
#define EEPROM_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT              10      /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_ERROR_LED_BRINK_PERIOD                           11      /*!< エラーLEDの点滅周期 */
#define EEPROM_COM_TIMEOUT_LIMIT                                12      /*!< 通信タイムアウト検出時間 */
#define EEPROM_INDEX_NUM                                        13      /*!< EEPROMインデックスの数 */
/*! @} */


/**
 * @struct  eeprom_st
 * @brief   EEPROM設定構造体
 */
struct eeprom_st {
    uint8_t addr;               /*!< EEPROMアドレス */
    uint8_t size;               /*!< EEPROMデータサイズ */
    bool write_enable;          /*!< EEPROMライトイネーブル */
};


/*! @cond */
#rom 0x2100={
    EEPROM_INIT_SERVO_INITIAL_CTRL_MODE,
    EEPROM_INIT_SERVO_POSITION_FACTOR,
    EEPROM_INIT_PAN_SERVO_INITIAL_ANGLE_L,
    EEPROM_INIT_PAN_SERVO_INITIAL_ANGLE_H,
    EEPROM_INIT_PAN_SERVO_NEUTRAL_POSITION_L,
    EEPROM_INIT_PAN_SERVO_NEUTRAL_POSITION_H,
    EEPROM_INIT_PAN_SERVO_MIN_POSITION_L,
    EEPROM_INIT_PAN_SERVO_MIN_POSITION_H,
    EEPROM_INIT_PAN_SERVO_MAX_POSITION_L,
    EEPROM_INIT_PAN_SERVO_MAX_POSITION_H,
    EEPROM_INIT_TILT_SERVO_INITIAL_ANGLE_L,
    EEPROM_INIT_TILT_SERVO_INITIAL_ANGLE_H,
    EEPROM_INIT_TILT_SERVO_NEUTRAL_POSITION_L,
    EEPROM_INIT_TILT_SERVO_NEUTRAL_POSITION_H,
    EEPROM_INIT_TILT_SERVO_MIN_POSITION_L,
    EEPROM_INIT_TILT_SERVO_MIN_POSITION_H,
    EEPROM_INIT_TILT_SERVO_MAX_POSITION_L,
    EEPROM_INIT_TILT_SERVO_MAX_POSITION_H,
    EEPROM_INIT_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT,
    EEPROM_INIT_ERROR_LED_BRINK_PERIOD,
    EEPROM_INIT_COM_TIMEOUT_LIMIT
}
/*! @endcond */


/**
 * @brief   EEPROM制御を初期化する
 */
void EEPROM_init(void);


/**
 * @brief   EEPROMデータサイズを取得する
 * @param[in]       index               EEPROMインデックス
 * @return          EEPROMデータサイズ
 */
uint8_t EEPROM_getSize(uint8_t index);


/**
 * @brief   EEPROM読込み処理
 * @param[in]       index               EEPROMインデックス
 * @param[out]      data                EEPROM読込みデータ
 * @return          EEPROM読込みサイズ
 */
uint8_t EEPROM_read(
    uint8_t index,
    void *data);


/**
 * @brief   EEPROMが書込み中か確認する
 * @retval          TRUE                EEPROM書込み中
 * @retval          FALSE               EEPROM書込み開始待機中
 */
#inline
bool EEPROM_isWriting(void);


/**
 * @brief   EEPROM書込み開始処理
 * @param[in]       index               EEPROMインデックス
 * @param[in]       data                EEPROM書込みデータ
 * @retval          TRUE                EEPROM書込み開始成功
 * @retval          FALSE               EEPROM書込み開始失敗
 */
bool EEPROM_write(
    uint8_t index,
    void *data);


/**
 * @brief   EEPROM書込み完了割込み処理
 */
#separate
void isr_EEPROM(void);

#endif  // __CAMERAMOUNT_EEPROM_H__
