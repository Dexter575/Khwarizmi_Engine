#pragma once

#include <chrono>
#include <vector>
#include <stdint.h>

namespace ke {

template <typename R>
class StopWatchTemplate {
private:
    std::vector<typename R::time_point> m_start_TPStack;

public:
    enum class DurationTypeEnum {
        NANO_SECONDS,
        MICRO_SECONDS,
        MILLI_SECONDS,
        SECONDS,
    };

    typename R::time_point start() {
        typename R::time_point start_time_point = R::now();
        m_start_TPStack.push_back(start_time_point);
        return start_time_point;
    };

    inline uint64_t duration_cast(const typename R::duration& duration, DurationTypeEnum dt) const {
        switch (dt) {
            case DurationTypeEnum::NANO_SECONDS:
                return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
            case DurationTypeEnum::MICRO_SECONDS:
                return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
            case DurationTypeEnum::MILLI_SECONDS:
                return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
            case DurationTypeEnum::SECONDS:
                return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
            default:
                break;
        }
        return UINT64_MAX;
    }

    uint64_t stop(DurationTypeEnum dt = DurationTypeEnum::MILLI_SECONDS) {
        typename R::duration duration = R::now() - m_start_TPStack.back();
        m_start_TPStack.pop_back();
        return duration_cast(duration, dt);
    }

    uint64_t elapsed(DurationTypeEnum dt = DurationTypeEnum::MILLI_SECONDS) {
        typename R::duration duration = R::now() - m_start_TPStack.back();
        return duration_cast(duration, dt);
    }

    uint64_t elapsedFromRoot(DurationTypeEnum dt = DurationTypeEnum::MILLI_SECONDS) {
        typename R::duration duration = R::now() - m_start_TPStack.front();
        return duration_cast(duration, dt);
    }
};

using StopWatch = StopWatchTemplate<std::chrono::system_clock>;
using StopWatchHiRes = StopWatchTemplate<std::chrono::high_resolution_clock>;

};