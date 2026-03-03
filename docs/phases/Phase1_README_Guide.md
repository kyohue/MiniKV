# Mini-KV Phase 1 学习指引

## 📚 本阶段概述

Phase 1 实现了一个基础的内存键值数据库，支持基本的 CRUD 操作（增删改查）。这个阶段的重点是掌握 C++ 的面向对象基础和 STL 容器的使用。

## 🎯 核心功能

- **SET**: 设置键值对（插入或更新）
- **GET**: 根据键获取值
- **DEL**: 删除指定的键值对
- **EXISTS**: 检查键是否存在
- **SIZE**: 获取数据库中键值对的数量
- **CLEAR**: 清空整个数据库

## 🔑 涵盖的 C++ 核心知识点

### 1. 类与对象（面向对象基础）

#### 1.1 类的定义与封装
```cpp
class Database {
private:
    std::unordered_map<std::string, std::string> storage_;  // 私有成员
public:
    bool set(const std::string& key, const std::string& value);  // 公有接口
};
```

**关键概念**：
- **封装性**：将数据（`storage_`）设为 private，只通过 public 方法访问
- **访问控制**：private/public 关键字控制成员的可见性
- **为什么这样设计**：防止外部代码直接修改内部数据结构，保证数据一致性

#### 1.2 构造函数与析构函数
```cpp
Database::Database() 
    : storage_(),           // 初始化列表
      operation_count_(0)
{
    // 构造函数体
}

Database::~Database() {
    // 析构函数：对象销毁时自动调用
}
```

**关键概念**：
- **初始化列表**：在对象构造时直接初始化成员，比在函数体内赋值更高效
- **RAII 原则**：资源获取即初始化，C++ 的核心设计哲学
- **为什么使用初始化列表**：
  - 对于复杂对象（如 `unordered_map`），避免了"先默认构造再赋值"的两步操作
  - 对于 const 成员和引用成员，必须使用初始化列表

### 2. 头文件与源文件分离

#### 2.1 头文件防卫式声明
```cpp
#pragma once  // 现代 C++ 推荐方式
```

**传统方式对比**：
```cpp
#ifndef MINIKV_H
#define MINIKV_H
// ... 代码 ...
#endif
```

**为什么使用 `#pragma once`**：
- 更简洁，不需要手动管理宏名称
- 编译器优化更好，编译速度更快
- 避免宏名称冲突

#### 2.2 头文件 vs 实现文件
- **头文件（.h）**：声明类的接口，告诉编译器"有什么"
- **实现文件（.cpp）**：定义类的实现，告诉编译器"怎么做"

**为什么要分离**：
- 加快编译速度（修改实现不需要重新编译所有依赖头文件的代码）
- 隐藏实现细节
- 便于团队协作（接口稳定，实现可以独立修改）

### 3. 命名空间（Namespace）

```cpp
namespace MiniKV {
    class Database { /* ... */ };
}

// 使用时
MiniKV::Database db;
```

**为什么使用命名空间**：
- 避免命名冲突（不同库可能有同名的类）
- 组织代码结构
- 提高代码可读性

**注意事项**：
- ❌ 不要在头文件中使用 `using namespace`（会污染全局命名空间）
- ✅ 可以在 .cpp 文件中使用（只影响当前文件）

### 4. STL 容器：std::unordered_map

#### 4.1 为什么选择 unordered_map？

| 容器 | 底层实现 | 查找复杂度 | 有序性 | 适用场景 |
|------|---------|-----------|--------|---------|
| `std::map` | 红黑树 | O(log n) | 有序 | 需要键有序 |
| `std::unordered_map` | 哈希表 | O(1) 平均 | 无序 | 只需快速查找 |

**我们的选择**：`unordered_map`
- 键值数据库不需要键的有序性
- 哈希表提供更快的查找速度
- 符合 Redis 等真实数据库的设计

#### 4.2 常用操作

