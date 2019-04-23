//
// Created by mynewdog on 11.03.19.
//

#include "Timer.h"
#include <iostream>

namespace TimerUtils {
    Timer *Timer::sInstance = nullptr;

    Timer *Timer::Instance() {

        if (sInstance == nullptr) 
		{
            sInstance = new Timer();
        }
        return sInstance;
    }

    void Timer::Release() 
	{
        delete sInstance;
        sInstance = nullptr;
    }

    Timer::Timer() 
	{
        Reset();
        m_time_scale = 1.0f;
        m_delta_time = std::chrono::duration<float>(0.0f);
    }

    Timer::~Timer() 
	{	
        std::cout << "Timer destroyed" << std::endl;
    }
	std::chrono::steady_clock::time_point Timer::start_time() {
		return m_start_time;
	}
    void Timer::Reset() 
	{
        m_start_time = std::chrono::high_resolution_clock::now();
    }

    float Timer::delta_time()
	{
        return m_delta_time.count();
    }

    void Timer::time_scale(float t) 
	{
        m_time_scale = t;
    }

    float Timer::time_scale() 
	{
        return m_time_scale;
    }

    void Timer::Tick()
	{
        m_delta_time = std::chrono::high_resolution_clock::now() - m_start_time;
    }
	float Timer::Delay() {
		auto delay = std::chrono::high_resolution_clock::now() - m_start_time;
		return delay.count();
	}

    float Timer::get_frame_rate()
	{
        return frame_rate;
    }
}