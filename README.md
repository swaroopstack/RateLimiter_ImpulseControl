# ⚙️ Implementation of Rate Limiting Algorithm for Impulse Control  

### 📘 Project Overview  
This project demonstrates the concept of **Impulse Control** using a **Rate Limiting Algorithm** implemented in C++.  
It simulates how systems (or humans) can limit frequent impulses — by allowing or blocking actions when they exceed a defined rate.  

---

## 🧠 Concept  
Rate Limiting is a common algorithm used to **control how many requests** can be made within a specific time window.  
It’s widely used in:
- API request management  
- Login attempt throttling  
- Server overload prevention  
- Behavioral simulations (like impulse control in psychology)

This project connects the **computer algorithm** concept with **human-like self-control** —  
showing how to manage “too many actions happening too fast”.

---

## 🚀 Features
- Written in **Modern C++17**
- Implements **Fixed Window Rate Limiting**
- Uses `std::queue` and `std::chrono` for time-based request control  
- Simulates impulses with controlled delay  
- Provides real-time feedback (`ALLOWED ✅` or `BLOCKED 🚫`)

---

## 🧩 Working Principle

1. The user inputs:
   - Maximum number of requests (`maxRequests`)
   - Time window in seconds (`timeWindow`)
2. The program simulates 10 requests.
3. For each request:
   - The algorithm removes old timestamps (older than `timeWindow`).
   - If the number of recent requests is below `maxRequests`, it **allows** the request.
   - Otherwise, it **blocks** it to control the impulse.
4. A delay (`700 ms`) is added between each request to simulate real-time behavior.

---

## 🧱 Algorithm Steps
**Algorithm: Fixed Window Rate Limiting**
```
Step 1: Initialize maxRequests and timeWindow
Step 2: For each incoming request:
            a. Record the current time (now)
            b. Remove old requests from the queue (older than timeWindow)
            c. If queue size < maxRequests:
                    Allow request (push time)
               Else:
                    Block request
Step 3: Repeat for next request
```

---

## 💻 Code Example

```cpp
#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

class RateLimiter {
private:
    int maxRequests;
    int timeWindow;
    queue<steady_clock::time_point> requestTimes;

public:
    RateLimiter(int maxReq, int windowSec) {
        maxRequests = maxReq;
        timeWindow = windowSec;
    }

    bool allowRequest() {
        auto now = steady_clock::now();

        while (!requestTimes.empty() && 
               duration_cast<seconds>(now - requestTimes.front()).count() >= timeWindow) {
            requestTimes.pop();
        }

        if ((int)requestTimes.size() < maxRequests) {
            requestTimes.push(now);
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    cout << "=== Rate Limiting Algorithm for Impulse Control ===\n\n";
    
    int limit, window;
    cout << "Enter maximum requests allowed: ";
    cin >> limit;
    cout << "Enter time window (in seconds): ";
    cin >> window;

    RateLimiter limiter(limit, window);
    cout << "\nSystem Ready! Simulating requests...\n\n";

    for (int i = 1; i <= 10; ++i) {
        if (limiter.allowRequest()) {
            cout << "✅ Request " << i << " ALLOWED.\n";
        } else {
            cout << "🚫 Request " << i << " BLOCKED (Too many requests!)\n";
        }
        this_thread::sleep_for(chrono::milliseconds(700));
    }

    cout << "\nSimulation Complete. Impulse Control Successful.\n";
    return 0;
}
```

---

## 🧪 Example Output

```
=== Rate Limiting Algorithm for Impulse Control ===

Enter maximum requests allowed: 5
Enter time window (in seconds): 5

System Ready! Simulating requests...

✅ Request 1 ALLOWED.
✅ Request 2 ALLOWED.
✅ Request 3 ALLOWED.
✅ Request 4 ALLOWED.
✅ Request 5 ALLOWED.
🚫 Request 6 BLOCKED (Too many requests!)
🚫 Request 7 BLOCKED (Too many requests!)
✅ Request 8 ALLOWED.
✅ Request 9 ALLOWED.
✅ Request 10 ALLOWED.

Simulation Complete. Impulse Control Successful.
```

---

## 📊 Use Case Analogy  
Think of this as a “self-control” mechanism:  
When you act too quickly without pause, your brain blocks impulses temporarily —  
just like this program stops too many requests within a short period.

| Scenario | Example |
|-----------|----------|
| Web API | Prevents overloading server by blocking excess requests |
| Security | Limits login attempts per time |
| Psychology | Models how humans control repetitive impulses |

---

## 🏁 Conclusion  
This project successfully implements a **Rate Limiting Algorithm** as a model of **Impulse Control**.  
It efficiently demonstrates how to manage action frequency within a time window, maintaining balance and stability in systems — just as impulse control maintains discipline in human behavior.  

---

## 👨‍💻 Developed By  
**Name:** Swaroop Kumar  
**Subject:** Advanced Data Structures and Algorithms  
**Language:** C++17  
**Compiler:** GCC 15.2.0 (MinGW WinLibs)  
**IDE:** Visual Studio Code  
**Year:** 2025  

---

## 🧾 License  
This project is open-source and free to use for educational purposes.
