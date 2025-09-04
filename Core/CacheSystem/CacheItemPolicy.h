#pragma once

enum class EvictionPolicy
{
    None,
    AbsoluteExpiration, // Time-based expiration, fixed time
    SlidingExpiration  // Time-based expiration, resets on access
};
