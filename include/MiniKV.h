#pragma once
// [C++特性说明]: 使用 #pragma once 防止头文件被重复包含，这是现代 C++ 的推荐做法
// 相比传统的 #ifndef/#define/#endif 更简洁且编译器优化更好

#include <string>
#include <unordered_map>

// [C++特性说明]: 使用命名空间避免全局命名污染
// 所有 Mini-KV 相关的类和函数都放在 MiniKV 命名空间下
namespace MiniKV {

/**
 * @brief 轻量级内存键值数据库类
 * 
 * [设计思路]: 
 * - 使用 std::unordered_map 作为底层存储，提供 O(1) 的平均查找性能
 * - 当前版本只支持 String 类型的键值对
 * - 提供基础的 CRUD 操作：SET, GET, DEL, EXISTS
 */
class Database {
private:
    // [C++特性说明]: private 成员变量，外部无法直接访问，体现封装性
    // 使用 std::unordered_map 而不是 std::map，因为我们不需要键的有序性
    // unordered_map 基于哈希表，查找性能更优
    std::unordered_map<std::string, std::string> storage_;
    
    // [C++特性说明]: 使用 size_t 存储计数，这是标准库容器大小的标准类型
    // size_t 是无符号整数，保证能容纳任何对象的大小
    mutable size_t operation_count_;

public:
    // [C++特性说明]: 构造函数，初始化成员变量
    // 使用初始化列表而不是在函数体内赋值，效率更高
    Database();
    
    // [C++特性说明]: 析构函数，当对象销毁时自动调用
    // 虽然这里没有手动分配的资源，但显式声明析构函数是好习惯
    ~Database();
    
    /**
     * @brief 设置键值对
     * @param key 键（常量引用传递，避免拷贝）
     * @param value 值（常量引用传递，避免拷贝）
     * @return 是否是新插入（true）还是更新已有键（false）
     * 
     * [C++特性说明]: 参数使用 const std::string& 而不是 std::string
     * 原因：
     * 1. 引用传递避免了字符串的深拷贝（性能优化）
     * 2. const 保证函数内部不会修改传入的参数（安全性）
     * 3. 对于大对象（如 string），引用传递是标准做法
     */
    bool set(const std::string& key, const std::string& value);
    
    /**
     * @brief 获取键对应的值
     * @param key 要查询的键
     * @param value 输出参数，用于存储查询结果
     * @return 是否找到该键
     * 
     * [C++特性说明]: value 参数使用非 const 引用（输出参数）
     * 这是 C++ 中返回多个值的常用技巧：
     * - 函数返回值表示操作是否成功（bool）
     * - 引用参数用于传出实际数据
     * 这样调用者可以先判断是否成功，再使用数据
     */
    bool get(const std::string& key, std::string& value) const;
    
    /**
     * @brief 删除指定的键值对
     * @param key 要删除的键
     * @return 是否成功删除（键存在返回 true）
     */
    bool del(const std::string& key);
    
    /**
     * @brief 检查键是否存在
     * @param key 要检查的键
     * @return 键是否存在
     * 
     * [C++特性说明]: 函数声明为 const，表示该函数不会修改对象状态
     * const 成员函数可以被 const 对象调用，也是良好的接口设计
     */
    bool exists(const std::string& key) const;
    
    /**
     * @brief 获取数据库中键值对的数量
     * @return 键值对数量
     */
    size_t size() const;
    
    /**
     * @brief 清空数据库
     */
    void clear();
    
    /**
     * @brief 获取总操作次数（用于统计）
     * @return 操作次数
     */
    size_t getOperationCount() const;
    
    /**
     * @brief 打印数据库所有内容（用于调试）
     */
    void printAll() const;
};

} // namespace MiniKV
