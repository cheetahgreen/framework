#include "fw/performance/PerformanceMonitor.hpp"
#include <cmath>

namespace fw
{

PerformanceMonitor::PerformanceMonitor():
    _secondsAccumulator{},
    _lastFPS{},
    _numFramesLastSecond{},
    _currentStartTime{std::chrono::high_resolution_clock::now()},
    _previousStartTime{_currentStartTime}
{
}

PerformanceMonitor::~PerformanceMonitor()
{
}

void PerformanceMonitor::startFrame()
{
    _previousStartTime = _currentStartTime;
    _currentStartTime = std::chrono::high_resolution_clock::now();
    updateFPS();
}

void PerformanceMonitor::updateFPS()
{
    auto deltaTime = std::chrono::duration<double>(getLastFrameDuration());
    _secondsAccumulator += deltaTime.count();

    if (_secondsAccumulator >= 1.0)
    {
        _lastFPS = _numFramesLastSecond;
        _numFramesLastSecond = 0;
        _secondsAccumulator = fmod(_secondsAccumulator, 1.0);
    }

    ++_numFramesLastSecond;
}

std::chrono::high_resolution_clock::duration
    PerformanceMonitor::getLastFrameDuration()
{
    return _currentStartTime - _previousStartTime;
}

}

