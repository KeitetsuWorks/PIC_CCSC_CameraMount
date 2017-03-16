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
#define EEPROM_ADDR_PAN_SERVO_NEUTRAL_POSITION                  0x00    /*!< 水平方向用サーボ，ニュートラル位置 */
#define EEPROM_ADDR_PAN_SERVO_MIN_POSITION                      0x01    /*!< 水平方向用サーボ，最小位置 */
#define EEPROM_ADDR_PAN_SERVO_MAX_POSITION                      0x02    /*!< 水平方向用サーボ，最大位置 */
#define EEPROM_ADDR_TILT_SERVO_NEUTRAL_POSITION                 0x03    /*!< 垂直方向用サーボ，ニュートラル位置 */
#define EEPROM_ADDR_TILT_SERVO_MIN_POSITION                     0x04    /*!< 垂直方向用サーボ，最小位置 */
#define EEPROM_ADDR_TILT_SERVO_MAX_POSITION                     0x05    /*!< 垂直方向用サーボ，最大位置 */
#define EEPROM_ADDR_POWER_LED_BRIGHTNESS_MIN_L                  0x06    /*!< 電源LEDの最小PWMデューティ，下位8bit */
#define EEPROM_ADDR_POWER_LED_BRIGHTNESS_MIN_H                  0x07    /*!< 電源LEDの最小PWMデューティ，上位8bit */
#define EEPROM_ADDR_POWER_LED_BRIGHTNESS_MAX_L                  0x08    /*!< 電源LEDの最大PWMデューティ，下位8bit */
#define EEPROM_ADDR_POWER_LED_BRIGHTNESS_MAX_H                  0x09    /*!< 電源LEDの最大PWMデューティ，上位8bit */
#define EEPROM_ADDR_POWER_LED_BRIGHTNESS_STEP                   0x0A    /*!< 電源LEDのPWMデューティの増減幅 */
#define EEPROM_ADDR_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         0x0B    /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_ADDR_ERROR_LED_BRINK_PERIOD                      0x0C    /*!< エラーLEDの点滅周期 */
#define EEPROM_ADDR_COM_TIMEOUT_LIMIT_L                         0x0D    /*!< 通信タイムアウト検出時間，下位8bit */
#define EEPROM_ADDR_COM_TIMEOUT_LIMIT_H                         0x0E    /*!< 通信タイムアウト検出時間，上位8bit */
/*! @} */


/**
 * @name    EEPROMデータ初期値
 */
/*! @{ */
#define EEPROM_INIT_PAN_SERVO_NEUTRAL_POSITION                  125     /*!< 水平方向用サーボ，ニュートラル位置 */
#define EEPROM_INIT_PAN_SERVO_MIN_POSITION                      47      /*!< 水平方向用サーボ，最小位置 */
#define EEPROM_INIT_PAN_SERVO_MAX_POSITION                      195     /*!< 水平方向用サーボ，最大位置 */
#define EEPROM_INIT_TILT_SERVO_NEUTRAL_POSITION                 125     /*!< 垂直方向用サーボ，ニュートラル位置 */
#define EEPROM_INIT_TILT_SERVO_MIN_POSITION                     47      /*!< 垂直方向用サーボ，最小位置 */
#define EEPROM_INIT_TILT_SERVO_MAX_POSITION                     195     /*!< 垂直方向用サーボ，最大位置 */
#define EEPROM_INIT_POWER_LED_BRIGHTNESS_MIN_L                  0x10    /*!< 電源LEDの最小PWMデューティ，下位8bit */
#define EEPROM_INIT_POWER_LED_BRIGHTNESS_MIN_H                  0x00    /*!< 電源LEDの最小PWMデューティ，上位8bit */
#define EEPROM_INIT_POWER_LED_BRIGHTNESS_MAX_L                  0xFF    /*!< 電源LEDの最大PWMデューティ，下位8bit */
#define EEPROM_INIT_POWER_LED_BRIGHTNESS_MAX_H                  0x01    /*!< 電源LEDの最大PWMデューティ，上位8bit */
#define EEPROM_INIT_POWER_LED_BRIGHTNESS_STEP                   4       /*!< 電源LEDのPWMデューティの増減幅 */
#define EEPROM_INIT_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         50      /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_INIT_ERROR_LED_BRINK_PERIOD                      25      /*!< エラーLEDの点滅周期 */
#define EEPROM_INIT_COM_TIMEOUT_LIMIT_L                         0x70    /*!< 通信タイムアウト検出時間，下位8bit */
#define EEPROM_INIT_COM_TIMEOUT_LIMIT_H                         0x17    /*!< 通信タイムアウト検出時間，上位8bit */
/*! @} */


/**
 * @name    EEPROMデータサイズ
 */
