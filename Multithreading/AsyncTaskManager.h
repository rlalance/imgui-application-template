#pragma once
#include <future>
#include <utility>

class AsyncTaskManager
{
public:
    template <typename F, typename... A>
    auto submitTask(F&& func, A && ... args)
    {
        return std::async(std::launch::async, std::forward<F>(func), std::forward<A>(args) ... );
    }
};
