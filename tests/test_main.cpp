#include "../include/MiniKV.h"
#include <iostream>
#include <cassert>

// [C++特性说明]: 简易测试框架
// 这里不使用第三方测试库（如 Google Test），而是用 assert 和自定义宏
// 这样可以学习如何从零构建测试工具

// 测试辅助宏
#define TEST_CASE(name) \
    std::cout << "\n[测试] " << name << std::endl;

#define ASSERT_TRUE(condition, message) \
    if (!(condition)) { \
        std::cerr << "  ❌ 断言失败: " << message << std::endl; \
        std::cerr << "     条件: " #condition << std::endl; \
        return false; \
    } else { \
        std::cout << "  ✓ " << message << std::endl; \
    }

#define ASSERT_FALSE(condition, message) \
    ASSERT_TRUE(!(condition), message)

#define ASSERT_EQUAL(actual, expected, message) \
    if ((actual) != (expected)) { \
        std::cerr << "  ❌ 断言失败: " << message << std::endl; \
        std::cerr << "     期望值: " << (expected) << std::endl; \
        std::cerr << "     实际值: " << (actual) << std::endl; \
        return false; \
    } else { \
        std::cout << "  ✓ " << message << std::endl; \
    }

// [C++特性说明]: 使用命名空间简化代码
using namespace MiniKV;

/**
 * 测试基本的 SET 和 GET 操作
 */
bool test_basic_set_get() {
    TEST_CASE("基本的 SET 和 GET 操作");
    
    Database db;
    
    // 测试插入新键
    bool is_new = db.set("name", "张三");
    ASSERT_TRUE(is_new, "插入新键应该返回 true");
    
    // 测试获取已存在的键
    std::string value;
    bool found = db.get("name", value);
    ASSERT_TRUE(found, "应该能找到刚插入的键");
    ASSERT_EQUAL(value, "张三", "获取的值应该与插入的值相同");
    
    // 测试更新已存在的键
    is_new = db.set("name", "李四");
    ASSERT_FALSE(is_new, "更新已存在的键应该返回 false");
    
    found = db.get("name", value);
    ASSERT_TRUE(found, "更新后应该能找到键");
    ASSERT_EQUAL(value, "李四", "获取的值应该是更新后的值");
    
    return true;
}

/**
 * 测试 GET 不存在的键
 */
bool test_get_nonexistent() {
    TEST_CASE("GET 不存在的键");
    
    Database db;
    std::string value;
    
    bool found = db.get("nonexistent", value);
    ASSERT_FALSE(found, "查询不存在的键应该返回 false");
    
    return true;
}

/**
 * 测试 DEL 操作
 */
bool test_delete() {
    TEST_CASE("DEL 删除操作");
    
    Database db;
    
    // 先插入数据
    db.set("key1", "value1");
    db.set("key2", "value2");
    
    // 删除存在的键
    bool deleted = db.del("key1");
    ASSERT_TRUE(deleted, "删除存在的键应该返回 true");
    
    // 验证键已被删除
    std::string value;
    bool found = db.get("key1", value);
    ASSERT_FALSE(found, "删除后不应该能找到该键");
    
    // 删除不存在的键
    deleted = db.del("nonexistent");
    ASSERT_FALSE(deleted, "删除不存在的键应该返回 false");
    
    // 验证其他键未受影响
    found = db.get("key2", value);
    ASSERT_TRUE(found, "其他键不应该受删除操作影响");
    ASSERT_EQUAL(value, "value2", "其他键的值应该保持不变");
    
    return true;
}

/**
 * 测试 EXISTS 操作
 */
bool test_exists() {
    TEST_CASE("EXISTS 检查键是否存在");
    
    Database db;
    
    // 检查不存在的键
    ASSERT_FALSE(db.exists("key1"), "不存在的键应该返回 false");
    
    // 插入键后检查
    db.set("key1", "value1");
    ASSERT_TRUE(db.exists("key1"), "存在的键应该返回 true");
    
    // 删除后检查
    db.del("key1");
    ASSERT_FALSE(db.exists("key1"), "删除后的键应该返回 false");
    
    return true;
}

/**
 * 测试 SIZE 和 CLEAR 操作
 */
