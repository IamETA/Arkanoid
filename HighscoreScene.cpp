#include "HighscoreScene.h"
#include "MenuScene.h"
HighscoreScene::HighscoreScene(Game& game) : Scene(game)
{

	std::cout << "Initializing HighScore Scene..." << std::endl;
	SDL_Renderer* renderer = game.get_renderer();
	TTF_Font* font = game.get_font();

	m_highscores_text = TextureManager::create_text("Highscores", renderer, font);
	m_logo = TextureManager::load_texture(".\\textures\\logo.png", renderer);

	SDL_Color selectedColor{ 0x0, 0xff, 0x0, 0xff };
	// construct text textures used to render textual contents.
	m_highscores_text = TextureManager::create_text("Highscores: ", renderer, font, selectedColor);
	//mPlayTextSelected = TextureManager::create_text("Play", renderer, font, selectedColor);

	// query texture dimensions for each text texture.
	SDL_QueryTexture(m_highscores_text, nullptr, nullptr, &m_highscore_text_pos.w, &m_highscore_text_pos.h);
	//SDL_QueryTexture(mLogo, nullptr, nullptr, &mLogoPosition.w, &mLogoPosition.h);
	m_logo_pos.w = 400;
	m_logo_pos.h = 200;
	// get the rendering window size and calculate the center position.
	int windowWidth = 0, windowHeight = 0;
	SDL_GetWindowSize(mGame.get_window(), &windowWidth, &windowHeight);
	int windowCenterX = (windowWidth / 2);

	// assign texts at the center of the screen.
#define CENTER(rect) (rect.x = windowCenterX - (rect.w / 2));
	CENTER(m_highscore_text_pos);
	CENTER(m_logo_pos);

	int slotHeight = (windowHeight / 10);
	m_logo_pos.y = slotHeight;
	m_highscore_text_pos.y = (5 * slotHeight);

	highscore_string = highscore->read_file();

}


HighscoreScene::~HighscoreScene()
{
#define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }
	std::cout << "Highscore scene destroyed" << std::endl;
	// release all reserved textures.
	RELEASE_TEXTURE(m_highscores_text);
	RELEASE_TEXTURE(m_logo);
}

void HighscoreScene::update_highscore()
{
	auto m_highscores_text = "Highscore: " + (highscore->read_file());

}

void HighscoreScene::render()
{
	auto renderer = mGame.get_renderer();
	auto font = mGame.get_font();

	SDL_RenderCopy(renderer, m_logo, nullptr, &m_logo_pos);
	SDL_RenderCopy(renderer, m_highscores_text, nullptr, &m_highscore_text_pos);

	std::stringstream highscore_list(highscore_string);
	const char delim = '\n';
	std::stringstream ss(highscore_string);
	std::string highscore_value;
	int index{ 0 };


	// get the rendering window size and calculate the center position.
	int windowWidth = 0, windowHeight = 0;
	SDL_GetWindowSize(mGame.get_window(), &windowWidth, &windowHeight);
	int windowCenterX = (windowWidth / 2);


	while (std::getline(ss, highscore_value, delim) || (index < 3)) {
		index++;
		if (!highscore_value.empty()) {
			auto renderText = TextureManager::create_text(highscore_value, renderer, font);
			SDL_Rect renderPosition{ 0,0,0,0 };
			SDL_QueryTexture(renderText, nullptr, nullptr, &renderPosition.w, &renderPosition.h);
			renderPosition.x = windowCenterX - (renderPosition.w / 2);
			renderPosition.y = 300 + (index * 60);
			SDL_RenderCopy(renderer, renderText, nullptr, &renderPosition);
		}
		
	}
}

void HighscoreScene::enter()
{
}

void HighscoreScene::exit()
{
}

void HighscoreScene::key_up(SDL_KeyboardEvent& event)
{
}

void HighscoreScene::key_down(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym)
	{
	case SDLK_ESCAPE:
		mGame.enter_scene(std::make_shared<MenuScene>(mGame));
		break;
	}
	
}
