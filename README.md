# Mini-KV - 轻量级内存键值数据库

> 一个用于学习现代 C++ 的教学项目，从零构建类似 Redis 的键值数据库

## 🎯 项目简介

Mini-KV 是一个纯 C++ 实现的轻量级内存键值数据库，旨在通过实际项目学习 C++ 的核心特性。项目分为 4 个阶段（Phase），每个阶段引入不同的 C++ 特性和设计模式。

### 为什么选择这个项目？

✅ **实用性强**：构建一个真实可用的数据库  
✅ **循序渐进**：从基础到高级，逐步深入  
✅ **纯净 C++**：不依赖任何第三方库，只用标准库  
✅ **详细注释**：每行代码都解释"为什么这么写"  
✅ **配套文档**：每个阶段都有完整的学习指引  

---

## 📦 当前进度：Phase 1 ✅

### Phase 1：基础骨架（面向对象与基础 STL）

**已实现功能**：
- ✅ 基础 CRUD 操作（SET, GET, DEL, EXISTS）
- ✅ 数据库管理（SIZE, CLEAR, INFO）
- ✅ 完整的测试套件（7 个测试用例）
- ✅ 交互式 CLI 界面（类似 Redis）

**涵盖的 C++ 特性**：
- 类与对象（封装、构造/析构函数）
- 头文件与源文件分离
- 命名空间（`namespace MiniKV`）
- STL 容器（`std::unordered_map`）
- 引用传递与常量引用
- const 成员函数
- 现代 C++ 特性（`auto`、范围 for 循环）

---

## 🚀 快速开始

### 环境要求

- **编译器**：支持 C++11 的编译器（g++, clang++, MSVC）
- **操作系统**：Windows / Linux / macOS
- **推荐 IDE**：VS Code, CLion, Visual Studio

### 编译运行

#### 方式 1：运行自动化测试

```bash
# Windows
scripts\build.bat

# Linux/Mac
chmod +x scripts/build.sh
./scripts/build.sh
```

#### 方式 2：运行交互式 CLI（推荐）⭐

```bash
# Windows
scripts\build_cli.bat

# Linux/Mac
chmod +x scripts/build_cli.sh
./scripts/build_cli.sh
```

#### 方式 3：清理构建产物

```bash
# Windows
scripts\clean.bat

# Linux/Mac
chmod +x scripts/clean.sh
./scripts/clean.sh
```

### CLI 使用示例

```
mini-kv> SET name 张三
✓ OK (新建)

mini-kv> GET name
"张三"

mini-kv> SET age 25
✓ OK (新建)

mini-kv> KEYS
数据库中的所有键值对:
========== Mini-KV 数据库内容 ==========
总键值对数量: 2
总操作次数: 2
----------------------------------------
  [name] => "张三"
  [age] => "25"
========================================

mini-kv> INFO

═══════════ 数据库统计信息 ═══════════
  键值对数量: 2
  总操作次数: 2
  数据库版本: Mini-KV v1.0 (Phase 1)
═══════════════════════════════════════

mini-kv> HELP
(显示所有可用命令)

mini-kv> QUIT
再见！感谢使用 Mini-KV。
```

---

## 📂 项目结构

```
Mini-KV/
├── .kiro/
│   └── steering/
│       ├── protocol.md              # 项目开发规范
│       └── file-organization.md     # 文件组织规则
├── include/
│   └── MiniKV.h                     # 数据库类的头文件声明
├── src/
│   ├── MiniKV.cpp                   # 数据库类的实现
│   └── cli_main.cpp                 # 交互式 CLI 主程序
├── tests/
│   └── test_main.cpp                # 自动化测试套件
├── docs/
│   ├── guides/
│   │   ├── CLI_使用指南.md          # CLI 使用手册
│   │   └── 中文乱码解决方案.md      # 编码问题解决指南
│   ├── phases/
│   │   └── Phase1_README_Guide.md   # Phase 1 学习指引
│   └── planning/
│       ├── 后续阶段CLI功能规划.md   # 后续功能规划
│       └── CLI功能演进对比.md       # 功能演进对比
├── scripts/
│   ├── build.bat                    # Windows 测试编译脚本
│   ├── build_cli.bat                # Windows CLI 编译脚本
│   ├── build.sh                     # Linux/Mac 测试编译脚本
│   ├── build_cli.sh                 # Linux/Mac CLI 编译脚本
│   └── clean.bat                    # 清理脚本
├── build/                           # 构建产物目录（.gitignore）
├── data/                            # 数据文件目录（Phase 2+）
├── .gitignore                       # Git 忽略规则
└── README.md                        # 本文件（项目主文档）
```

---

## 📚 学习路径

### 1. 阅读文档（推荐顺序）

1. **README.md**（本文件）- 项目概览
2. **Phase1_README_Guide.md** - Phase 1 详细学习指引
3. **CLI_使用指南.md** - 交互式界面使用手册
4. **中文乱码解决方案.md** - Windows 编码问题解决

### 2. 阅读源码（推荐顺序）

1. **include/MiniKV.h** - 理解类的接口设计
2. **src/MiniKV.cpp** - 学习实现细节和 C++ 特性
3. **tests/test_main.cpp** - 学习如何编写测试
4. **src/cli_main.cpp** - 学习 REPL 模式和命令解析

### 3. 动手实践

1. 运行 `build.bat` 查看测试结果
2. 运行 `build_cli.bat` 体验交互式界面
3. 尝试修改代码，添加新功能
4. 完成 Phase1_README_Guide.md 中的练习题

