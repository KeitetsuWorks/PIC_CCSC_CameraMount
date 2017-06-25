/**
 * @file        CameraMount_EEPROM.c
 * @brief       カメラマウントコントローラ EEPROM制御
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"

#include "CameraMount_EEPROM.h"


/**
 * @var     EEPROM_table
 * @brief   EEPROMテーブル
 */
const struct eeprom_t EEPROM_table[] = {
    {   EEPROM_ADDR_PAN_SERVO_NEUTRAL_POSITION_L,           EEPROM_SIZE_PAN_SERVO_NEUTRAL_POSITION,             TRUE    },
    {   EEPROM_ADDR_PAN_SERVO_MIN_POSITION_L,               EEPROM_SIZE_PAN_SERVO_MIN_POSITION,                 TRUE    },
    {   EEPROM_ADDR_PAN_SERVO_MAX_POSITION_L,               EEPROM_SIZE_PAN_SERVO_MAX_POSITION,                 TRUE    },
    {   EEPROM_ADDR_TILT_SERVO_NEUTRAL_POSITION_L,          EEPROM_SIZE_TILT_SERVO_NEUTRAL_POSITION,            TRUE    },
    {   EEPROM_ADDR_TILT_SERVO_MIN_POSITION_L,              EEPROM_SIZE_TILT_SERVO_MIN_POSITION,                TRUE    },
    {   EEPROM_ADDR_TILT_SERVO_MAX_POSITION_L,              EEPROM_SIZE_TILT_SERVO_MAX_POSITION,                TRUE    },
    {   EEPROM_ADDR_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT,    EEPROM_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT,    TRUE    },
    {   EEPROM_ADDR_ERROR_LED_BRINK_PERIOD,                 EEPROM_SIZE_ERROR_LED_BRINK_PERIOD,                 TRUE    },
    {   EEPROM_ADDR_COM_TIMEOUT_LIMIT,                      EEPROM_SIZE_COM_TIMEOUT_LIMIT,                      TRUE    }
};


bool EEPROM_writing;                            /*!< EEPROM書込み中フラグ */
uint8_t EEPROM_write_index;                     /*!< EEPROM書込みターゲットインデックス */
uint8_t EEPROM_write_buffer[EEPROM_SIZE_MAX];   /*!< EEPROM書込みデータバッファ */
uint8_t EEPROM_write_count;                     /*!< EEPROM書込みサイズ */


void EEPROM_init(void)
{
    EEPROM_writing = FALSE;
    
    return;
}


uint8_t EEPROM_getSize(uint8_t index)
{
    uint8_t size;
    
    size = 0;
    
    if (index < EEPROM_INDEX_NUM) {
        size =  EEPROM_table[index].size;
    }
    
    return size;
}


uint8_t EEPROM_read(
    uint8_t index,
    void *data)
{
    uint8_t *read_buffer;
    uint8_t read_count;
    
    read_buffer = (uint8_t *)data;
    read_count = 0;
    
    if (EEPROM_isWriting() == FALSE) {
        if (index < EEPROM_INDEX_NUM) {
            while (read_count < EEPROM_table[index].size) {
                *read_buffer = read_eeprom(EEPROM_table[index].addr + read_count);
                read_buffer++;
                read_count++;
            }
        }
    }
    
    return read_count;
}


#inline
bool EEPROM_isWriting(void)
{
    return EEPROM_writing;
}


bool EEPROM_write(
    uint8_t index,
    void *data)
{
    bool result;
    uint8_t *write_data;
    uint8_t copy_count;
    
    write_data = (uint8_t *)data;
    copy_count = 0;
    
    if (EEPROM_isWriting() == FALSE) {
        if (    (index < EEPROM_INDEX_NUM)
            &&  (EEPROM_table[index].write_enable == TRUE)  ) {
            while (copy_count < EEPROM_table[index].size) {
                EEPROM_write_buffer[copy_count] = *write_data;
                *write_data++;
                copy_count++;
            }
            EEPROM_write_index = index;
            EEPROM_write_count = 0;
            
            write_eeprom((EEPROM_table[EEPROM_write_index].addr + EEPROM_write_count), EEPROM_write_buffer[EEPROM_write_count]);
            enable_interrupts(INT_EEPROM);
            eeprom_writing = TRUE;
            result = TRUE;
        }
        else {
            result = FALSE;
        }
    }
    else {
        result = FALSE;
    }
    
    return result;
}


#org 0x0A00, 0xAFF DEFAULT
#int_EEPROM
void isr_EEPROM(void)
{
    EEPROM_write_count++;
    
    if (EEPROM_write_count < EEPROM_table[EEPROM_write_index].size) {
        write_eeprom((EEPROM_table[EEPROM_write_index].addr + EEPROM_write_count), EEPROM_write_buffer[EEPROM_write_count]);
    }
    else {
        disable_interrupts(INT_EEPROM);
        eeprom_writing = FALSE;
    }
    
    return;
}
#org DEFAULT
