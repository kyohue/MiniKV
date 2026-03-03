@echo off
REM Mini-KV CLI 交互式界面编译脚本 (Windows)

REM [解决方案]: 设置终端编码为 UTF-8，解决中文乱码问题
chcp 65001 >nul

REM 获取脚本所在目录的父目录（项目根目录）
set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%.."
cd /d "%PROJECT_ROOT%"

echo ========================================
echo   Mini-KV CLI 交互式界面编译
echo ========================================
echo 项目根目录: %CD%
echo.

REM 检查 g++ 是否安装
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo 错误: 未找到 g++ 编译器！
    echo 请安装 MinGW 或其他 C++ 编译器。
    pause
    exit /b 1
)

REM 创建 build 目录（如果不存在）
if not exist "build" mkdir build

echo.
echo [1/2] 编译 MiniKV.cpp...
g++ -std=c++11 -c src/MiniKV.cpp -o build/MiniKV.o
if %errorlevel% neq 0 (
    echo 编译 MiniKV.cpp 失败！
    pause
    exit /b 1
)

echo [2/2] 编译 cli_main.cpp 并链接...
g++ -std=c++11 build/MiniKV.o src/cli_main.cpp -o build/mini_kv_cli.exe
if %errorlevel% neq 0 (
    echo 编译失败！
    pause
    exit /b 1
)

echo.
echo ========================================
echo   编译成功！正在启动 Mini-KV CLI...
echo ========================================
echo.

REM 启动交互式界面
build\mini_kv_cli.exe

echo.
pause
