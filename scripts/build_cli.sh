#!/bin/bash
# Mini-KV CLI 交互式界面编译脚本 (Linux/Mac)

echo "========================================"
echo "  Mini-KV CLI 交互式界面编译"
echo "========================================"

# 检查 g++ 是否安装
if ! command -v g++ &> /dev/null; then
    echo "错误: 未找到 g++ 编译器！"
    echo "请安装 g++ 或 clang++。"
    exit 1
fi

# 创建 build 目录（如果不存在）
mkdir -p build

echo ""
echo "[1/2] 编译 MiniKV.cpp..."
g++ -std=c++11 -c src/MiniKV.cpp -o build/MiniKV.o
if [ $? -ne 0 ]; then
    echo "编译 MiniKV.cpp 失败！"
    exit 1
fi

echo "[2/2] 编译 cli_main.cpp 并链接..."
g++ -std=c++11 build/MiniKV.o src/cli_main.cpp -o build/mini_kv_cli
if [ $? -ne 0 ]; then
    echo "编译失败！"
    exit 1
fi

echo ""
echo "========================================"
echo "  编译成功！正在启动 Mini-KV CLI..."
echo "========================================"
echo ""

# 启动交互式界面
./build/mini_kv_cli
