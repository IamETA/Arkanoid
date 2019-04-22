#include "SDL.h"
#include "Timer.h"
#include "Game.h"
#include "InputManager.h"

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 600

int main(int argc, char* argv[])
{

	//Burde ha opprettelse av klasser i en GameManager ???
	TimerUtils::Timer* timer = TimerUtils::Timer::Instance();
	InputUtils::InputManager* input = InputUtils::InputManager::Instance();

	Game::Game* game = nullptr;

	game = new Game::Game();

	game->init_window("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_WIDTH, false);

	while (game->running()) {

		timer->Tick();

		if (timer->delta_time() >= 1 / timer->get_frame_rate()) 
		{
			//Not changing delta_time when using reset()
			timer->Reset();
			//std::cout << timer->delta_time() << std::endl;

			game->handle_exit_event();
			game->update();
			game->render();
		}
	}

	game->clean();
	input->Release();
	timer->Release();

//	TimerUtils::Timer::Release();
	return 0;
}
