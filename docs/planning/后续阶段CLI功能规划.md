# Mini-KV 后续阶段 CLI 功能规划

## 📋 概述

每个 Phase 的新功能都会在交互式 CLI 中体现，让您可以直观地测试和使用新特性。

---

## Phase 2：持久化与健壮性

### 🎯 核心 C++ 特性
- 文件流操作（`<fstream>`）
- 异常处理（`try-catch-throw`）
- 智能指针（`std::unique_ptr`）
- 操作符重载（`<<` 操作符）

### 🆕 新增 CLI 命令

#### 1. SAVE - 保存数据到磁盘

**语法**：
```
SAVE [filename]
```

**示例**：
```
mini-kv> SET user:1001:name 张三
✓ OK (新建)

mini-kv> SET user:1001:age 25
✓ OK (新建)

mini-kv> SAVE
✓ 数据已保存到 mini_kv.db (2 个键值对)

mini-kv> SAVE backup.db
✓ 数据已保存到 backup.db (2 个键值对)
```

**功能说明**：
- 将内存中的所有数据持久化到磁盘文件
- 默认文件名：`mini_kv.db`
- 可以指定自定义文件名
- 显示保存的键值对数量

---

#### 2. LOAD - 从磁盘加载数据

**语法**：
```
LOAD [filename]
```

**示例**：
```
mini-kv> LOAD
✓ 从 mini_kv.db 加载了 2 个键值对

mini-kv> LOAD backup.db
✓ 从 backup.db 加载了 5 个键值对

mini-kv> LOAD nonexistent.db
❌ 错误: 文件不存在
```

**功能说明**：
- 从磁盘文件加载数据到内存
- 会覆盖当前内存中的数据（需要确认）
- 显示加载的键值对数量
- 异常处理：文件不存在、格式错误等

---

#### 3. AUTOSAVE - 自动保存设置

**语法**：
```
AUTOSAVE ON|OFF
AUTOSAVE STATUS
```

**示例**：
```
mini-kv> AUTOSAVE ON
✓ 自动保存已启用（每 10 次操作自动保存）

mini-kv> AUTOSAVE OFF
✓ 自动保存已禁用

mini-kv> AUTOSAVE STATUS
自动保存状态: 启用
保存间隔: 每 10 次操作
上次保存: 2024-01-15 10:30:00
```

**功能说明**：
- 启用/禁用自动保存功能
- 每 N 次操作自动保存到磁盘
- 查看自动保存状态

---

#### 4. BACKUP - 创建备份

**语法**：
```
BACKUP
```

**示例**：
```
mini-kv> BACKUP
✓ 备份已创建: mini_kv_backup_20240115_103000.db
```

**功能说明**：
- 创建带时间戳的备份文件
- 不影响当前数据库状态

---

#### 5. 增强的错误处理

**示例**：
```
mini-kv> LOAD corrupted.db
❌ 错误: 文件格式损坏
   详细信息: 第 5 行解析失败
   建议: 请检查文件格式或使用备份文件

mini-kv> SAVE /invalid/path/file.db
❌ 错误: 无法写入文件
   详细信息: 权限不足或路径不存在
```

---

### 📊 CLI 界面增强

#### INFO 命令增强

```
mini-kv> INFO

═══════════ 数据库统计信息 ═══════════
  键值对数量: 5
  总操作次数: 12
  数据库版本: Mini-KV v2.0 (Phase 2)
  
  持久化信息:
    数据文件: mini_kv.db
    上次保存: 2024-01-15 10:30:00
    自动保存: 启用 (每 10 次操作)
    备份数量: 3
═══════════════════════════════════════
```

---

## Phase 3：高级抽象与泛型编程

### 🎯 核心 C++ 特性
- 模板编程（`template <typename T>`）
- `std::variant` / `std::any`
- Lambda 表达式
- 移动语义（`std::move`）

### 🆕 新增 CLI 命令

#### 1. SETINT / SETDOUBLE - 设置不同类型的值

**语法**：
```
SETINT <key> <integer>
SETDOUBLE <key> <double>
SETLIST <key> <value1> <value2> ...
```

**示例**：
```
mini-kv> SETINT age 25
✓ OK (类型: Integer)

mini-kv> SETDOUBLE price 99.99
✓ OK (类型: Double)

mini-kv> SETLIST tags C++ Database Learning
✓ OK (类型: List, 3 个元素)

mini-kv> SET name 张三
✓ OK (类型: String)
```

**功能说明**：
- 支持多种数据类型
- 自动类型推导和验证
- 类型安全的存储

---

#### 2. TYPE - 查询值的类型

**语法**：
```
TYPE <key>
```

