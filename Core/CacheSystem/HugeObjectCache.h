#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>

class CacheItem;
class CacheItemPolicy;
class HugeObjectCache
{
  public:
    HugeObjectCache(size_t maxCacheSizeInMB);
    virtual ~HugeObjectCache();

    void AddItem(const CacheItemPolicy &policy, const std::string &key, std::unique_ptr<CacheItem> item);
    std::shared_ptr<CacheItem> GetItem(const std::string &key);
    void RemoveItem(const std::string &key);
    void Clear();

  private:
    size_t mMaxCacheSizeInBytes = 0;
    std::unordered_map<std::string, std::shared_ptr<CacheItem>> mCacheItems;

    void RefreshCacheItems();
    void EvictItemsIfNeeded();
};