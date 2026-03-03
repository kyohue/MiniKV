#include "../include/MiniKV.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

// [C++特性说明]: 使用命名空间简化代码
using namespace MiniKV;

/**
 * @brief 将字符串按空格分割成多个部分
 * 
 * [C++特性说明]: 使用 std::istringstream 进行字符串流处理
 * 这是 C++ 中解析字符串的标准方法
 */
std::vector<std::string> split_command(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    
    // [C++特性说明]: >> 操作符会自动跳过空白字符
    // 这样可以方便地按空格分割字符串
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

/**
 * @brief 将字符串转换为大写
 * 
 * [C++特性说明]: 使用 std::transform 和 Lambda 表达式
 * 这是函数式编程的思想在 C++ 中的体现
 */
std::string to_upper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), 
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

/**
 * @brief 打印欢迎信息
 */
void print_welcome() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════╗\n";
    std::cout << "║                                                ║\n";
    std::cout << "║          Mini-KV 交互式命令行界面              ║\n";
    std::cout << "║        轻量级内存键值数据库 v1.0               ║\n";
    std::cout << "║                                                ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    std::cout << "\n";
    std::cout << "欢迎使用 Mini-KV！输入 HELP 查看可用命令。\n";
    std::cout << "\n";
}

/**
 * @brief 打印帮助信息
 */
void print_help() {
    std::cout << "\n";
    std::cout << "═══════════════ 可用命令 ═══════════════\n";
    std::cout << "\n";
    std::cout << "  数据操作命令：\n";
    std::cout << "    SET <key> <value>     设置键值对\n";
    std::cout << "    GET <key>             获取键对应的值\n";
    std::cout << "    DEL <key>             删除指定的键\n";
    std::cout << "    EXISTS <key>          检查键是否存在\n";
    std::cout << "\n";
    std::cout << "  数据库管理命令：\n";
    std::cout << "    KEYS                  列出所有键\n";
    std::cout << "    SIZE                  显示键值对数量\n";
    std::cout << "    CLEAR                 清空数据库\n";
    std::cout << "    INFO                  显示数据库统计信息\n";
    std::cout << "\n";
    std::cout << "  系统命令：\n";
    std::cout << "    HELP                  显示此帮助信息\n";
    std::cout << "    QUIT / EXIT           退出程序\n";
    std::cout << "\n";
    std::cout << "═══════════════════════════════════════════\n";
    std::cout << "\n";
}

/**
 * @brief 处理 SET 命令
 */
void handle_set(Database& db, const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cout << "❌ 错误: SET 命令需要 2 个参数\n";
        std::cout << "   用法: SET <key> <value>\n";
        return;
    }
    
    const std::string& key = args[1];
    
    // [C++特性说明]: 将剩余的所有参数拼接成 value
    // 这样可以支持包含空格的值
    std::string value;
    for (size_t i = 2; i < args.size(); ++i) {
        if (i > 2) value += " ";
        value += args[i];
    }
    
    bool is_new = db.set(key, value);
    
    if (is_new) {
        std::cout << "✓ OK (新建)\n";
    } else {
        std::cout << "✓ OK (更新)\n";
    }
}

/**
 * @brief 处理 GET 命令
 */
void handle_get(Database& db, const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "❌ 错误: GET 命令需要 1 个参数\n";
        std::cout << "   用法: GET <key>\n";
        return;
    }
    
    const std::string& key = args[1];
    std::string value;
    
    if (db.get(key, value)) {
        std::cout << "\"" << value << "\"\n";
    } else {
        std::cout << "(nil) - 键不存在\n";
    }
}

/**
 * @brief 处理 DEL 命令
 */
void handle_del(Database& db, const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "❌ 错误: DEL 命令需要 1 个参数\n";
        std::cout << "   用法: DEL <key>\n";
        return;
    }
    
    const std::string& key = args[1];
    
    if (db.del(key)) {
        std::cout << "✓ 删除成功\n";
    } else {
        std::cout << "❌ 键不存在\n";
    }
}

/**
 * @brief 处理 EXISTS 命令
 */
void handle_exists(Database& db, const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "❌ 错误: EXISTS 命令需要 1 个参数\n";
        std::cout << "   用法: EXISTS <key>\n";
        return;
    }
    
    const std::string& key = args[1];
    
    if (db.exists(key)) {
        std::cout << "✓ 存在\n";
    } else {
        std::cout << "✗ 不存在\n";
    }
}

