#pragma once
#include <time.h>
namespace demolish {
namespace utils {
class Timer {
public:
    Timer();
    float gameTime();
    float deltaTime();
    void reset();  // this is to be called before message loop
    void start();  // when unpaused
    void stop();   // when paused
    void tick();   // every frame

private:
    double _deltaTime;

    struct timespec _baseTime;
    struct timespec _pausedTime;
    struct timespec _stopTime;
    struct timespec _prevTime;
    struct timespec _currTime;

    bool _stopped;
};
}  // namespace utils
}  // namespace demolish
