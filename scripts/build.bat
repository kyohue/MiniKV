@echo off
REM Mini-KV Phase 1 编译脚本 (Windows)

REM [解决方案]: 设置终端编码为 UTF-8，解决中文乱码问题
REM 65001 是 UTF-8 的代码页编号
chcp 65001 >nul

REM 获取脚本所在目录的父目录（项目根目录）
set "SCRIPT_DIR=%~dp0"
set "PROJECT_ROOT=%SCRIPT_DIR%.."
cd /d "%PROJECT_ROOT%"

echo ========================================
echo   Mini-KV Phase 1 编译脚本
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
echo [1/3] 编译 MiniKV.cpp...
g++ -std=c++11 -c src/MiniKV.cpp -o build/MiniKV.o
if %errorlevel% neq 0 (
    echo 编译 MiniKV.cpp 失败！
    pause
    exit /b 1
)

echo [2/3] 编译 test_main.cpp...
g++ -std=c++11 -c tests/test_main.cpp -o build/test_main.o
if %errorlevel% neq 0 (
    echo 编译 test_main.cpp 失败！
    pause
    exit /b 1
)

echo [3/3] 链接生成可执行文件...
g++ build/MiniKV.o build/test_main.o -o build/mini_kv_test.exe
if %errorlevel% neq 0 (
    echo 链接失败！
    pause
    exit /b 1
)

echo.
echo ========================================
echo   编译成功！正在运行测试...
echo ========================================
echo.

REM 运行测试
build\mini_kv_test.exe

echo.
pause
