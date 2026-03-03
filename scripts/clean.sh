#!/bin/bash
# Mini-KV 清理脚本 (Linux/Mac)

echo "========================================"
echo "  Mini-KV 清理脚本"
echo "========================================"
echo ""

echo "正在清理构建产物..."

# 删除 build 目录中的所有文件
if [ -d "build" ]; then
    rm -f build/*.o
    rm -f build/*.exe
    rm -f build/*.out
    rm -f build/mini_kv_test
    rm -f build/mini_kv_cli
    echo "✓ 已清理 build/ 目录"
else
    echo "ℹ build/ 目录不存在"
fi

# 可选：清理数据文件（谨慎使用）
# if [ -d "data" ]; then
#     rm -f data/*.db
#     echo "✓ 已清理 data/ 目录"
# fi

echo ""
echo "========================================"
echo "  清理完成！"
echo "========================================"
echo ""
