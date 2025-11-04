#include "token_bucket.h"
#include <algorithm>

TokenBucket::TokenBucket(double cap, double rate)
    : capacity_(cap), tokens_(cap), rate_(rate), lastFill_(clock::now()) {}

void TokenBucket::refill() {
    auto now = clock::now();
    std::chrono::duration<double> elapsed = now - lastFill_;
    double add = elapsed.count() * rate_;
    if (add > 0.0) {
        tokens_ = std::min(capacity_, tokens_ + add);
        lastFill_ = now;
    }
}

bool TokenBucket::allow(double tokens) {
    std::lock_guard<std::mutex> lg(mtx_);
    refill();
    const double EPS = 1e-12;
    if (tokens_ + EPS >= tokens) {
        tokens_ -= tokens;
        return true;
    }
    return false;
}

void TokenBucket::setRate(double r) {
    std::lock_guard<std::mutex> lg(mtx_);
    refill();
    rate_ = r;
}

void TokenBucket::setCapacity(double cap) {
    std::lock_guard<std::mutex> lg(mtx_);
    refill();
    capacity_ = cap;
    if (tokens_ > capacity_) tokens_ = capacity_;
}
