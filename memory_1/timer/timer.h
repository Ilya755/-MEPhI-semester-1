#include <cassert>
#include <chrono>
#include <cmath>
#include <sstream>
#include <string>
#include <thread>

class Timer {
private:
    std::chrono::duration<double> step_;
    const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

public:
    Timer(std::chrono::duration<double> step)
        : step_(step)
        {}

    bool Expired() const {
        const std::chrono::steady_clock::time_point cur = std::chrono::steady_clock::now();
        if (cur - start <= step_) {
            return false;
        }
        else {
            return true;
        }
    }
};

class TimeMeasurer {
private:
    std::ostream& out_stream_;
public:
    std::chrono::steady_clock::time_point start;

    TimeMeasurer(std::ostream& out_stream) 
        : out_stream_(out_stream)
        {
            start = std::chrono::steady_clock::now();
        }
    ~TimeMeasurer() {
        const std::chrono::steady_clock::time_point finish = std::chrono::steady_clock::now();

        out_stream_ << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl; 
    }
};