**示例**：
```
mini-kv> TYPE age
Integer

mini-kv> TYPE price
Double

mini-kv> TYPE name
String

mini-kv> TYPE tags
List
```

---

#### 3. INCR / DECR - 整数自增/自减

**语法**：
```
INCR <key> [increment]
DECR <key> [decrement]
```

**示例**：
```
mini-kv> SETINT counter 10
✓ OK (类型: Integer)

mini-kv> INCR counter
11

mini-kv> INCR counter 5
16

mini-kv> DECR counter 3
13

mini-kv> INCR name
❌ 错误: 键 'name' 的类型不是 Integer
```

---

#### 4. FILTER - 条件查询（Lambda 表达式）

**语法**：
```
FILTER <condition>
```

**示例**：
```
mini-kv> SETINT user:1001:age 25
mini-kv> SETINT user:1002:age 30
mini-kv> SETINT user:1003:age 20

mini-kv> FILTER age > 22
找到 2 个匹配的键值对:
  [user:1001:age] => 25
  [user:1002:age] => 30

mini-kv> FILTER key contains "user"
找到 3 个匹配的键值对:
  [user:1001:age] => 25
  [user:1002:age] => 30
  [user:1003:age] => 20

mini-kv> FILTER value == "张三"
找到 1 个匹配的键值对:
  [user:1001:name] => "张三"
```

**功能说明**：
- 支持条件表达式（>, <, ==, !=, contains）
- 可以对键或值进行过滤
- 返回所有匹配的键值对

---

#### 5. LLEN / LGET - 列表操作

**语法**：
```
LLEN <key>
LGET <key> <index>
LRANGE <key> <start> <end>
```

**示例**：
```
mini-kv> SETLIST tags C++ Database Learning
✓ OK (类型: List, 3 个元素)

mini-kv> LLEN tags
3

mini-kv> LGET tags 0
"C++"

mini-kv> LGET tags 1
"Database"

mini-kv> LRANGE tags 0 2
1) "C++"
2) "Database"
3) "Learning"
```

---

#### 6. KEYS 命令增强（支持模式匹配）

**语法**：
```
KEYS [pattern]
```

**示例**：
```
mini-kv> KEYS
(显示所有键)

mini-kv> KEYS user:*
找到 3 个匹配的键:
  user:1001:name
  user:1001:age
  user:1002:name

mini-kv> KEYS *:age
找到 2 个匹配的键:
  user:1001:age
  user:1002:age
```

---

### 📊 CLI 界面增强

#### INFO 命令增强

```
mini-kv> INFO

═══════════ 数据库统计信息 ═══════════
  键值对数量: 10
  总操作次数: 25
  数据库版本: Mini-KV v3.0 (Phase 3)
  
  类型分布:
    String: 5 个
    Integer: 3 个
    Double: 1 个
    List: 1 个
  
  持久化信息:
    数据文件: mini_kv.db
    上次保存: 2024-01-15 10:30:00
═══════════════════════════════════════
```

---

## Phase 4：并发安全

### 🎯 核心 C++ 特性
- 多线程（`<thread>`）
- 互斥锁（`std::mutex`）
- 读写锁（`std::shared_mutex`）
- 条件变量（`std::condition_variable`）

### 🆕 新增 CLI 命令

#### 1. MULTI / EXEC - 事务支持

**语法**：
```
MULTI
<commands>
EXEC
```

**示例**：
```
mini-kv> MULTI
✓ 进入事务模式

mini-kv(TX)> SET user:1001:name 张三
QUEUED

mini-kv(TX)> SETINT user:1001:age 25
QUEUED

mini-kv(TX)> SET user:1001:email zhangsan@example.com
QUEUED

mini-kv(TX)> EXEC
✓ 事务执行成功 (3 个命令)
1) OK
2) OK
3) OK

mini-kv> MULTI
✓ 进入事务模式

mini-kv(TX)> SET key1 value1
QUEUED

mini-kv(TX)> DISCARD
✓ 事务已取消
```

**功能说明**：
- 原子性执行多个命令
- 命令在 EXEC 前不会真正执行
- 支持 DISCARD 取消事务

---

#### 2. WATCH - 监视键（乐观锁）

**语法**：
```
WATCH <key> [key ...]
```

**示例**：
```
mini-kv> WATCH balance
✓ 正在监视键: balance

mini-kv> MULTI
✓ 进入事务模式

mini-kv(TX)> SETINT balance 100
QUEUED

mini-kv(TX)> EXEC
❌ 事务失败: 键 'balance' 已被其他客户端修改
```

**功能说明**：
- 监视键的变化
- 如果键在事务执行前被修改，事务会失败
- 实现乐观锁机制

---

#### 3. CLIENT - 客户端管理

**语法**：
```
CLIENT LIST
CLIENT ID
CLIENT KILL <id>
```

