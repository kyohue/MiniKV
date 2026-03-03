#include "../include/MiniKV.h"
#include <iostream>

// [C++特性说明]: 实现文件中也需要使用命名空间
// 可以用 using namespace 简化代码，但在头文件中绝不能这样做
namespace MiniKV {

// [C++特性说明]: 构造函数实现，使用初始化列表
// 初始化列表在对象构造时直接初始化成员，比在函数体内赋值更高效
Database::Database() 
    : storage_(),           // 调用 unordered_map 的默认构造函数
      operation_count_(0)   // 直接初始化为 0
{
    // [设计说明]: 构造函数体为空，所有初始化都在初始化列表完成
    // 这是现代 C++ 的最佳实践
}

Database::~Database() {
    // [C++特性说明]: 析构函数
    // std::unordered_map 会自动清理内存，我们不需要手动 delete
    // 这就是 RAII (Resource Acquisition Is Initialization) 的优势
}

bool Database::set(const std::string& key, const std::string& value) {
    // [C++特性说明]: 使用 unordered_map 的 insert_or_assign (C++17)
    // 或者使用 operator[] 进行插入/更新
    
    // insert_or_assign 返回一个 pair
    // result.first 是指向该元素的迭代器
    // result.second 是一个 bool，true 代表是新插入，false 代表是更新
    //auto result = storage_.insert_or_assign(key, value);
    
    // 检查键是否已存在
    bool is_new_key = (storage_.find(key) == storage_.end());
    storage_[key] = value;
    ++operation_count_;
    
    return is_new_key;
}

bool Database::get(const std::string& key, std::string& value) const {
     ++operation_count_; // ✅ 现在即使在 const 函数里也能合法自增了！
    
     // [C++特性说明]: 使用 find() 而不是 operator[]
    // 原因：
    // 1. operator[] 不是 const 函数，因为它可能插入新元素
    // 2. find() 是 const 函数，只查找不修改
    // 3. find() 返回迭代器，找不到时返回 end()
    
    auto it = storage_.find(key);
    
    // [C++特性说明]: auto 关键字让编译器自动推导类型
    // 这里 it 的实际类型是 std::unordered_map<std::string, std::string>::const_iterator
    // 使用 auto 让代码更简洁易读
    
    if (it != storage_.end()) {
        // [C++特性说明]: 迭代器的 -> 操作符
        // it->second 访问键值对中的值部分
        // unordered_map 的元素类型是 std::pair<const Key, Value>
        value = it->second;
        return true;
    }
    
    return false;
}

bool Database::del(const std::string& key) {
    // [C++特性说明]: erase() 返回删除的元素个数
    // 对于 unordered_map，返回值只能是 0 或 1
    // 返回 1 表示删除成功，0 表示键不存在
    ++operation_count_;
    size_t erased_count = storage_.erase(key);
    
    if (erased_count > 0) {
        return true;
    }
    
    return false;
}

bool Database::exists(const std::string& key) const {
     ++operation_count_; // ✅ 现在即使在 const 函数里也能合法自增了！
    
    // [C++特性说明]: find() + 比较迭代器是检查键是否存在的标准做法
    // 也可以使用 count()，但 find() 语义更清晰
    return storage_.find(key) != storage_.end();
}

size_t Database::size() const {
     ++operation_count_; // ✅ 现在即使在 const 函数里也能合法自增了！

    // [C++特性说明]: 直接返回容器的 size()
    // 这是 O(1) 操作，unordered_map 内部维护了元素计数
    return storage_.size();
}

void Database::clear() {
    // [C++特性说明]: clear() 会删除所有元素，但不释放已分配的内存
    // 如果需要释放内存，可以使用 swap 技巧：
    // std::unordered_map<std::string, std::string>().swap(storage_);
    storage_.clear();
    ++operation_count_;
}

size_t Database::getOperationCount() const {
    return operation_count_;
}

void Database::printAll() const {
    ++operation_count_;
    std::cout << "========== Mini-KV 数据库内容 ==========" << std::endl;
    std::cout << "总键值对数量: " << storage_.size() << std::endl;
    std::cout << "总操作次数: " << operation_count_ << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    if (storage_.empty()) {
        std::cout << "(数据库为空)" << std::endl;
    } else {
        // [C++特性说明]: 基于范围的 for 循环 (C++11)
        // 这是遍历容器的现代写法，比传统迭代器更简洁
        // const auto& 避免拷贝，提高性能
        for (const auto& pair : storage_) {
            // [C++特性说明]: pair.first 是键，pair.second 是值
            std::cout << "  [" << pair.first << "] => \"" 
                      << pair.second << "\"" << std::endl;
        }
    }
    
    std::cout << "========================================" << std::endl;
}

} // namespace MiniKV
