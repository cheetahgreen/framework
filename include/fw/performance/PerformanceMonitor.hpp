#pragma once
#include <chrono>

namespace fw
{

class PerformanceMonitor
{
public:
    PerformanceMonitor();
    ~PerformanceMonitor();

    void startFrame();

    std::chrono::high_resolution_clock::duration getLastFrameDuration();
    int getLastFPS() { return _lastFPS; }

protected:
    void updateFPS();

private:
    double _secondsAccumulator;
    int _lastFPS;
    int _numFramesLastSecond;

    std::chrono::high_resolution_clock::time_point _currentStartTime;
    std::chrono::high_resolution_clock::time_point _previousStartTime;
};

}