bool test_size_and_clear() {
    TEST_CASE("SIZE 和 CLEAR 操作");
    
    Database db;
    
    // 初始大小应该为 0
    ASSERT_EQUAL(db.size(), static_cast<size_t>(0), "初始数据库大小应该为 0");
    
    // 插入数据后检查大小
    db.set("key1", "value1");
    db.set("key2", "value2");
    db.set("key3", "value3");
    ASSERT_EQUAL(db.size(), static_cast<size_t>(3), "插入 3 个键后大小应该为 3");
    
    // 更新已存在的键不应该改变大小
    db.set("key1", "new_value");
    ASSERT_EQUAL(db.size(), static_cast<size_t>(3), "更新键不应该改变大小");
    
    // 清空数据库
    db.clear();
    ASSERT_EQUAL(db.size(), static_cast<size_t>(0), "清空后大小应该为 0");
    ASSERT_FALSE(db.exists("key1"), "清空后不应该存在任何键");
    
    return true;
}

/**
 * 测试操作计数功能
 */
bool test_operation_count() {
    TEST_CASE("操作计数功能");
    
    Database db;
    
    ASSERT_EQUAL(db.getOperationCount(), static_cast<size_t>(0), 
                 "初始操作计数应该为 0");
    
    db.set("key1", "value1");  // +1
    db.set("key2", "value2");  // +1
    ASSERT_EQUAL(db.getOperationCount(), static_cast<size_t>(2), 
                 "执行 2 次 SET 后计数应该为 2");
    
    db.del("key1");  // +1
    ASSERT_EQUAL(db.getOperationCount(), static_cast<size_t>(3), 
                 "执行 DEL 后计数应该为 3");
    
    db.clear();  // +1
    ASSERT_EQUAL(db.getOperationCount(), static_cast<size_t>(4), 
                 "执行 CLEAR 后计数应该为 4");
    
    return true;
}

/**
 * 综合测试：模拟真实使用场景
 */
bool test_real_world_scenario() {
    TEST_CASE("综合场景：用户信息管理");
    
    Database db;
    
    // 存储用户信息
    db.set("user:1001:name", "张三");
    db.set("user:1001:email", "zhangsan@example.com");
    db.set("user:1001:age", "25");
    
    db.set("user:1002:name", "李四");
    db.set("user:1002:email", "lisi@example.com");
    
    // 查询用户信息
    std::string name, email;
    ASSERT_TRUE(db.get("user:1001:name", name), "应该能获取用户名");
    ASSERT_EQUAL(name, "张三", "用户名应该正确");
    
    ASSERT_TRUE(db.get("user:1001:email", email), "应该能获取邮箱");
    ASSERT_EQUAL(email, "zhangsan@example.com", "邮箱应该正确");
    
    // 更新用户信息
    db.set("user:1001:age", "26");
    std::string age;
    db.get("user:1001:age", age);
    ASSERT_EQUAL(age, "26", "年龄应该已更新");
    
    // 删除用户
    db.del("user:1002:name");
    db.del("user:1002:email");
    ASSERT_FALSE(db.exists("user:1002:name"), "用户信息应该已删除");
    
    // 验证数据库状态
    ASSERT_EQUAL(db.size(), static_cast<size_t>(3), 
                 "删除 2 个键后应该剩余 3 个键");
    
    return true;
}

// [C++特性说明]: main 函数是程序入口
// 返回 0 表示成功，非 0 表示失败
int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  Mini-KV Phase 1 测试套件" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // 运行所有测试
    int passed = 0;
    int total = 0;
    
    // [C++特性说明]: 使用数组存储函数指针
    // 这样可以方便地批量运行测试
    bool (*tests[])() = {
        test_basic_set_get,
        test_get_nonexistent,
        test_delete,
        test_exists,
        test_size_and_clear,
        test_operation_count,
        test_real_world_scenario
    };
    
    total = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < total; ++i) {
        if (tests[i]()) {
            ++passed;
        }
    }
    
    // 打印测试结果
    std::cout << "\n========================================" << std::endl;
    std::cout << "测试结果: " << passed << "/" << total << " 通过" << std::endl;
    
    if (passed == total) {
        std::cout << "🎉 所有测试通过！" << std::endl;
    } else {
        std::cout << "❌ 有 " << (total - passed) << " 个测试失败" << std::endl;
    }
    std::cout << "========================================" << std::endl;
    
    // 演示数据库功能
    std::cout << "\n========== 功能演示 ==========" << std::endl;
    Database demo_db;
    demo_db.set("language", "C++");
    demo_db.set("version", "17");
    demo_db.set("project", "Mini-KV");
    demo_db.printAll();
    
    return (passed == total) ? 0 : 1;
}
