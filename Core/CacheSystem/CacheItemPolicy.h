#pragma once

class CacheItemPolicy
{
    enum class EvictionPolicy
    {
        None,
        AbsoluteExpiration, // Time-based expiration, fixed time
        SlidingExpiration,  // Time-based expiration, resets on access
        SizeBased,          // Evict based on size constraints
        PriorityBased       // Evict based on item priority
    };
};
