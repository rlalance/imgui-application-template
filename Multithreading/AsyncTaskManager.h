#pragma once
#include <functional>
#include <future>
#include <utility>

class AsyncTaskManager
{
public:
    template <typename F, typename... A>
    auto submitTask(F&& func, A && ... args)
    {
        // Use a packaged_task to wrap the function and get a future
        using return_type = decltype(func(args...));

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(func), std::forward<A>(args)...)
        );

        std::future<return_type> res = task->get_future();

        // Launch a new thread explicitly to run the task
        std::thread([task]() {
            (*task)();
        }).detach(); // Detach the thread so we don't need to join it

        return res;
    }
};
