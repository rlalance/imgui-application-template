#pragma once

#include "CacheItemPolicy.h"

#include <any>
#include <chrono>

class CacheItem
{
  public:
    template <typename T>
    explicit CacheItem(std::chrono::high_resolution_clock::duration lifetime, T data)
        : mLifetime(lifetime), mData(std::move(data))
    {
    }

    template <typename T> T GetDataAs() const
    {
        return std::any_cast<T>(mData);
    }

    void SetEvictionPolicy(const EvictionPolicy &evictionPolicy);
    EvictionPolicy GetEvictionPolicy() const
    {
        return mEvictionPolicy;
    }

    template <typename T> bool Is() const noexcept
    {
        return std::any_cast<T>(&mData) != nullptr;
    }

    std::chrono::high_resolution_clock::duration mLifetimeElapsed =
        std::chrono::high_resolution_clock::duration::zero();
    std::chrono::high_resolution_clock::duration mLifetime; // Default 30 seconds

  private:
    EvictionPolicy mEvictionPolicy = EvictionPolicy::None;
    std::any mData;
};
