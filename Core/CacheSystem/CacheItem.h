#pragma once

#include "CacheItemPolicy.h"

#include <any>

class CacheItem
{
public:
    template <typename T>
    explicit CacheItem(T data) : mData(std::move(data)) {}

    template <typename T>
    T GetDataAs() const { return std::any_cast<T>(mData); }

    void SetPolicy(const CacheItemPolicy &policy);
    const CacheItemPolicy &GetPolicy() const { return policy; }

    template<typename T>
    bool Is() const noexcept
    {
        return std::any_cast<T>(&mData) != nullptr;
    }


private:
    CacheItemPolicy policy;
    std::any mData;
};
