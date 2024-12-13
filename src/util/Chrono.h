#pragma once 

#include <chrono>

//! \class Chrono
//! \brief Class to measure time.
class Chrono
{
    public:
        Chrono();
        virtual ~Chrono();

        void Start();
        void Stop();
        void Reset();
        float GetElapsedTime(); // in seconds, usage when finished only !
        float GetCurrentDuration(); // in seconds, Only consider start timer, then calculate from there.

        void PrintElapsedTime();  
    private:
        std::chrono::system_clock::time_point m_startTime;
        std::chrono::system_clock::time_point m_stopTime;

        bool started;
        bool finished;
};