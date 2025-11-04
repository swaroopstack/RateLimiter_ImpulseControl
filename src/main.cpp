#include <iostream>
#include <thread>
#include "token_bucket.h"
#include "sliding_window.h"

void demoTokenBucket() {
    std::cout << "=== Token Bucket Demo ===\n";
    TokenBucket tb(5, 1.0); // capacity=5, refill 1 token/sec
    for (int i = 0; i < 12; ++i) {
        bool ok = tb.allow();
        std::cout << "Request " << i << ": " << (ok ? "ALLOWED" : "BLOCKED") << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << '\n';
}

void demoSlidingWindow() {
    std::cout << "=== Sliding Window Log Demo ===\n";
    SlidingWindowLog sw(5, 1000); // 5 requests per 1000ms
    for (int i = 0; i < 12; ++i) {
        bool ok = sw.allow();
        std::cout << "Request " << i << ": " << (ok ? "ALLOWED" : "BLOCKED") << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << '\n';
}

int main() {
    demoTokenBucket();
    demoSlidingWindow();
    return 0;
}