```cpp
// 插入/更新
storage_["key"] = "value";  // operator[]

// 查找
auto it = storage_.find("key");
if (it != storage_.end()) {
    std::string value = it->second;  // 访问值
}

// 删除
size_t count = storage_.erase("key");  // 返回删除的元素数量

// 遍历
for (const auto& pair : storage_) {
    std::cout << pair.first << " => " << pair.second << std::endl;
}
```

### 5. 引用传递与常量引用

#### 5.1 参数传递方式对比

```cpp
// ❌ 值传递：会拷贝整个字符串（低效）
void bad_set(std::string key, std::string value);

// ✅ 常量引用：不拷贝，且保证不修改（高效且安全）
void good_set(const std::string& key, const std::string& value);

// ✅ 非常量引用：用于输出参数
bool get(const std::string& key, std::string& value);
```

**性能对比**：
- 值传递：拷贝整个字符串（可能几 KB）
- 引用传递：只传递地址（8 字节）

**何时使用 const 引用**：
- 输入参数（函数不修改参数）
- 参数是大对象（string, vector, 自定义类等）

**何时使用非 const 引用**：
- 输出参数（函数需要修改参数来返回结果）
- 例如：`bool get(const std::string& key, std::string& value)`

### 6. const 成员函数

```cpp
bool exists(const std::string& key) const;  // 注意最后的 const
//                                    ^^^^^ 表示该函数不修改对象状态
```

**为什么需要 const 成员函数**：
```cpp
const Database db;
db.exists("key");  // 只有 const 成员函数才能被 const 对象调用
```

**设计原则**：
- 不修改对象状态的函数都应该声明为 const
- 提高代码的安全性和可读性
- 允许 const 对象使用这些方法

### 7. 现代 C++ 特性

#### 7.1 auto 类型推导（C++11）
```cpp
// 传统写法（冗长）
std::unordered_map<std::string, std::string>::iterator it = storage_.find(key);

// 现代写法（简洁）
auto it = storage_.find(key);
```

**何时使用 auto**：
- 类型名很长或复杂时
- 类型显而易见时（如 `auto x = 5;`）

**何时不用 auto**：
- 类型不明显，影响代码可读性时

#### 7.2 基于范围的 for 循环（C++11）
```cpp
// 传统写法
for (auto it = storage_.begin(); it != storage_.end(); ++it) {
    std::cout << it->first << " => " << it->second << std::endl;
}

// 现代写法
for (const auto& pair : storage_) {
    std::cout << pair.first << " => " << pair.second << std::endl;
}
```

**注意**：使用 `const auto&` 避免拷贝，提高性能。

## 🚨 常见陷阱与避坑指南

### 陷阱 1：operator[] 的副作用
```cpp
// ❌ 错误：在 const 函数中使用 operator[]
bool Database::get(const std::string& key, std::string& value) const {
    value = storage_[key];  // 编译错误！operator[] 不是 const 函数
    return true;
}
```

**原因**：`operator[]` 在键不存在时会插入新元素，所以不能是 const 函数。

**正确做法**：使用 `find()` 方法。

### 陷阱 2：忘记检查 find() 的返回值
```cpp
// ❌ 危险：没有检查迭代器是否有效
auto it = storage_.find(key);
std::string value = it->second;  // 如果 key 不存在，这里会崩溃！

// ✅ 正确：先检查
auto it = storage_.find(key);
if (it != storage_.end()) {
    std::string value = it->second;
}
```

### 陷阱 3：在头文件中使用 using namespace
```cpp
// ❌ 绝对不要在头文件中这样做
using namespace std;  // 会污染所有包含此头文件的代码

// ✅ 在 .cpp 文件中可以使用（仅影响当前文件）
using namespace std;
```

### 陷阱 4：值传递大对象
```cpp
// ❌ 低效：每次调用都拷贝字符串
void set(std::string key, std::string value);

// ✅ 高效：使用常量引用
void set(const std::string& key, const std::string& value);
```

## 🛠️ 编译与运行

### 方式 1：运行自动化测试（推荐用于验证功能）

**Windows 系统**：
```cmd
scripts\build.bat
```

**Linux/Mac 系统**：
```bash
chmod +x scripts/build.sh
./scripts/build.sh
```

