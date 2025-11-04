#include "sliding_window.h"

SlidingWindowLog::SlidingWindowLog(size_t maxRequests, long long windowMs)
    : maxRequests_(maxRequests), window_(std::chrono::milliseconds(windowMs)) {}

bool SlidingWindowLog::allow() {
    std::lock_guard<std::mutex> lg(mtx_);
    auto now = clock::now();

    while (!timestamps_.empty() && now - timestamps_.front() >= window_) {
        timestamps_.pop_front();
    }

    if (timestamps_.size() < maxRequests_) {
        timestamps_.push_back(now);
        return true;
    }
    return false;
}
