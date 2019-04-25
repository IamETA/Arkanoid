#pragma once

#include <chrono>
#include <iosfwd>

namespace TimerUtils {

	class Timer {

	private:

		static Timer* sInstance;
		std::chrono::steady_clock::time_point m_start_time;
		std::chrono::duration<float> m_delta_time;
		float m_time_scale;
		float frame_rate = 60.0f;

	public:

		static Timer* Instance();
		static void Release();
		void reset();
		float delta_time();

		//What to use time_scale for?
		void time_scale(float t = 1.0f);
		float time_scale();
		void tick();
		std::chrono::steady_clock::time_point start_time();
		float get_frame_rate();
		float delay();
		explicit Timer();
		~Timer();

	};

}

