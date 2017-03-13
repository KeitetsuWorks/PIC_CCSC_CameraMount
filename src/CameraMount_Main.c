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

#include "CameraMount_Main.h"
#include "CameraMount_LED.h"
#include "CameraMount_Servo.h"
#include "CameraMount_System.h"
#include "CameraMount_CyclicHandler.h"


void initDevice(void)
{
#if _DEVELOPMENTBOARD == 1
    // 出力ピンの初期化
    output_a(0x00);
    output_b(0x00);
    output_c(0x01);
    output_d(0x00);
    output_e(0x00);

    // 入出力設定
    set_tris_a(0x00);
    set_tris_b(0x00);
    set_tris_c(0x80);
    set_tris_d(0x00);
    set_tris_e(0x00);

    // ペリフェラル設定
    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_OFF);
    setup_psp(PSP_DISABLED);
    setup_spi(FALSE);
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_64);
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
    setup_timer_2(T2_DIV_BY_1, 255, 1);
    setup_ccp1(CCP_PWM);
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
#else
    // 出力ピンの初期化
    output_a(0x00);
    output_b(0x04);

    // 入出力設定
    set_tris_a(0x00);
    set_tris_b(0x00);

    // ペリフェラル設定
    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_OFF);
    setup_spi(FALSE);
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_64);
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
    setup_timer_2(T2_DIV_BY_1, 255, 1);
    setup_ccp1(CCP_PWM);
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
#endif

    return;
}


void main(void)
{
    // デバイスの初期化
    initDevice();
    LED_init();
    Servo_init();
    
    // システムの初期化
    System_init();
    
    // 周期ハンドラの初期化
    CyclicHandler_init();
    
    // 割込み設定
    enable_interrupts(GLOBAL);
    
    // 無限ループ
    while (TRUE) {
    }
    
    return;
}
