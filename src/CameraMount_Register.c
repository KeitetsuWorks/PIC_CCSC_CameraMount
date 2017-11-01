/**
 * @file        CameraMount_Register.c
 * @brief       カメラマウントコントローラ レジスタ制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "CameraMount_Register.h"


/**
 * @var     Register_table
 * @brief   レジスタテーブル
 */
const struct register_st Register_table[] = {
    {   (uint8_t *)(&System_state),                         REGISTER_SIZE_SYSTEM_STATE,                         FALSE   },
    {   (uint8_t *)(&System_status),                        REGISTER_SIZE_SYSTEM_STATUS,                        TRUE    },
    {   (uint8_t *)(&System_error),                         REGISTER_SIZE_SYSTEM_ERROR,                         TRUE    },
    {   (uint8_t *)(&Servo_mode),                           REGISTER_SIZE_SERVO_CTRL_MODE,                      TRUE    },
    {   (uint8_t *)(&Servo_position_factor),                REGISTER_SIZE_SERVO_POSITION_FACTOR,                TRUE    },
    {   (uint8_t *)(&(PanServo.request_angle)),             REGISTER_SIZE_PAN_SERVO_REQUEST_ANGLE,              TRUE    },
    {   (uint8_t *)(&(PanServo.request_position)),          REGISTER_SIZE_PAN_SERVO_REQUEST_POSITION,           TRUE    },
    {   (uint8_t *)(&(PanServo.neutral_position)),          REGISTER_SIZE_PAN_SERVO_NEUTRAL_POSITION,           TRUE    },
    {   (uint8_t *)(&(PanServo.min_position)),              REGISTER_SIZE_PAN_SERVO_MIN_POSITION,               TRUE    },
    {   (uint8_t *)(&(PanServo.max_position)),              REGISTER_SIZE_PAN_SERVO_MAX_POSITION,               TRUE    },
    {   (uint8_t *)(&(TiltServo.request_angle)),            REGISTER_SIZE_TILT_SERVO_REQUEST_ANGLE,             TRUE    },
    {   (uint8_t *)(&(TiltServo.request_position)),         REGISTER_SIZE_TILT_SERVO_REQUEST_POSITION,          TRUE    },
    {   (uint8_t *)(&(TiltServo.neutral_position)),         REGISTER_SIZE_TILT_SERVO_NEUTRAL_POSITION,          TRUE    },
    {   (uint8_t *)(&(TiltServo.min_position)),             REGISTER_SIZE_TILT_SERVO_MIN_POSITION,              TRUE    },
    {   (uint8_t *)(&(TiltServo.max_position)),             REGISTER_SIZE_TILT_SERVO_MAX_POSITION,              TRUE    },
    {   (uint8_t *)(&StatusLED_brink_period_COM_TIMEOUT),   REGISTER_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT,  TRUE    },
    {   (uint8_t *)(&ErrorLED_brink_period),                REGISTER_SIZE_ERROR_LED_BRINK_PERIOD,               TRUE    },
    {   (uint8_t *)(&com_timeout_limit),                    REGISTER_SIZE_COM_TIMEOUT_LIMIT,                    TRUE    }
};


uint8_t Register_getSize(uint8_t index)
{
    uint8_t size;
    
    size = 0;
    
    if (index < REGISTER_INDEX_NUM) {
        size = Register_table[index].size;
    }
    
    return size;
}


uint8_t Register_read(
    uint8_t index,
    void *data)
{
    uint8_t *read_addr;
    uint8_t *read_buffer;
    uint8_t read_count;
    
    read_buffer = (uint8_t *)data;
    read_count = 0;
    
    if (index < REGISTER_INDEX_NUM) {
        read_addr = Register_table[index].addr;
        while (read_count < Register_table[index].size) {
            *read_buffer = *read_addr;
            read_addr++;
            read_buffer++;
            read_count++;
        }
    }
    
    return read_count;
}


uint8_t Register_write(
    uint8_t index,
    void *data)
{
    uint8_t *write_addr;
    uint8_t *write_data;
    uint8_t write_count;
    
    disable_interrupts(GLOBAL);
    
    write_data = (uint8_t *)data;
    write_count = 0;
    
    if ((index < REGISTER_INDEX_NUM) && (Register_table[index].write_enable == TRUE)) {
        write_addr = Register_table[index].addr;
        while (write_count < Register_table[index].size) {
            *write_addr = *write_data;
            write_data++;
            write_addr++;
            write_count++;
        }
    }
    
    enable_interrupts(GLOBAL);
    
    return write_count;
}
