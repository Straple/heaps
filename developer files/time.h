#pragma once

#include <iostream>

// тики ведутся с 1-го января 1970 г. 00:00:00 Всемирного времени

#if defined(_WIN32)

#include <windows.h>

// вернет частоту обновления устройства
unsigned long long get_performance_frequency() {
    LARGE_INTEGER perf;

    QueryPerformanceFrequency(&perf);

    return perf.QuadPart;
}

// вернет текущий тик
unsigned long long get_ticks() {
    LARGE_INTEGER ticks;

    QueryPerformanceCounter(&ticks);

    return ticks.QuadPart;
}

#elif defined(__linux__) || defined (__APPLE__)

#include <sys/time.h>

// вернет частоту обновления устройства
unsigned long long get_performance_frequency() {
    return 1'000'000; // колво микросекунд в секунде
}

// вернет текущий тик
unsigned long long get_ticks() {
    timeval ticks;

    // вернет -1 в случае ошибки
    gettimeofdey(&ticks, NULL);
    return ticks.tv_usec;
}

#else 

// not supported operating system

#endif

const double performance_frequency = get_performance_frequency();

class Timer {

    unsigned long long start_tick;

public:

    Timer() {
        reset();
    }

    // вернет время после reset|default constructor в секундах
    double time() const {

        // разница тиков делить на частоту
        return (get_ticks() - start_tick) / performance_frequency;
    }

    // обновит указатель времени
    void reset() {
        start_tick = get_ticks();
    }

    // вернет тик начала отсчета
    unsigned long long get_tick() const {
        return start_tick;
    }
};
std::ostream& operator << (std::ostream& output, const Timer& time) {
    return output << time.time() << "s";
}