# Mini-KV 交互式 CLI 使用指南

## 🎯 概述

Mini-KV CLI 是一个类似 Redis 的交互式命令行界面，让您可以像使用真实数据库一样操作 Mini-KV。

## 🚀 快速开始

### 编译并启动

**Windows 系统**：
```cmd
build_cli.bat
```

**手动编译**：
```bash
g++ -std=c++11 -c src/MiniKV.cpp -o MiniKV.o
g++ -std=c++11 MiniKV.o src/cli_main.cpp -o mini_kv_cli.exe
mini_kv_cli.exe
```

### 启动界面

```
╔════════════════════════════════════════════════╗
║                                                ║
║          Mini-KV 交互式命令行界面              ║
║        轻量级内存键值数据库 v1.0               ║
║                                                ║
╚════════════════════════════════════════════════╝

欢迎使用 Mini-KV！输入 HELP 查看可用命令。

mini-kv>
```

## 📖 命令参考

### 数据操作命令

#### SET - 设置键值对

**语法**：
```
SET <key> <value>
```

**示例**：
```
mini-kv> SET name 张三
✓ OK (新建)

mini-kv> SET name 李四
✓ OK (更新)

mini-kv> SET message Hello World
✓ OK (新建)
```

**说明**：
- 如果键不存在，创建新的键值对
- 如果键已存在，更新其值
- 值可以包含空格（会自动拼接）

---

#### GET - 获取键对应的值

**语法**：
```
GET <key>
```

**示例**：
```
mini-kv> GET name
"李四"

mini-kv> GET nonexistent
(nil) - 键不存在
```

**说明**：
- 返回键对应的值（用引号包裹）
- 如果键不存在，返回 `(nil)`

---

#### DEL - 删除键值对

**语法**：
```
DEL <key>
```

**示例**：
```
mini-kv> DEL name
✓ 删除成功

mini-kv> DEL nonexistent
❌ 键不存在
```

**说明**：
- 删除指定的键值对
- 返回操作是否成功

---

#### EXISTS - 检查键是否存在

**语法**：
```
EXISTS <key>
```

**示例**：
```
mini-kv> EXISTS name
✓ 存在

mini-kv> EXISTS nonexistent
✗ 不存在
```

**说明**：
- 检查键是否存在于数据库中
- 不返回值，只返回存在性

---

### 数据库管理命令

#### KEYS - 列出所有键值对

**语法**：
```
KEYS
```

**示例**：
```
mini-kv> KEYS
数据库中的所有键值对:
========== Mini-KV 数据库内容 ==========
总键值对数量: 3
总操作次数: 5
----------------------------------------
  [name] => "张三"
  [age] => "25"
  [city] => "北京"
========================================
```

**说明**：
- 显示数据库中所有的键值对
- 如果数据库为空，显示提示信息

---

#### SIZE - 显示键值对数量

**语法**：
```
SIZE
```

**示例**：
```
mini-kv> SIZE
键值对数量: 3
```

**说明**：
- 返回数据库中键值对的总数

---

#### CLEAR - 清空数据库

**语法**：
```
CLEAR
```

**示例**：
```
mini-kv> CLEAR
⚠️  确定要清空数据库吗？(y/n): y
✓ 数据库已清空

mini-kv> CLEAR
⚠️  确定要清空数据库吗？(y/n): n
✗ 操作已取消
```

**说明**：
- 删除数据库中的所有键值对
- 需要用户确认（输入 y/yes 确认）
- 这是危险操作，请谨慎使用

---

#### INFO - 显示数据库统计信息

**语法**：
```
INFO
```

**示例**：
```
mini-kv> INFO

═══════════ 数据库统计信息 ═══════════
  键值对数量: 5
  总操作次数: 12
  数据库版本: Mini-KV v1.0 (Phase 1)
═══════════════════════════════════════
```

**说明**：
- 显示数据库的统计信息
- 包括键值对数量、操作次数、版本信息

---

### 系统命令

#### HELP - 显示帮助信息

**语法**：
```
HELP
```

**示例**：
```
mini-kv> HELP

═══════════════ 可用命令 ═══════════════

  数据操作命令：
    SET <key> <value>     设置键值对
    GET <key>             获取键对应的值
    DEL <key>             删除指定的键
    EXISTS <key>          检查键是否存在

  数据库管理命令：
    KEYS                  列出所有键
    VALUES                列出所有值
    SIZE                  显示键值对数量
    CLEAR                 清空数据库
    INFO                  显示数据库统计信息

  系统命令：
    HELP                  显示此帮助信息
    QUIT / EXIT           退出程序

═══════════════════════════════════════
```

---

#### QUIT / EXIT - 退出程序

**语法**：
```
QUIT
EXIT
```

**示例**：
```
mini-kv> QUIT

再见！感谢使用 Mini-KV。
```

**说明**：
- 退出 Mini-KV CLI
- `QUIT` 和 `EXIT` 效果相同
- 也可以使用 `Ctrl+C` 强制退出

---

## 💡 使用技巧

### 1. 命令不区分大小写

```
mini-kv> set name 张三
✓ OK (新建)

mini-kv> SET name 张三
✓ OK (更新)

mini-kv> SeT name 张三
✓ OK (更新)
```

所有命令都会自动转换为大写处理。

