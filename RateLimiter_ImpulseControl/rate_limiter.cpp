#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

// Class for Rate Limiting Algorithm (Impulse Control)
class RateLimiter {
private:
    int maxRequests;    // maximum allowed requests
    int timeWindow;     // time window in seconds
    queue<steady_clock::time_point> requestTimes;  // stores timestamps of allowed requests

public:
    // Constructor to set the limit and time window
    RateLimiter(int maxReq, int windowSec) {
        maxRequests = maxReq;
        timeWindow = windowSec;
    }

    // Function to check if a new request is allowed
    bool allowRequest() {
        auto now = steady_clock::now();

        // Remove old requests (older than timeWindow)
        while (!requestTimes.empty() && 
               duration_cast<seconds>(now - requestTimes.front()).count() >= timeWindow) {
            requestTimes.pop();
        }

        // Check how many requests are within the window
        if ((int)requestTimes.size() < maxRequests) {
            requestTimes.push(now);
            return true; // allowed
        } else {
            return false; // blocked
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
        std::this_thread::sleep_for(std::chrono::milliseconds(700));  // simulate request timing
    }

    cout << "\nSimulation Complete. Impulse Control Successful.\n";
    return 0;
}

/*
-----------------------------------------
    EXPLANATION OF THE CODE
-----------------------------------------

HEADER FILES:
    - <iostream>: For input/output.
    - <queue>: To store timestamps of requests.
    - <chrono>: To handle real-time duration and timing.
    - <thread>: To pause between requests (simulate time gap).

CLASS "RateLimiter":
    - Controls how many requests are allowed in a given time.
    - Has 3 main variables:
        • maxRequests → maximum allowed actions
        • timeWindow → time duration (in seconds)
        • requestTimes → queue storing timestamps of allowed requests

FUNCTION: allowRequest()
    - Gets the current time using steady_clock.
    - Removes timestamps older than 'timeWindow' seconds (old impulses).
    - Checks the queue size:
        • If below maxRequests → request allowed 
        • If at limit → request blocked 

MAIN FUNCTION:
    - Takes user input for limit and time window.
    - Creates a RateLimiter object with those values.
    - Runs a loop of 10 simulated requests.
    - Each request waits 700 milliseconds before the next.
    - Shows if each request is allowed or blocked.

CONCEPT:
    - Simulates *Impulse Control*:
        The system learns to "pause" when too many actions happen quickly.
        Just like humans control impulses, the algorithm controls request bursts.

-----------------------------------------
EXAMPLE:
If maxRequests = 5 and timeWindow = 10 seconds:
→ The first 5 requests are allowed.
→ Requests after that are blocked until old ones expire (after 10 seconds).
-----------------------------------------

*/
