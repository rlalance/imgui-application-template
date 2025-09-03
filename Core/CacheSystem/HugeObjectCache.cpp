#include "HugeObjectCache.h"
#include "CacheItem.h"
#include "CacheItemPolicy.h"

HugeObjectCache::HugeObjectCache(size_t maxCacheSizeInMB) : mMaxCacheSizeInBytes(maxCacheSizeInMB)
{

}

HugeObjectCache::~HugeObjectCache() = default;

void HugeObjectCache::AddItem(const CacheItemPolicy &policy, const std::string &key, std::unique_ptr<CacheItem> item)
{
    item->SetPolicy(policy);

    mCacheItems[key] = std::move(item);
}

std::shared_ptr<CacheItem> HugeObjectCache::GetItem(const std::string &key)
{
    return mCacheItems[key];
}

void HugeObjectCache::RemoveItem(const std::string &key)
{
}
void HugeObjectCache::Clear()
{
}
void HugeObjectCache::RefreshCacheItems()
{
}
void HugeObjectCache::EvictItemsIfNeeded()
{
}