/*! @{ */
#define EEPROM_SIZE_MAX                                         4       /*!< 最大サイズ */
#define EEPROM_SIZE_PAN_SERVO_NEUTRAL_POSITION                  1       /*!< 水平方向用サーボ，ニュートラル位置 */
#define EEPROM_SIZE_PAN_SERVO_MIN_POSITION                      1       /*!< 水平方向用サーボ，最小位置 */
#define EEPROM_SIZE_PAN_SERVO_MAX_POSITION                      1       /*!< 水平方向用サーボ，最大位置 */
#define EEPROM_SIZE_TILT_SERVO_NEUTRAL_POSITION                 1       /*!< 垂直方向用サーボ，ニュートラル位置 */
#define EEPROM_SIZE_TILT_SERVO_MIN_POSITION                     1       /*!< 垂直方向用サーボ，最小位置 */
#define EEPROM_SIZE_TILT_SERVO_MAX_POSITION                     1       /*!< 垂直方向用サーボ，最大位置 */
#define EEPROM_SIZE_POWER_LED_BRIGHTNESS_MIN                    2       /*!< 電源LEDの最小PWMデューティ */
#define EEPROM_SIZE_POWER_LED_BRIGHTNESS_MAX                    2       /*!< 電源LEDの最大PWMデューティ */
#define EEPROM_SIZE_POWER_LED_BRIGHTNESS_STEP                   1       /*!< 電源LEDのPWMデューティの増減幅 */
#define EEPROM_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         1       /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_SIZE_ERROR_LED_BRINK_PERIOD                      1       /*!< エラーLEDの点滅周期 */
#define EEPROM_SIZE_COM_TIMEOUT_LIMIT                           2       /*!< 通信タイムアウト検出時間 */
/*! @} */


/**
 * @name    EEPROMインデックス
 */
/*! @{ */
#define EEPROM_PAN_SERVO_NEUTRAL_POSITION                       0       /*!< 水平方向用サーボ，ニュートラル位置 */
#define EEPROM_PAN_SERVO_MIN_POSITION                           1       /*!< 水平方向用サーボ，最小位置 */
#define EEPROM_PAN_SERVO_MAX_POSITION                           2       /*!< 水平方向用サーボ，最大位置 */
#define EEPROM_TILT_SERVO_NEUTRAL_POSITION                      3       /*!< 垂直方向用サーボ，ニュートラル位置 */
#define EEPROM_TILT_SERVO_MIN_POSITION                          4       /*!< 垂直方向用サーボ，最小位置 */
#define EEPROM_TILT_SERVO_MAX_POSITION                          5       /*!< 垂直方向用サーボ，最大位置 */
#define EEPROM_POWER_LED_BRIGHTNESS_MIN                         6       /*!< 電源LEDの最小PWMデューティ */
#define EEPROM_POWER_LED_BRIGHTNESS_MAX                         7       /*!< 電源LEDの最大PWMデューティ */
#define EEPROM_POWER_LED_BRIGHTNESS_STEP                        8       /*!< 電源LEDのPWMデューティの増減幅 */
#define EEPROM_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT              9       /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_ERROR_LED_BRINK_PERIOD                           10      /*!< エラーLEDの点滅周期 */
#define EEPROM_COM_TIMEOUT_LIMIT                                11      /*!< 通信タイムアウト検出時間 */
#define EEPROM_INDEX_NUM                                        12      /*!< EEPROMインデックスの数 */
/*! @} */


/**
 * @struct  eeprom_t
 * @brief   EEPROM設定構造体
 */
struct eeprom_t {
    uint8_t addr;               /*!< EEPROMアドレス */
    uint8_t size;               /*!< EEPROMデータサイズ */
    bool write_enable;          /*!< EEPROMライトイネーブル */
};


/*! @cond */
#ROM 0x2100={
    EEPROM_INIT_PAN_SERVO_NEUTRAL_POSITION,
    EEPROM_INIT_PAN_SERVO_MIN_POSITION,
    EEPROM_INIT_PAN_SERVO_MAX_POSITION,
    EEPROM_INIT_TILT_SERVO_NEUTRAL_POSITION,
    EEPROM_INIT_TILT_SERVO_MIN_POSITION,
    EEPROM_INIT_TILT_SERVO_MAX_POSITION,
    EEPROM_INIT_POWER_LED_BRIGHTNESS_MIN_L,
    EEPROM_INIT_POWER_LED_BRIGHTNESS_MIN_H,
    EEPROM_INIT_POWER_LED_BRIGHTNESS_MAX_L,
    EEPROM_INIT_POWER_LED_BRIGHTNESS_MAX_H,
    EEPROM_INIT_POWER_LED_BRIGHTNESS_STEP,
    EEPROM_INIT_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT,
    EEPROM_INIT_ERROR_LED_BRINK_PERIOD,
    EEPROM_INIT_COM_TIMEOUT_LIMIT_L,
    EEPROM_INIT_COM_TIMEOUT_LIMIT_H
}
/*! @endcond */


/**
 * @brief   EEPROM制御の初期化
 */
void EEPROM_init(void);


/**
 * @brief   EEPROMデータサイズ取得処理
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
void isr_EEPROM(void);

#endif  // __CAMERAMOUNT_EEPROM_H__
