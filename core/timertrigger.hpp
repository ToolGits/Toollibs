#pragma once

#include <chrono>
#include <functional>
#include <string>


namespace Toollibs
{

class TimerTrigger
{

public:

    TimerTrigger();


    TimerTrigger(
        const std::string& timerID,
        long long milliseconds,
        std::function<void()> callback,
        bool repeat = false
    );


    void Start();

    void Stop();

    void Pause();

    void Resume();

    void Reset();

    void Update();



    bool IsRunning() const;

    bool IsPaused() const;

    bool Executed() const;



    long long GetElapsedMilliseconds() const;

    long long GetRemainingMilliseconds() const;


    std::string GetID() const;



private:


    std::string id;


    std::chrono::steady_clock::time_point startTime;

    std::chrono::steady_clock::time_point pauseTime;



    long long interval;


    long long pausedDuration;



    bool running;

    bool paused;

    bool executed;

    bool repeat;



    std::function<void()> callback;


};


}