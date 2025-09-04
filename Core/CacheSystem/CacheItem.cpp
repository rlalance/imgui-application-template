#include "CacheItem.h"

void CacheItem::SetEvictionPolicy(const EvictionPolicy &evictionPolicy)
{
    mEvictionPolicy = evictionPolicy;
}