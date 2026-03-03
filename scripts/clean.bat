@echo off
REM Mini-KV 清理脚本 (Windows)

chcp 65001 >nul

REM 获取脚本所在目录的父目录（项目根目录）
set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%.."
cd /d "%PROJECT_ROOT%"

echo ========================================
echo   Mini-KV 清理脚本
echo ========================================
echo 项目根目录: %CD%
echo.

echo 正在清理构建产物...

REM 删除 build 目录中的所有文件
if exist "build" (
    del /Q build\*.o 2>nul
    del /Q build\*.exe 2>nul
    del /Q build\*.out 2>nul
    echo ✓ 已清理 build/ 目录
) else (
    echo ℹ build/ 目录不存在
)

REM 可选：清理数据文件（谨慎使用）
REM if exist "data" (
REM     del /Q data\*.db 2>nul
REM     echo ✓ 已清理 data/ 目录
REM )

echo.
echo ========================================
echo   清理完成！
echo ========================================
echo.

pause
