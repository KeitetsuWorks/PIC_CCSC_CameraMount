@echo off

rem 
rem @file        doxygen_clean.bat
rem @brief       Doxygen �o�̓t�@�C���폜����
rem @author      Keitetsu
rem @date        2017/03/06
rem @copyright   Copyright (c) 2017 Keitetsu
rem @par         License
rem              This software is released under the MIT License.
rem 

setlocal

set DOXYGEN_HTML_DIR=.\html
set DOXYGEN_RTF_DIR=.\rtf

echo Doxygen �̏o�̓t�@�C�����폜���Ă��܂�
rmdir /s /q %DOXYGEN_HTML_DIR%
rmdir /s /q %DOXYGEN_RTF_DIR%

echo �폜���������܂���

endlocal

exit /B
