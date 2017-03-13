@echo off

rem 
rem @file        ccsc_clean.bat
rem @brief       CCS C Compiler 出力ファイル削除処理
rem @author      Keitetsu
rem @date        2017/01/30
rem @copyright   Copyright (c) 2017 Keitetsu
rem @par         License
rem              This software is released under the MIT License.
rem 

setlocal

set SRC_DIR=.\src
set BUILD_DIR=.\build

echo CCS C Compiler の出力ファイルを削除しています
del /Q %SRC_DIR%\*.BAK
del /Q %SRC_DIR%\*.cod
del /Q %SRC_DIR%\*.cof
del /Q %SRC_DIR%\*.err
del /Q %SRC_DIR%\*.HEX
del /Q %SRC_DIR%\*.LST
del /Q %SRC_DIR%\*.PJT
del /Q %SRC_DIR%\*.sta
del /Q %SRC_DIR%\*.SYM
del /Q %SRC_DIR%\*.tre
rmdir /s /q %BUILD_DIR%

echo 削除が完了しました

endlocal

exit
