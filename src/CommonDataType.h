/**
 * @file        CommonDataType.h
 * @brief       共通データ型定義
 * @author      Keitetsu
 * @date        2017/02/11
 * @copyright   Copyright (c) 2017 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __COMMONDATATYPE_H__
#define __COMMONDATATYPE_H__


/**
 * @name    Boolean
 */
/** @{ */
typedef int1                    bool;       /**< Boolean */
/** @} */


/**
 * @name    Signed Integer
 */
/** @{ */
typedef signed int8             int8_t;     /**< 符号あり，8bit */
typedef signed int16            int16_t;    /**< 符号あり，16bit */
typedef signed int32            int32_t;    /**< 符号あり，32bit */
/** @} */


/**
 * @name    Unsigned Integer
 */
/** @{ */
typedef unsigned int8           uint8_t;    /**< 符号なし，8bit */
typedef unsigned int16          uint16_t;   /**< 符号なし，16bit */
typedef unsigned int32          uint32_t;   /**< 符号なし，32bit */
/** @} */


/**
 * @union   data8_u
 * @brief   8bit共用体
 */
union data8_u {
    uint8_t _8bit;          /**< 8bitアクセス */
    struct {
        bool _bit0;
        bool _bit1;
        bool _bit2;
        bool _bit3;
        bool _bit4;
        bool _bit5;
        bool _bit6;
        bool _bit7;
    };
};


/**
 * @union   data16_u
 * @brief   16bit共用体
 */
union data16_u {
    uint16_t _16bit;        /**< 16bitアクセス */
    uint8_t _8bit[2];       /**< 8bitアクセス */
    struct {
        bool _bit0;
        bool _bit1;
        bool _bit2;
        bool _bit3;
        bool _bit4;
        bool _bit5;
        bool _bit6;
        bool _bit7;
        bool _bit8;
        bool _bit9;
        bool _bit10;
        bool _bit11;
        bool _bit12;
        bool _bit13;
        bool _bit14;
        bool _bit15;
    };
};


/**
 * @union   data32_u
 * @brief   32bit共用体
 */
union data32_u {
    uint32_t _32bit;        /**< 32bitアクセス */
    uint16_t _16bit[2];     /**< 16bitアクセス */
    uint8_t _8bit[4];       /**< 8bitアクセス */
    struct {
        bool _bit0;
        bool _bit1;
        bool _bit2;
        bool _bit3;
        bool _bit4;
        bool _bit5;
        bool _bit6;
        bool _bit7;
        bool _bit8;
        bool _bit9;
        bool _bit10;
        bool _bit11;
        bool _bit12;
        bool _bit13;
        bool _bit14;
        bool _bit15;
        bool _bit16;
        bool _bit17;
        bool _bit18;
        bool _bit19;
        bool _bit20;
        bool _bit21;
        bool _bit22;
        bool _bit23;
        bool _bit24;
        bool _bit25;
        bool _bit26;
        bool _bit27;
        bool _bit28;
        bool _bit29;
        bool _bit30;
        bool _bit31;
    };
};

#endif  // __COMMONDATATYPE_H__
