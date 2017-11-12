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

rem ソースフォルダに移動
if not exist %SRC_DIR%\ (
	echo Error: ソースフォルダが見つかりません
	pause
	goto END_MAKE
)
cd /D %SRC_DIR%

rem コンパイル実行
if not exist %SRC% (
	echo Error: ソースファイルが見つかりません
	cd /D %~dp0
	pause
	goto END_MAKE
)
"C:\Program Files (x86)\PICC\Ccsc.exe" +FM +EW +T +A +G_DEVELOPMENTBOARD=0 %SRC%
cd /D %~dp0

rem コンパイル結果格納用フォルダを作成
if not exist %BUILD_DIR%\ (
	mkdir %BUILD_DIR%
)

rem コンパイル結果をコンパイル結果格納用フォルダに移動
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
