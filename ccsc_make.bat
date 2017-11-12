@echo off

rem 
rem @file        ccsc_make.bat
rem @brief       Makefile for CCS C Compiler
rem @author      Keitetsu
rem @date        2016/12/31
rem @copyright   Copyright (c) 2016 Keitetsu
rem @par         License
rem              This software is released under the MIT License.
rem 

setlocal

set SRC_DIR=.\src
set SRC=CameraMount.c
set BUILD_DIR=.\build

rem �\�[�X�t�H���_�Ɉړ�
if not exist %SRC_DIR%\ (
	echo Error: �\�[�X�t�H���_��������܂���
	pause
	goto END_MAKE
)
cd /D %SRC_DIR%

rem �R���p�C�����s
if not exist %SRC% (
	echo Error: �\�[�X�t�@�C����������܂���
	cd /D %~dp0
	pause
	goto END_MAKE
)
"C:\Program Files (x86)\PICC\Ccsc.exe" +FM +EW +T +A +G_DEVELOPMENTBOARD=0 %SRC%
cd /D %~dp0

rem �R���p�C�����ʊi�[�p�t�H���_���쐬
if not exist %BUILD_DIR%\ (
	mkdir %BUILD_DIR%
)

rem �R���p�C�����ʂ��R���p�C�����ʊi�[�p�t�H���_�Ɉړ�
move /Y %SRC_DIR%\*.cod %BUILD_DIR%
move /Y %SRC_DIR%\*.cof %BUILD_DIR%
move /Y %SRC_DIR%\*.err %BUILD_DIR%
move /Y %SRC_DIR%\*.HEX %BUILD_DIR%
move /Y %SRC_DIR%\*.LST %BUILD_DIR%
move /Y %SRC_DIR%\*.PJT %BUILD_DIR%
move /Y %SRC_DIR%\*.sta %BUILD_DIR%
move /Y %SRC_DIR%\*.SYM %BUILD_DIR%
move /Y %SRC_DIR%\*.tre %BUILD_DIR%

:END_MAKE
endlocal

exit /B
