#include <gtest/gtest.h>
#include "memory_resource.hpp"
#include "vector.hpp"
#include "exceptions.hpp"
#include <string>
#include <memory>

struct TestStruct {
    int id;
    std::string name;
    
    TestStruct(int i = 0, const std::string& n = "") : id(i), name(n) {}
    
    bool operator==(const TestStruct& other) const {
        return id == other.id && name == other.name;
    }
};

class MemoryResourceTest : public ::testing::Test {
protected:
    void SetUp() override {
        resource = std::make_unique<memory_resource::MemoryResource>(64);
    }

    void TearDown() override {
        resource.reset();
    }

    std::unique_ptr<memory_resource::MemoryResource> resource;
};

TEST_F(MemoryResourceTest, BasicAllocation) {
    void* ptr1 = resource->allocate(32, 8);
    void* ptr2 = resource->allocate(16, 8);
    
    ASSERT_NE(ptr1, nullptr);
    ASSERT_NE(ptr2, nullptr);
    ASSERT_NE(ptr1, ptr2);
    
    resource->deallocate(ptr1, 32, 8);
    resource->deallocate(ptr2, 16, 8);
}

TEST_F(MemoryResourceTest, ReuseMemory) {
    void* ptr1 = resource->allocate(32, 8);
    resource->deallocate(ptr1, 32, 8);
    
    void* ptr2 = resource->allocate(32, 8);
    ASSERT_EQ(ptr1, ptr2);
    
    resource->deallocate(ptr2, 32, 8);
}

TEST_F(MemoryResourceTest, ThrowsOnOversizedAllocation) {
    EXPECT_THROW(resource->allocate(128, 8), std::bad_alloc);
}

class VectorIntTest : public ::testing::Test {
protected:
    void SetUp() override {
        resource = std::make_unique<memory_resource::MemoryResource>(256);
        vec = std::make_unique<vector::Vector<int>>(resource.get());
    }

    std::unique_ptr<memory_resource::MemoryResource> resource;
    std::unique_ptr<vector::Vector<int>> vec;
};

TEST_F(VectorIntTest, DefaultConstructor) {
    EXPECT_TRUE(vec->IsEmpty());
    EXPECT_EQ(vec->Size(), 0);
    EXPECT_EQ(vec->Capacity(), 0);
}

TEST_F(VectorIntTest, PushBackAndAccess) {
    vec->PushBack(1);
    vec->PushBack(2);
    vec->PushBack(3);
    
    EXPECT_EQ(vec->Size(), 3);
    EXPECT_EQ(vec->Front(), 1);
    EXPECT_EQ(vec->Back(), 3);
    EXPECT_EQ((*vec)[1], 2);
}

TEST_F(VectorIntTest, InitializerListConstructor) {
    vector::Vector<int> vec2({1, 2, 3, 4, 5}, resource.get());
    EXPECT_EQ(vec2.Size(), 5);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[4], 5);
}

