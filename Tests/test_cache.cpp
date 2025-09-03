#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "CacheItem.h"
#include <gtest/gtest.h>

TEST(CacheItemTest, StoresAndRetrievesInt)
{
    CacheItem item(42);

    EXPECT_TRUE(item.Is<int>());
    EXPECT_EQ(item.GetDataAs<int>(), 42);
}

TEST(CacheItemTest, StoresAndRetrievesString)
{
    CacheItem item(std::string("Hello"));

    EXPECT_TRUE(item.Is<std::string>());
    EXPECT_EQ(item.GetDataAs<std::string>(), "Hello");
}

TEST(CacheItemTest, IsReturnsFalseForWrongType)
{
    CacheItem item(100);
    EXPECT_FALSE(item.Is<std::string>());
}

TEST(CacheItemTest, CanCacheRawPointer)
{
    CacheItem item(new int[50000]); // Allocate a large array
    EXPECT_TRUE(item.Is<int*>());
    delete[] item.GetDataAs<int*>(); // Clean up
}

TEST(CacheItemTest, CanCachePointer)
{
    auto ptr = std::make_shared<int>(123);
    CacheItem item(ptr);

    EXPECT_TRUE(item.Is<std::shared_ptr<int>>());
    EXPECT_EQ(*item.GetDataAs<std::shared_ptr<int>>(), 123);
}
