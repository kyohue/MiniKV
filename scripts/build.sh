#!/bin/bash
# Mini-KV Phase 1 编译脚本 (Linux/Mac)

echo "========================================"
echo "  Mini-KV Phase 1 编译脚本"
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
echo "[1/3] 编译 MiniKV.cpp..."
g++ -std=c++11 -c src/MiniKV.cpp -o build/MiniKV.o
if [ $? -ne 0 ]; then
    echo "编译 MiniKV.cpp 失败！"
    exit 1
fi

echo "[2/3] 编译 test_main.cpp..."
g++ -std=c++11 -c tests/test_main.cpp -o build/test_main.o
if [ $? -ne 0 ]; then
    echo "编译 test_main.cpp 失败！"
    exit 1
fi

echo "[3/3] 链接生成可执行文件..."
g++ build/MiniKV.o build/test_main.o -o build/mini_kv_test
if [ $? -ne 0 ]; then
    echo "链接失败！"
    exit 1
fi

echo ""
echo "========================================"
echo "  编译成功！正在运行测试..."
echo "========================================"
echo ""

# 运行测试
./build/mini_kv_test