/**
 * @brief 处理 KEYS 命令（列出所有键）
 * 
 * [设计说明]: 这个功能需要访问 Database 的内部数据
 * 为了保持封装性，我们直接调用 printAll() 的简化版本
 */
void handle_keys(Database& db, const std::vector<std::string>& args) {
    if (db.size() == 0) {
        std::cout << "(数据库为空)\n";
        return;
    }
    
    std::cout << "数据库中的所有键值对:\n";
    db.printAll();
}

/**
 * @brief 处理 SIZE 命令
 */
void handle_size(Database& db, const std::vector<std::string>& args) {
    std::cout << "键值对数量: " << db.size() << "\n";
}

/**
 * @brief 处理 CLEAR 命令
 */
void handle_clear(Database& db, const std::vector<std::string>& args) {
    std::cout << "⚠️  确定要清空数据库吗？(y/n): ";
    std::string confirm;
    std::getline(std::cin, confirm);
    
    if (confirm == "y" || confirm == "Y" || confirm == "yes" || confirm == "YES") {
        db.clear();
        std::cout << "✓ 数据库已清空\n";
    } else {
        std::cout << "✗ 操作已取消\n";
    }
}

/**
 * @brief 处理 INFO 命令
 */
void handle_info(Database& db, const std::vector<std::string>& args) {
    std::cout << "\n";
    std::cout << "═══════════ 数据库统计信息 ═══════════\n";
    std::cout << "  键值对数量: " << db.size() << "\n";
    std::cout << "  总操作次数: " << db.getOperationCount() << "\n";
    std::cout << "  数据库版本: Mini-KV v1.0 (Phase 1)\n";
    std::cout << "═══════════════════════════════════════\n";
    std::cout << "\n";
}

/**
 * @brief 主命令处理函数
 * 
 * [设计模式]: 命令模式 (Command Pattern)
 * 将每个命令封装成独立的处理函数，便于扩展和维护
 */
bool process_command(Database& db, const std::string& line) {
    // 分割命令
    std::vector<std::string> args = split_command(line);
    
    if (args.empty()) {
        return true;  // 空行，继续
    }
    
    // 将命令转换为大写（不区分大小写）
    std::string cmd = to_upper(args[0]);
    
    // [C++特性说明]: 使用 if-else 链处理不同命令
    // Phase 3 可以改用 std::unordered_map<std::string, function> 实现命令分发
    
    if (cmd == "QUIT" || cmd == "EXIT") {
        std::cout << "\n再见！感谢使用 Mini-KV。\n\n";
        return false;  // 退出
    }
    else if (cmd == "HELP") {
        print_help();
    }
    else if (cmd == "SET") {
        handle_set(db, args);
    }
    else if (cmd == "GET") {
        handle_get(db, args);
    }
    else if (cmd == "DEL") {
        handle_del(db, args);
    }
    else if (cmd == "EXISTS") {
        handle_exists(db, args);
    }
    else if (cmd == "KEYS") {
        handle_keys(db, args);
    }
    else if (cmd == "SIZE") {
        handle_size(db, args);
    }
    else if (cmd == "CLEAR") {
        handle_clear(db, args);
    }
    else if (cmd == "INFO") {
        handle_info(db, args);
    }
    else {
        std::cout << "❌ 未知命令: " << cmd << "\n";
        std::cout << "   输入 HELP 查看可用命令\n";
    }
    
    return true;  // 继续
}

/**
 * @brief 主函数：交互式命令行循环
 * 
 * [设计模式]: REPL (Read-Eval-Print Loop)
 * 这是所有交互式解释器的标准模式
 */
int main() {
    // 创建数据库实例
    Database db;
    
    // 打印欢迎信息
    print_welcome();
    
    // [C++特性说明]: REPL 循环
    // Read (读取) -> Eval (执行) -> Print (输出) -> Loop (循环)
    while (true) {
        // 显示提示符
        std::cout << "mini-kv> ";
        
        // 读取用户输入
        std::string line;
        if (!std::getline(std::cin, line)) {
            // [C++特性说明]: getline 失败可能是因为 EOF (Ctrl+D/Ctrl+Z)
            std::cout << "\n";
            break;
        }
        
        // 处理命令
        if (!process_command(db, line)) {
            break;  // 用户输入了 QUIT/EXIT
        }
    }
    
    return 0;
}
