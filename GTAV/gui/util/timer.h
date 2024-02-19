#pragma once
#include "pch.h"
#include "rage/invoker/natives.h"

class Timer {
public:
    explicit Timer(std::chrono::milliseconds delay) :
        m_Timer(std::chrono::high_resolution_clock::now()),
        m_Delay(delay),
        m_ElapsedTime(0ms)
    {
    }

    bool Update() {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_Timer);
        if (delta >= m_Delay) {
            m_Timer = now;
            m_ElapsedTime = delta;
            return true;
        }

        return false;
    }


    void SetDelay(std::chrono::milliseconds delay) {
        m_Delay = delay;
    }

    std::chrono::milliseconds GetDelay() const {
        return m_Delay;
    }

    std::chrono::milliseconds GetElapsedTime() const {
        return m_ElapsedTime;
    }

    void Reset() {
        m_Timer = std::chrono::high_resolution_clock::now();
        m_ElapsedTime = 0ms;
    }

private:
    std::chrono::high_resolution_clock::time_point m_Timer;
    std::chrono::milliseconds m_Delay;
    std::chrono::milliseconds m_ElapsedTime;
};

class timer {
public:
    void start(unsigned long long ticks) {
        if (m_tick) {
            m_ready_at = GetTickCount64() + ticks;
            m_tick = false;
        }
    }

    bool is_ready() {
        return GetTickCount64() > m_ready_at;
    }

    void reset() {
        m_tick = true;
    }
private:
    unsigned long long m_ready_at;
    bool m_tick;
};

inline void run_timed(int* timer, int ms, std::function<void()> callback) {
    if (*timer < MISC::GET_GAME_TIMER()) {
        *timer = MISC::GET_GAME_TIMER() + ms;
        callback();
    }
}