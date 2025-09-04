#pragma once
#include "CacheItemPolicy.h"

#include <chrono>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

class CacheItem;
class CacheEvictionPolicy;
class HugeObjectCache
{
  public:
    explicit HugeObjectCache(size_t maxCacheSizeInMB);
    virtual ~HugeObjectCache();

    void AddItem(const EvictionPolicy &policy, const std::string &key, std::unique_ptr<CacheItem> item);
    std::shared_ptr<CacheItem> GetItem(const std::string &key);
    void RemoveItem(const std::string &key);
    void Clear();
    void Update();

  private:
    size_t mMaxCacheSizeInBytes = 0;
    std::unordered_map<std::string, std::shared_ptr<CacheItem>> mCacheItems;
    std::set<std::string> mKeysToEvict;
    std::chrono::high_resolution_clock::time_point mLastUpdateTime;
    std::chrono::high_resolution_clock::duration mTileElapsed;

    void RefreshCacheItems();
    void MarkItemsToEvict(const std::string &key, const std::shared_ptr<CacheItem>& item);
};