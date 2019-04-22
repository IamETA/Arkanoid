//
// Created by mynewdog on 11.03.19.
//

#ifndef ARCADEGAME_TIMER_H
#define ARCADEGAME_TIMER_H

#include <chrono>
#include <iosfwd>


namespace EngineUtils {

    class Timer {

    private:
        static Timer *sInstance;

        std::chrono::system_clock::time_point m_start_time;
        std::chrono::duration<float> m_delta_time;
        float m_time_scale;
        float frame_rate = 60.0f;

    public:
        static Timer *Instance();

        static void Release();

        void Reset();

        float delta_time();

        //What to use time_scale for?

        void time_scale(float t = 1.0f);

        float time_scale();

        void Tick();

        float get_frame_rate();



    private:
        explicit Timer();
        ~Timer();

    };


}


#endif //ARCADEGAME_TIMER_H
