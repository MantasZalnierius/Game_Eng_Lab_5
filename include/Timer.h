#pragma once
#include <SDL_timer.h>
#include <cstdint>
typedef unsigned int uint32_t;

class Timer
{
private:
public:
    Timer() 
    { 
        restart(); 
    }

    void restart() 
    {
        m_timer = 0;
        start();
    }

    void start() 
    {
        m_timer = SDL_GetTicks();
    }

    float getTimerAsSeconds() 
    {
        return getTicks() / 1000.0f;
    }

    uint32_t getTicks() {return SDL_GetTicks() - m_timer;}

private:
    uint32_t m_timer;
};