**示例**：
```
mini-kv> CLIENT LIST
客户端列表:
  ID: 1, 连接时间: 10:30:00, 命令数: 15
  ID: 2, 连接时间: 10:35:00, 命令数: 8
  ID: 3, 连接时间: 10:40:00, 命令数: 3

mini-kv> CLIENT ID
当前客户端 ID: 1

mini-kv> CLIENT KILL 3
✓ 客户端 3 已断开连接
```

**功能说明**：
- 查看所有连接的客户端
- 查看当前客户端 ID
- 强制断开指定客户端

---

#### 4. MONITOR - 实时监控

**语法**：
```
MONITOR
```

**示例**：
```
mini-kv> MONITOR
✓ 进入监控模式（按 Ctrl+C 退出）

[10:30:15] Client 2: SET user:1001:name 张三
[10:30:16] Client 3: GET user:1001:name
[10:30:17] Client 2: SETINT counter 10
[10:30:18] Client 3: INCR counter
[10:30:19] Client 2: SAVE
```

**功能说明**：
- 实时显示所有客户端的命令
- 用于调试和监控
- 显示时间戳和客户端 ID

---

#### 5. BENCHMARK - 性能测试

**语法**：
```
BENCHMARK <command> <count>
```

**示例**：
```
mini-kv> BENCHMARK SET 10000
正在执行 10000 次 SET 操作...
========================================
  总耗时: 125.5 ms
  平均耗时: 0.0126 ms/op
  吞吐量: 79,681 ops/sec
========================================

mini-kv> BENCHMARK GET 10000
正在执行 10000 次 GET 操作...
========================================
  总耗时: 98.3 ms
  平均耗时: 0.0098 ms/op
  吞吐量: 101,729 ops/sec
========================================
```

**功能说明**：
- 测试命令的性能
- 显示平均耗时和吞吐量
- 用于性能调优

---

#### 6. LOCK / UNLOCK - 手动锁管理（调试用）

**语法**：
```
LOCK <key>
UNLOCK <key>
```

**示例**：
```
mini-kv> LOCK user:1001
✓ 键 'user:1001' 已锁定

mini-kv> SET user:1001:name 张三
✓ OK (持有锁)

mini-kv> UNLOCK user:1001
✓ 键 'user:1001' 已解锁
```

**功能说明**：
- 手动锁定/解锁键
- 用于调试并发问题
- 显示锁的持有者

---

### 📊 CLI 界面增强

#### INFO 命令增强

```
mini-kv> INFO

═══════════ 数据库统计信息 ═══════════
  键值对数量: 10
  总操作次数: 25
  数据库版本: Mini-KV v4.0 (Phase 4)
  
  类型分布:
    String: 5 个
    Integer: 3 个
    Double: 1 个
    List: 1 个
  
  并发信息:
    活跃客户端: 3
    读操作数: 150
    写操作数: 75
    锁等待数: 2
    平均响应时间: 0.5 ms
  
  持久化信息:
    数据文件: mini_kv.db
    上次保存: 2024-01-15 10:30:00
═══════════════════════════════════════
```

---

## 🎨 CLI 界面演进

### Phase 1（当前）
```
mini-kv>
```

### Phase 2
```
mini-kv> (带持久化状态指示)
mini-kv[*]> (有未保存的修改)
```

### Phase 3
```
mini-kv[10]> (显示键值对数量)
```

### Phase 4
```
mini-kv[10|3]> (显示键值对数量和客户端数量)
mini-kv(TX)[10|3]> (事务模式)
```

---

## 📈 功能对比表

| 功能 | Phase 1 | Phase 2 | Phase 3 | Phase 4 |
|------|---------|---------|---------|---------|
| 基础 KV 操作 | ✅ | ✅ | ✅ | ✅ |
| 持久化 | ❌ | ✅ | ✅ | ✅ |
| 多数据类型 | ❌ | ❌ | ✅ | ✅ |
| 条件查询 | ❌ | ❌ | ✅ | ✅ |
| 事务支持 | ❌ | ❌ | ❌ | ✅ |
| 并发控制 | ❌ | ❌ | ❌ | ✅ |
| 性能监控 | ❌ | ❌ | ❌ | ✅ |

---

## 🎯 总结

每个 Phase 都会在 CLI 中增加新的命令和功能：

- **Phase 2**：持久化相关命令（SAVE, LOAD, BACKUP）
- **Phase 3**：多类型支持和高级查询（SETINT, FILTER, LGET）
- **Phase 4**：并发和事务支持（MULTI/EXEC, WATCH, MONITOR）

这样，您可以通过交互式 CLI 直观地体验和测试每个阶段的新特性，就像使用真实的 Redis 一样！🚀
