#include "timertrigger.hpp"


namespace Toollibs
{


TimerTrigger::TimerTrigger()
{
    interval = 0;

    pausedDuration = 0;


    running = false;

    paused = false;

    executed = false;

    repeat = false;
}



TimerTrigger::TimerTrigger(
    const std::string& timerID,
    long long milliseconds,
    std::function<void()> function,
    bool repeatTimer
)
{

    id = timerID;

    interval = milliseconds;

    callback = function;

    repeat = repeatTimer;


    pausedDuration = 0;


    running = false;

    paused = false;

    executed = false;

}



void TimerTrigger::Start()
{

    startTime =
        std::chrono::steady_clock::now();


    pausedDuration = 0;


    running = true;

    paused = false;

    executed = false;

}



void TimerTrigger::Stop()
{

    running = false;

    paused = false;

}



void TimerTrigger::Pause()
{

    if(!running || paused)
        return;


    pauseTime =
        std::chrono::steady_clock::now();


    paused = true;

}



void TimerTrigger::Resume()
{

    if(!paused)
        return;



    auto now =
        std::chrono::steady_clock::now();



    pausedDuration +=
        std::chrono::duration_cast<
            std::chrono::milliseconds
        >(now - pauseTime)
        .count();



    paused = false;

}



void TimerTrigger::Reset()
{

    startTime =
        std::chrono::steady_clock::now();


    pausedDuration = 0;


    executed = false;

}



void TimerTrigger::Update()
{

    if(!running || paused)
        return;



    if(GetElapsedMilliseconds() >= interval)
    {

        if(callback)
        {
            callback();
        }


        executed = true;



        if(repeat)
        {
            Reset();
        }
        else
        {
            Stop();
        }

    }


}



long long TimerTrigger::GetElapsedMilliseconds() const
{

    if(!running)
        return 0;


    auto now =
        std::chrono::steady_clock::now();



    return
        std::chrono::duration_cast<
            std::chrono::milliseconds
        >(now - startTime)
        .count()
        -
        pausedDuration;

}



long long TimerTrigger::GetRemainingMilliseconds() const
{

    long long remaining =
        interval -
        GetElapsedMilliseconds();



    return remaining > 0 ? remaining : 0;

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



std::string TimerTrigger::GetID() const
{
    return id;
}



}