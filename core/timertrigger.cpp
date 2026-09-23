#include "timertrigger.hpp"

namespace Toollibs
{

TimerTrigger::TimerTrigger()
    : interval(0),
      pausedDuration(0),
      elapsedAtStop(0),
      running(false),
      paused(false),
      executed(false),
      repeat(false)
{
}

TimerTrigger::TimerTrigger(
    const std::string& timerID,
    long long milliseconds,
    std::function<void()> timerCallback,
    bool shouldRepeat
)
    : id(timerID),
      interval(milliseconds),
      pausedDuration(0),
      elapsedAtStop(0),
      running(false),
      paused(false),
      executed(false),
      repeat(shouldRepeat),
      callback(std::move(timerCallback))
{
}

void TimerTrigger::Start()
{
    startTime = std::chrono::steady_clock::now();
    pausedDuration = 0;
    elapsedAtStop = 0;

    running = true;
    paused = false;
    executed = false;
}

void TimerTrigger::Stop()
{
    if (running)
        elapsedAtStop = GetElapsedMilliseconds();

    running = false;
    paused = false;
}

void TimerTrigger::Pause()
{
    if (!running || paused)
        return;

    pauseTime = std::chrono::steady_clock::now();
    paused = true;
}

void TimerTrigger::Resume()
{
    if (!running || !paused)
        return;

    const auto now = std::chrono::steady_clock::now();

    pausedDuration +=
        std::chrono::duration_cast<
            std::chrono::milliseconds
        >(now - pauseTime).count();

    paused = false;
}

void TimerTrigger::Reset()
{
    startTime = std::chrono::steady_clock::now();
    pausedDuration = 0;
    elapsedAtStop = 0;

    running = true;
    paused = false;
    executed = false;
}

void TimerTrigger::Update()
{
    if (!running || paused)
        return;

    if (GetElapsedMilliseconds() >= interval)
    {
        executed = true;

        if (callback)
            callback();

        if (repeat)
        {
            Reset();
        }
        else
        {
            elapsedAtStop = GetElapsedMilliseconds();
            running = false;
        }
    }
}

bool TimerTrigger::IsRunning() const
{
    return running;
}

bool TimerTrigger::IsPaused() const
{
    return paused;
}

bool TimerTrigger::Executed() const
{
    return executed;
}

long long TimerTrigger::GetElapsedMilliseconds() const
{
    if (!running)
        return elapsedAtStop;

    const auto endTime =
        paused
            ? pauseTime
            : std::chrono::steady_clock::now();

    const long long elapsed =
        std::chrono::duration_cast<
            std::chrono::milliseconds
        >(endTime - startTime).count();

    return elapsed - pausedDuration;
}

long long TimerTrigger::GetRemainingMilliseconds() const
{
    const long long elapsed =
        GetElapsedMilliseconds();

    if (elapsed >= interval)
        return 0;

    return interval - elapsed;
}

std::string TimerTrigger::GetID() const
{
    return id;
}

}