---

## 🎓 核心知识点

### Phase 1 涵盖的 C++ 特性

| 特性 | 说明 | 代码位置 |
|------|------|---------|
| **类与对象** | 封装、构造/析构函数 | `MiniKV.h`, `MiniKV.cpp` |
| **头文件防卫** | `#pragma once` | `MiniKV.h` |
| **命名空间** | `namespace MiniKV` | 所有文件 |
| **STL 容器** | `std::unordered_map` | `MiniKV.cpp` |
| **引用传递** | `const std::string&` | `MiniKV.h` |
| **const 成员函数** | 不修改对象状态的方法 | `MiniKV.h` |
| **auto 类型推导** | 简化复杂类型声明 | `MiniKV.cpp` |
| **范围 for 循环** | 遍历容器的现代写法 | `MiniKV.cpp` |
| **字符串流** | `std::istringstream` | `cli_main.cpp` |
| **Lambda 表达式** | 匿名函数 | `cli_main.cpp` |

---

## 🔜 后续阶段预告

> 💡 **提示**：每个阶段的新功能都会在交互式 CLI 中体现！详见 [后续阶段CLI功能规划.md](后续阶段CLI功能规划.md)

### Phase 2：持久化与健壮性（计划中）

**功能**：
- 文件持久化（保存/加载数据）
- 异常处理机制
- 智能指针（`std::unique_ptr`）
- 操作符重载（`<<` 操作符）

**新增 C++ 特性**：
- 文件流操作（`<fstream>`）
- 异常处理（`try-catch-throw`）
- 自定义异常类
- 现代内存管理

**新增 CLI 命令**：
- `SAVE` / `LOAD` - 持久化数据
- `BACKUP` - 创建备份
- `AUTOSAVE` - 自动保存设置

---

### Phase 3：高级抽象与泛型编程（计划中）

**功能**：
- 支持多种数据类型（int, double, list）
- 条件查询（Lambda 过滤器）
- 移动语义优化

**新增 C++ 特性**：
- 模板编程（`template <typename T>`）
- `std::variant` / `std::any`
- Lambda 表达式高级用法
- 右值引用与移动语义（`std::move`）

**新增 CLI 命令**：
- `SETINT` / `SETDOUBLE` / `SETLIST` - 多类型支持
- `TYPE` - 查询值类型
- `INCR` / `DECR` - 整数操作
- `FILTER` - 条件查询
- `LLEN` / `LGET` - 列表操作

---

### Phase 4：并发安全（计划中）

**功能**：
- 多线程并发访问
- 读写锁优化
- 事务支持

**新增 C++ 特性**：
- 多线程（`<thread>`）
- 互斥锁（`std::mutex`, `std::lock_guard`）
- 读写锁（`std::shared_mutex`）
- 条件变量（`std::condition_variable`）

**新增 CLI 命令**：
- `MULTI` / `EXEC` / `DISCARD` - 事务支持
- `WATCH` - 乐观锁
- `CLIENT LIST` / `CLIENT KILL` - 客户端管理
- `MONITOR` - 实时监控
- `BENCHMARK` - 性能测试

---

## 🆚 与 Redis 的对比

| 特性 | Redis | Mini-KV Phase 1 | 后续阶段 |
|------|-------|----------------|---------|
| 基础 KV 操作 | ✅ | ✅ | - |
| 交互式 CLI | ✅ | ✅ | - |
| 持久化 | ✅ | ❌ | Phase 2 |
| 多数据类型 | ✅ | ❌ | Phase 3 |
| 并发支持 | ✅ | ❌ | Phase 4 |
| 网络协议 | ✅ | ❌ | 未计划 |
| 集群模式 | ✅ | ❌ | 未计划 |

---

## 💡 设计理念

### 1. 纯净主义（Pure C++）

- ❌ 不使用任何第三方库（Boost, Qt, nlohmann_json 等）
- ✅ 只使用 C++11/14/17 标准库
- ✅ 所有功能从零实现（包括测试框架）

### 2. 导师模式（Mentor Mode）

- 代码注释不仅解释"做什么"，更解释"为什么"
- 每个 C++ 特性都有详细说明
- 提供常见陷阱的避坑指南

### 3. 渐进式交付（Progressive）

- 不一次性引入所有复杂特性
- 每个阶段对应一组核心 C++ 特性
- 循序渐进，由浅入深

### 4. 学习辅助（Learning Aids）

- 每个阶段配套学习指引文档
- 提供练习题和扩展建议
- 包含性能测试和对比分析

---

## 🤝 贡献指南

这是一个教学项目，欢迎提出改进建议！

### 如何贡献

1. Fork 本项目
2. 创建特性分支（`git checkout -b feature/AmazingFeature`）
3. 提交更改（`git commit -m 'Add some AmazingFeature'`）
4. 推送到分支（`git push origin feature/AmazingFeature`）
5. 开启 Pull Request

### 贡献方向

- 改进代码注释和文档
- 添加更多测试用例
- 优化性能
- 修复 Bug
- 添加新功能（需符合教学目标）

---


## 🎉 开始学习

现在就运行 `build_cli.bat`，开启您的 C++ 学习之旅吧！

```bash
# Windows
build_cli.bat

# 然后在 CLI 中尝试：
mini-kv> SET hello world
mini-kv> GET hello
mini-kv> HELP
```

祝学习愉快！🚀