这会编译并运行完整的测试套件，验证所有功能是否正常。

### 方式 2：运行交互式 CLI（推荐用于实际使用）⭐

**Windows 系统**：
```cmd
scripts\build_cli.bat
```

**Linux/Mac 系统**：
```bash
chmod +x scripts/build_cli.sh
./scripts/build_cli.sh
```

这会启动一个类似 Redis 的交互式命令行界面，您可以像使用真实数据库一样操作 Mini-KV。

**CLI 界面示例**：
```
mini-kv> SET name 张三
✓ OK (新建)

mini-kv> GET name
"张三"

mini-kv> HELP
(显示所有可用命令)
```

详细使用方法请参考 `docs/guides/CLI_使用指南.md`。

### 方式 3：清理构建产物

**Windows 系统**：
```cmd
scripts\clean.bat
```

**Linux/Mac 系统**：
```bash
chmod +x scripts/clean.sh
./scripts/clean.sh
```

### 手动编译命令

**编译测试版本**：
```bash
# 创建 build 目录
mkdir -p build

# 编译
g++ -std=c++11 -c src/MiniKV.cpp -o build/MiniKV.o
g++ -std=c++11 -c tests/test_main.cpp -o build/test_main.o
g++ build/MiniKV.o build/test_main.o -o build/mini_kv_test

# 运行
./build/mini_kv_test
```

**编译 CLI 版本**：
```bash
# 创建 build 目录
mkdir -p build

# 编译
g++ -std=c++11 -c src/MiniKV.cpp -o build/MiniKV.o
g++ -std=c++11 build/MiniKV.o src/cli_main.cpp -o build/mini_kv_cli

# 运行
./build/mini_kv_cli
```

## 📖 扩展学习建议

### 1. 深入理解 STL 容器
- 阅读 `std::unordered_map` 的源码实现
- 对比 `map` 和 `unordered_map` 的性能差异
- 学习哈希表的冲突解决策略

### 2. 练习题
1. 为 Database 类添加一个 `keys()` 方法，返回所有键的列表
2. 实现一个 `values()` 方法，返回所有值的列表
3. 添加一个 `contains_value()` 方法，检查某个值是否存在
4. 实现批量操作：`mset()` 和 `mget()`

### 3. 性能测试
- 测试插入 10 万条数据的性能
- 对比 `map` 和 `unordered_map` 的查找速度
- 分析内存占用情况

### 4. CLI 功能扩展（进阶）
- 添加命令历史记录功能（使用 `std::vector` 存储历史命令）
- 实现 Tab 键自动补全（需要学习终端控制）
- 添加 `MSET` 和 `MGET` 批量操作命令
- 实现命令别名功能（例如 `LS` 作为 `KEYS` 的别名）

### 5. 学习 REPL 设计模式
- 研究其他 REPL 程序（Python、Node.js、Redis）
- 理解命令解析的不同实现方式
- 学习如何设计用户友好的交互界面

## 🎓 设计模式与最佳实践

### 1. RAII（资源获取即初始化）
- 构造函数获取资源，析构函数释放资源
- STL 容器自动管理内存，无需手动 delete

### 2. 接口设计原则
- 使用 const 引用传递输入参数
- 使用非 const 引用传递输出参数
- 不修改对象状态的方法声明为 const

### 3. 错误处理策略
- 当前版本使用返回值表示成功/失败（bool）
- Phase 2 将引入异常处理机制

## 🔜 下一阶段预告

Phase 2 将引入：
- **文件持久化**：将数据保存到磁盘
- **异常处理**：使用 try-catch 处理错误
- **智能指针**：使用 `std::unique_ptr` 管理资源
- **操作符重载**：重载 `<<` 操作符

## 📝 总结

Phase 1 是整个项目的基础，掌握了：
- ✅ 类的封装与接口设计
- ✅ STL 容器的使用
- ✅ 引用传递与 const 正确性
- ✅ 现代 C++ 语法（auto, 范围 for）
- ✅ 头文件与源文件分离

这些知识是后续阶段的基石，务必理解透彻！
