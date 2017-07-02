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
const struct register_t Register_table[] = {
    {   (uint8_t *)(&System_state),                         1,  FALSE   },
    {   (uint8_t *)(&System_status),                        1,  TRUE    },
    {   (uint8_t *)(&System_error),                         1,  TRUE    },
    {   (uint8_t *)(&Servo_mode),                           1,  TRUE    },
    {   (uint8_t *)(&Servo_position_factor),                1,  TRUE    },
    {   (uint8_t *)(&(PanServo.request_angle)),             2,  TRUE    },
    {   (uint8_t *)(&(PanServo.request_position)),          2,  TRUE    },
    {   (uint8_t *)(&(PanServo.neutral_position)),          2,  TRUE    },
    {   (uint8_t *)(&(PanServo.min_position)),              2,  TRUE    },
    {   (uint8_t *)(&(PanServo.max_position)),              2,  TRUE    },
    {   (uint8_t *)(&(TiltServo.request_angle)),            2,  TRUE    },
    {   (uint8_t *)(&(TiltServo.request_position)),         2,  TRUE    },
    {   (uint8_t *)(&(TiltServo.neutral_position)),         2,  TRUE    },
    {   (uint8_t *)(&(TiltServo.min_position)),             2,  TRUE    },
    {   (uint8_t *)(&(TiltServo.max_position)),             2,  TRUE    },
    {   (uint8_t *)(&StatusLED_brink_period_COM_TIMEOUT),   1,  TRUE    },
    {   (uint8_t *)(&ErrorLED_brink_period),                1,  TRUE    },
    {   (uint8_t *)(&com_timeout_limit),                    1,  TRUE    }
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
    
    if (    (index < REGISTER_INDEX_NUM)
        &&  (Register_table[index].write_enable == TRUE)  ) {
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
