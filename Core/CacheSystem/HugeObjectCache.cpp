#include "HugeObjectCache.h"
#include "CacheItem.h"
#include "CacheItemPolicy.h"

HugeObjectCache::HugeObjectCache(size_t maxCacheSizeInMB) : mMaxCacheSizeInBytes(maxCacheSizeInMB), mTileElapsed()
{
    mLastUpdateTime = std::chrono::high_resolution_clock::now();
}

HugeObjectCache::~HugeObjectCache() = default;

void HugeObjectCache::Update()
{
    RefreshCacheItems();
}

void HugeObjectCache::AddItem(const EvictionPolicy &policy, const std::string &key, std::unique_ptr<CacheItem> item)
{
    mCacheItems[key] = std::move(item);
    mCacheItems[key]->SetEvictionPolicy(policy);
}

std::shared_ptr<CacheItem> HugeObjectCache::GetItem(const std::string &key)
{
    auto it = mCacheItems.find(key);

    if (it != mCacheItems.end())
    {
        if (it->second->GetEvictionPolicy() == EvictionPolicy::SlidingExpiration)
        {
            it->second->mLifetimeElapsed = std::chrono::high_resolution_clock::duration::zero();
        }
        return it->second;
    }

    return mCacheItems[key];
}

void HugeObjectCache::RemoveItem(const std::string &key)
{
    mCacheItems.erase(key);
}

void HugeObjectCache::Clear()
{
    for (auto it = mCacheItems.begin(); it != mCacheItems.end();)
    {
        it = mCacheItems.erase(it);
    }
}

void HugeObjectCache::RefreshCacheItems()
{
    auto now = std::chrono::high_resolution_clock::now();
    mTileElapsed = now - mLastUpdateTime;
    mLastUpdateTime = now;

    for (const auto &[key, item] : mCacheItems)
    {
        item->mLifetimeElapsed += mTileElapsed;

        MarkItemsToEvict(key, item);
    }

    for (const auto &key : mKeysToEvict)
    {
        mCacheItems.erase(key);
    }
}

void HugeObjectCache::MarkItemsToEvict(const std::string &key, const std::shared_ptr<CacheItem> &item)
{
    if (item->mLifetimeElapsed >= item->mLifetime)
    {
        mKeysToEvict.insert(key);
    }
}