---

### 2. 值可以包含空格

```
mini-kv> SET message Hello World from Mini-KV
✓ OK (新建)

mini-kv> GET message
"Hello World from Mini-KV"
```

SET 命令会自动将第二个参数之后的所有内容拼接成值。

---

### 3. 空行会被忽略

```
mini-kv> 

mini-kv> 

mini-kv> SET name 张三
✓ OK (新建)
```

直接按回车不会产生任何效果。

---

### 4. 错误提示友好

```
mini-kv> UNKNOWN_COMMAND
❌ 未知命令: UNKNOWN_COMMAND
   输入 HELP 查看可用命令

mini-kv> SET
❌ 错误: SET 命令需要 2 个参数
   用法: SET <key> <value>
```

---

## 🎓 实战演练

### 场景 1：用户信息管理

```
mini-kv> SET user:1001:name 张三
✓ OK (新建)

mini-kv> SET user:1001:email zhangsan@example.com
✓ OK (新建)

mini-kv> SET user:1001:age 25
✓ OK (新建)

mini-kv> GET user:1001:name
"张三"

mini-kv> GET user:1001:email
"zhangsan@example.com"

mini-kv> KEYS
数据库中的所有键值对:
========== Mini-KV 数据库内容 ==========
总键值对数量: 3
总操作次数: 3
----------------------------------------
  [user:1001:name] => "张三"
  [user:1001:email] => "zhangsan@example.com"
  [user:1001:age] => "25"
========================================

mini-kv> DEL user:1001:age
✓ 删除成功

mini-kv> SIZE
键值对数量: 2
```

---

### 场景 2：配置管理

```
mini-kv> SET config:database:host localhost
✓ OK (新建)

mini-kv> SET config:database:port 3306
✓ OK (新建)

mini-kv> SET config:cache:enabled true
✓ OK (新建)

mini-kv> GET config:database:host
"localhost"

mini-kv> EXISTS config:cache:enabled
✓ 存在

mini-kv> INFO

═══════════ 数据库统计信息 ═══════════
  键值对数量: 3
  总操作次数: 3
  数据库版本: Mini-KV v1.0 (Phase 1)
═══════════════════════════════════════
```

---

### 场景 3：会话管理

```
mini-kv> SET session:abc123:user_id 1001
✓ OK (新建)

mini-kv> SET session:abc123:login_time 2024-01-15 10:30:00
✓ OK (新建)

mini-kv> GET session:abc123:user_id
"1001"

mini-kv> DEL session:abc123:user_id
✓ 删除成功

mini-kv> DEL session:abc123:login_time
✓ 删除成功

mini-kv> SIZE
键值对数量: 0
```

---

## 🔧 技术实现亮点

### 1. REPL 模式（Read-Eval-Print Loop）

```cpp
while (true) {
    std::cout << "mini-kv> ";
    std::string line;
    std::getline(std::cin, line);
    process_command(db, line);
}
```

这是所有交互式解释器的标准模式。

---

### 2. 命令解析

```cpp
std::vector<std::string> split_command(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}
```

使用 `std::istringstream` 按空格分割命令。

---

### 3. 命令分发（Command Pattern）

```cpp
if (cmd == "SET") {
    handle_set(db, args);
}
else if (cmd == "GET") {
    handle_get(db, args);
}
// ...
```

每个命令对应一个独立的处理函数，便于扩展。

---

### 4. 用户友好的错误提示

```cpp
if (args.size() < 3) {
    std::cout << "❌ 错误: SET 命令需要 2 个参数\n";
    std::cout << "   用法: SET <key> <value>\n";
    return;
}
```

---

## 🆚 与 Redis CLI 的对比

| 特性 | Redis CLI | Mini-KV CLI | 说明 |
|------|-----------|-------------|------|
| 交互式界面 | ✅ | ✅ | 都支持 REPL 模式 |
| 基础命令 | ✅ | ✅ | SET/GET/DEL/EXISTS |
| 命令补全 | ✅ | ❌ | Phase 1 暂不支持 |
| 历史记录 | ✅ | ❌ | Phase 1 暂不支持 |
| 网络连接 | ✅ | ❌ | Phase 1 是单机版 |
| 持久化 | ✅ | ❌ | Phase 2 将实现 |
| 多数据类型 | ✅ | ❌ | Phase 3 将实现 |
| 并发支持 | ✅ | ❌ | Phase 4 将实现 |

---

## 🚀 后续版本预告

### Phase 2 将增加：
- `SAVE` 命令：保存数据到磁盘
- `LOAD` 命令：从磁盘加载数据
- 异常处理：更健壮的错误处理

### Phase 3 将增加：
- 支持多种数据类型（int, double, list）
- `FILTER` 命令：条件查询
- Lambda 表达式支持

### Phase 4 将增加：
- 多客户端并发访问
- 事务支持（MULTI/EXEC）
- 发布订阅模式

---

## 📝 总结

Mini-KV CLI 提供了一个类似 Redis 的交互式体验，让您可以：

✅ 直观地测试数据库功能  
✅ 学习命令行程序的设计模式  
✅ 理解 REPL 循环的实现原理  
✅ 体验真实数据库的使用感受  

现在就运行 `build_cli.bat`，开始您的 Mini-KV 之旅吧！🎉
