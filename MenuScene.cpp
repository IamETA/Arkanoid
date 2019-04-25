#include "MenuScene.h"
#include "GameScene.h"
#include "game.h"
#include "Highscores.h"

MenuScene::MenuScene(Game& game) : Scene(game),
	m_exit_text(nullptr),
	m_highscores_text(nullptr),
	m_play_text(nullptr)
{

	std::cout << "Initializing MenuScene..." << std::endl;
	SDL_Renderer* renderer = game.get_renderer();
	TTF_Font* font = game.get_font();


	// construct text textures used to render textual contents.
	m_exit_text = TextureManager::create_text("Exit game",renderer,font);
	m_highscores_text = TextureManager::create_text("Highscores",renderer,font);
	m_play_text = TextureManager::create_text("Play",renderer,font);
	m_logo = TextureManager::load_texture(".\\textures\\logo.png", renderer);

	SDL_Color selectedColor{ 0x0, 0xff, 0x0, 0xff };
	// construct text textures used to render textual contents.
	m_exit_text_selected = TextureManager::create_text("Exit game", renderer, font, selectedColor);
	m_highscore_text_selected = TextureManager::create_text("Highscores", renderer, font, selectedColor);
	m_play_text_selected = TextureManager::create_text("Play", renderer, font, selectedColor);

	// query texture dimensions for each text texture.
	SDL_QueryTexture(m_exit_text, nullptr, nullptr, &m_exit_text_pos.w, &m_exit_text_pos.h);
	SDL_QueryTexture(m_highscores_text, nullptr, nullptr, &m_highscore_text_pos.w, &m_highscore_text_pos.h);
	SDL_QueryTexture(m_play_text, nullptr, nullptr, &m_play_text_pos.w, &m_play_text_pos.h);
	//SDL_QueryTexture(mLogo, nullptr, nullptr, &mLogoPosition.w, &mLogoPosition.h);
	m_logo_pos.w = 400; 
	m_logo_pos.h = 200;
	// get the rendering window size and calculate the center position.
	int windowWidth = 0, windowHeight = 0;
	SDL_GetWindowSize(mGame.get_window(), &windowWidth, &windowHeight);
	int windowCenterX = (windowWidth / 2);

	// assign texts at the center of the screen.
#define CENTER(rect) (rect.x = windowCenterX - (rect.w / 2));
	CENTER(m_exit_text_pos);
	CENTER(m_highscore_text_pos);
	CENTER(m_play_text_pos);
	CENTER(m_logo_pos);
	
	// assign vertical positions for each texture.
	int slotHeight = (windowHeight / 10);
	m_play_text_pos.y = 4 * slotHeight;
	
	m_logo_pos.y = slotHeight;
	//mControlTextPosition.y = static_cast<int>(2.5 * slotHeight);
	m_highscore_text_pos.y = (5 * slotHeight);
	m_exit_text_pos.y = (6 * slotHeight);
}

MenuScene::~MenuScene()
{
	// define a helper function to be used to release textures.
#define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }

// release all reserved textures.
	RELEASE_TEXTURE(m_exit_text);
	RELEASE_TEXTURE(m_highscores_text);
	RELEASE_TEXTURE(m_play_text);
	RELEASE_TEXTURE(m_exit_text_selected);
	RELEASE_TEXTURE(m_highscore_text_selected);
	RELEASE_TEXTURE(m_play_text_selected);
	RELEASE_TEXTURE(m_logo);

	std::cout << "MenuScene destroyed" << std::endl;
}

void MenuScene::update(float delta)
{
	// ...
}

void MenuScene::render()
{
	// get a reference to the SDL renderer.
	SDL_Renderer* renderer = mGame.get_renderer();
	if (selected_item == 0)
	{
		SDL_RenderCopy(renderer, m_play_text_selected, nullptr, &m_play_text_pos);
	}
	else 
	{
		SDL_RenderCopy(renderer, m_play_text, nullptr, &m_play_text_pos);
	}
	if (selected_item == 1) 
	{
		SDL_RenderCopy(renderer, m_highscore_text_selected, nullptr, &m_highscore_text_pos);
	}
	else 
	{
		SDL_RenderCopy(renderer, m_highscores_text, nullptr, &m_highscore_text_pos);
	}
	if (selected_item == 2)
	{
		SDL_RenderCopy(renderer, m_exit_text_selected, nullptr, &m_exit_text_pos);
	}
	else
	{
		SDL_RenderCopy(renderer, m_exit_text, nullptr, &m_exit_text_pos);
	}

	SDL_RenderCopy(renderer, m_logo, nullptr, &m_logo_pos);

}

void MenuScene::enter()
{
	// ...
}

void MenuScene::exit()
{
	// ...
}
void MenuScene::execute_menu(int selection) 
{
	switch (selection)
	{
	case 0:
		mGame.enter_scene(std::make_shared<GameScene>(mGame));
		break;
	case 1:
		break;
	case 2:
		mGame.exit();
		break;
	}
}

void MenuScene::key_up(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym)
	{
	case SDLK_DOWN:
		selected_item++;
		if (selected_item > 2)selected_item = 0;
		break;
	case SDLK_UP:
		selected_item--;
		if (selected_item < 0)selected_item = 2;
		break;
	case SDLK_RETURN:
		execute_menu(selected_item);
		break;
	}
}
void MenuScene::key_down(SDL_KeyboardEvent& event)
{
}