TEST_F(VectorIntTest, CopyConstructor) {
    vec->PushBack(1);
    vec->PushBack(2);
    vec->PushBack(3);
    
    vector::Vector<int> vec2(*vec);
    EXPECT_EQ(vec2.Size(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[2], 3);
}

TEST_F(VectorIntTest, MoveConstructor) {
    vec->PushBack(1);
    vec->PushBack(2);
    
    vector::Vector<int> vec2(std::move(*vec));
    EXPECT_EQ(vec2.Size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_TRUE(vec->IsEmpty());
}

TEST_F(VectorIntTest, AssignmentOperators) {
    vec->PushBack(1);
    vec->PushBack(2);
    
    vector::Vector<int> vec2(resource.get());
    vec2 = *vec;
    EXPECT_EQ(vec2.Size(), 2);
    EXPECT_EQ(vec2[1], 2);
    
    vector::Vector<int> vec3(resource.get());
    vec3 = std::move(vec2);
    EXPECT_EQ(vec3.Size(), 2);
    EXPECT_TRUE(vec2.IsEmpty());
}

TEST_F(VectorIntTest, ReserveAndCapacity) {
    vec->Reserve(10);
    EXPECT_GE(vec->Capacity(), 10);
    
    for (int i = 0; i < 15; ++i) {
        vec->PushBack(i);
    }
    EXPECT_GE(vec->Capacity(), 15);
}

TEST_F(VectorIntTest, ClearAndEmpty) {
    vec->PushBack(1);
    vec->PushBack(2);
    EXPECT_FALSE(vec->IsEmpty());
    
    vec->Clear();
    EXPECT_TRUE(vec->IsEmpty());
    EXPECT_EQ(vec->Size(), 0);
}

TEST_F(VectorIntTest, InsertAndErase) {
    vec->PushBack(1);
    vec->PushBack(3);
    
    vec->Insert(1, 2);
    EXPECT_EQ(vec->Size(), 3);
    EXPECT_EQ((*vec)[1], 2);
    
    vec->Erase(0, 1);
    EXPECT_EQ(vec->Size(), 2);
    EXPECT_EQ(vec->Front(), 2);
}

TEST_F(VectorIntTest, PopBack) {
    vec->PushBack(1);
    vec->PushBack(2);
    vec->PushBack(3);
    
    vec->PopBack();
    EXPECT_EQ(vec->Size(), 2);
    EXPECT_EQ(vec->Back(), 2);
}

TEST_F(VectorIntTest, Resize) {
    vec->PushBack(1);
    vec->PushBack(2);
    
    vec->Resize(5, 0);
    EXPECT_EQ(vec->Size(), 5);
    EXPECT_EQ(vec->Back(), 0);
    
    vec->Resize(2, 0);
    EXPECT_EQ(vec->Size(), 2);
    EXPECT_EQ(vec->Back(), 2);
}

TEST_F(VectorIntTest, OutOfRangeAccess) {
    EXPECT_THROW(vec->Front(), exceptions::VectorOutOfRange);
    EXPECT_THROW(vec->Back(), exceptions::VectorOutOfRange);
    
    vec->PushBack(1);
    EXPECT_NO_THROW(vec->Front());
    EXPECT_NO_THROW(vec->Back());
}

class VectorComplexTest : public ::testing::Test {
protected:
    void SetUp() override {
        resource = std::make_unique<memory_resource::MemoryResource>(512);
        vec = std::make_unique<vector::Vector<TestStruct>>(resource.get());
    }

    std::unique_ptr<memory_resource::MemoryResource> resource;
    std::unique_ptr<vector::Vector<TestStruct>> vec;
};

TEST_F(VectorComplexTest, ComplexTypeOperations) {
    vec->EmplaceBack(1, "first");
    vec->PushBack(TestStruct(2, "second"));
    vec->EmplaceBack(3, "third");
    
    EXPECT_EQ(vec->Size(), 3);
    EXPECT_EQ(vec->Front().id, 1);
    EXPECT_EQ(vec->Back().name, "third");
}

TEST_F(VectorComplexTest, CopyWithComplexTypes) {
    vec->EmplaceBack(1, "test");
    vec->EmplaceBack(2, "example");
    
    vector::Vector<TestStruct> vec2(*vec);
    EXPECT_EQ(vec2.Size(), 2);
    EXPECT_EQ(vec2[0].name, "test");
    EXPECT_EQ(vec2[1].id, 2);
}

// Тесты для итераторов
class VectorIteratorTest : public ::testing::Test {
protected:
    void SetUp() override {
        resource = std::make_unique<memory_resource::MemoryResource>(256);
        vec = std::make_unique<vector::Vector<int>>(resource.get());
        
        for (int i = 0; i < 5; ++i) {
            vec->PushBack(i * 10);
        }
    }

    std::unique_ptr<memory_resource::MemoryResource> resource;
    std::unique_ptr<vector::Vector<int>> vec;
};

TEST_F(VectorIteratorTest, IteratorTraversal) {
    auto it = vec->Begin();
    EXPECT_EQ(*it, 0);
    
    ++it;
    EXPECT_EQ(*it, 10);
    
    it++;
    EXPECT_EQ(*it, 20);
}

TEST_F(VectorIteratorTest, IteratorRange) {
    int sum = 0;
    for (auto it = vec->Begin(); it != vec->End(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 100);
}

TEST_F(VectorIteratorTest, IteratorComparison) {
    auto it1 = vec->Begin();
    auto it2 = vec->Begin();
    
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
    
    ++it1;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

TEST_F(VectorIteratorTest, IteratorArrowOperator) {
    vector::Vector<TestStruct> vec2(resource.get());
    vec2.EmplaceBack(1, "test");
    
    auto it = vec2.Begin();
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->name, "test");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}