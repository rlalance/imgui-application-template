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

    for (const auto& [key,item] : mCacheItems)
    {
        item->mLifetimeElapsed += mTileElapsed;

        MarkItemsToEvict(key, item);
    }

    for (const auto& key : mKeysToEvict)
    {
        mCacheItems.erase(key);
    }
}

void HugeObjectCache::MarkItemsToEvict(const std::string &key, const std::shared_ptr<CacheItem>& item)
{
    if (item->GetEvictionPolicy() == EvictionPolicy::AbsoluteExpiration)
    {
        if (item->mLifetimeElapsed >= item->mLifetime)
        {
            // Evict the item
            // Note: Actual eviction logic (like removing from mCacheItems) should be handled here
            mKeysToEvict.insert(key);
        }
    }
    else if (item->GetEvictionPolicy() == EvictionPolicy::SlidingExpiration)
    {
    }
    else if (item->GetEvictionPolicy() == EvictionPolicy::SizeBased)
    {
    }
    else if (item->GetEvictionPolicy() == EvictionPolicy::PriorityBased)
    {
    }
}