#pragma once
#include <chrono>
#include <mutex>

class TokenBucket {
public:
    using clock = std::chrono::steady_clock;
    TokenBucket(double cap = 10.0, double rate = 1.0);
    bool allow(double tokens = 1.0);
    void setRate(double r);
    void setCapacity(double cap);
private:
    void refill();
    double capacity_;
    double tokens_;
    double rate_;
    clock::time_point lastFill_;
    mutable std::mutex mtx_;
};
