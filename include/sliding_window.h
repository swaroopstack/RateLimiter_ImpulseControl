#pragma once
#include <chrono>
#include <deque>
#include <mutex>

class SlidingWindowLog {
public:
    using clock = std::chrono::steady_clock;
    SlidingWindowLog(size_t maxRequests, long long windowMs);
    bool allow();
private:
    size_t maxRequests_;
    std::chrono::milliseconds window_;
    std::deque<clock::time_point> timestamps_;
    std::mutex mtx_;
};
