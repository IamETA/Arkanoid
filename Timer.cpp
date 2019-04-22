//
// Created by mynewdog on 11.03.19.
//

#include "Timer.h"
#include <iostream>

namespace EngineUtils {
    Timer *Timer::sInstance = nullptr;

    Timer *Timer::Instance() {

        if (sInstance == nullptr) {
            sInstance = new Timer();
        }
        return sInstance;
    }

    void Timer::Release() {
        delete sInstance;
        //No dangling pointer
        sInstance = nullptr;
    }

    Timer::Timer() {
        Reset();
        m_time_scale = 1.0f;
        m_delta_time = std::chrono::duration<float>(0.0f);
    }

    Timer::~Timer() {
        std::cout << "Timer destroyed" << std::endl;
    }

    void Timer::Reset() {
        m_start_time = std::chrono::system_clock::now();
    }

    float Timer::delta_time() {
        return m_delta_time.count();
    }

    void Timer::time_scale(float t) {
        m_time_scale = t;
    }

    float Timer::time_scale() {
        return m_time_scale;
    }

    void Timer::Tick() {
        m_delta_time = std::chrono::system_clock::now() - m_start_time;
    }

    float Timer::get_frame_rate() {
        return frame_rate;
    }
}