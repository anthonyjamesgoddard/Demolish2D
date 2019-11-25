#include "demolish/utils/timer.h"

using demolish::utils::Timer;

constexpr float OONPS = 1E-9;  // ONE_OVER_NANOSECONDS_PER_SECOND

Timer::Timer() {
    _deltaTime = -1.0;
    clock_gettime(CLOCK_REALTIME, &_baseTime);
    _pausedTime = {0, 0};
    _prevTime = {0, 0};
    _currTime = {0, 0};
    _stopped = false;
}
float Timer::gameTime() {
    if (_stopped) {
        return (_stopTime.tv_sec - _pausedTime.tv_sec) - _baseTime.tv_sec +
               ((_stopTime.tv_nsec - _pausedTime.tv_nsec) - _baseTime.tv_nsec) *
                   OONPS;
    } else {
        return (_currTime.tv_sec - _baseTime.tv_sec) +
               (_currTime.tv_nsec - _baseTime.tv_nsec) * OONPS;
    }
}
void Timer::reset() {
    _deltaTime = -1.0;
    clock_gettime(CLOCK_REALTIME, &_baseTime);
    _pausedTime = {0, 0};
    _prevTime = {0, 0};
    _currTime = {0, 0};
    _stopped = false;
}

void Timer::tick() {
    if (_stopped) {
        _deltaTime = 0.0;
        return;
    }
    clock_gettime(CLOCK_REALTIME, &_currTime);
    _deltaTime = (_currTime.tv_sec - _prevTime.tv_sec) +
                (_currTime.tv_nsec - _prevTime.tv_nsec) * OONPS;
    _prevTime = _currTime;
}

float Timer::deltaTime() { return (float)_deltaTime; }

void Timer::start() {
    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    // Accumulate the time elapsed between stop and start pairs.
    //
    //                     |<-------d------->|
    // ----*---------------*-----------------*------------> time
    //  mBaseTime       mStopTime        startTime

    if (_stopped) {
        _pausedTime.tv_sec += (start.tv_sec - _stopTime.tv_sec);
        _pausedTime.tv_nsec += (start.tv_nsec - _stopTime.tv_nsec);

        _prevTime = start;
        _stopTime.tv_sec = 0;
        _stopTime.tv_nsec = 0;
        _stopped = false;
    }
}

void Timer::stop() {
    if (!_stopped) {
        struct timespec current;
        clock_gettime(CLOCK_REALTIME, &current);

        _stopTime = _currTime;
        _stopped = true;
    }
}

