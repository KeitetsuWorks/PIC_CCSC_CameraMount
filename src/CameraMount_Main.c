/**
 * @file        CameraMount_Main.c
 * @brief       カメラマウントコントローラ メイン関数
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include "TargetBoard.h"

#include "CommonDataType.h"
#include "CommonDefine.h"
#include "ccsc_uart.h"

#include "CameraMount_Main.h"
#include "CameraMount_System.h"
#include "CameraMount_AppManager.h"
#include "CameraMount_EEPROM.h"


#priority TIMER1, CCP1, RDA, TBE, EEPROM, RTCC


void initDevice(void)
{
#if _DEVELOPMENTBOARD == 1
    // 出力ピンの初期化
    output_a(0x00);
    output_b(0x00);
    output_c(0x00);
    output_d(0x00);
    output_e(0x00);

    // 入出力設定
    set_tris_a(0x00);
    set_tris_b(0x00);
    set_tris_c(0x80);
    set_tris_d(0x00);
    set_tris_e(0x00);

    // 割込み無効化
    disable_interrupts(GLOBAL);

    // ペリフェラル設定
    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_OFF);
    setup_psp(PSP_DISABLED);
    setup_spi(FALSE);
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_128);
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
    setup_timer_2(T2_DISABLED, 255, 1);
    setup_ccp1(CCP_COMPARE_INT);
    setup_ccp2(CCP_OFF);
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
#else
    // 出力ピンの初期化
    output_a(0x00);
    output_b(0x04);

    // 入出力設定
    set_tris_a(0x00);
    set_tris_b(0x00);

    // 割込み無効化
    disable_interrupts(GLOBAL);

    // ペリフェラル設定
    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_OFF);
    setup_spi(FALSE);
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_128);
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
    setup_timer_2(T2_DISABLED, 255, 1);
    setup_ccp1(CCP_COMPARE_INT);
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
#endif

    return;
}


void main(void)
{
    // デバイスの初期化
    initDevice();
    
    // デバイス制御の初期化（システムステート非依存）
    uart_tx_initBuffer();
    uart_rx_initBuffer();
    uart_rx_disable();
    EEPROM_init();
    
    // システム制御の初期化
    System_init();
    
    // アプリケーションマネージャの初期化
    AppManager_init();
    
    // 無限ループ
    while (TRUE) {
        AppManager_exec();
    }
    
    return;
}
