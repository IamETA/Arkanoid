#include "HighscoreScene.h"
#include "MenuScene.h"

HighscoreScene::HighscoreScene(Game& game) : Scene(game)
{

	std::cout << "Initializing HighScore Scene..." << std::endl;
	SDL_Renderer* renderer = game.getRenderer();
	TTF_Font* font = game.getFont();

	mHighscoresText = TextureManager::create_text("Highscores", renderer, font);
	mLogo = TextureManager::load_texture(".\\textures\\logo.png", renderer);

	SDL_Color selectedColor{ 0x0, 0xff, 0x0, 0xff };
	// construct text textures used to render textual contents.
	mHighscoresText = TextureManager::create_text("Your highscore: ", renderer, font, selectedColor);
	//mPlayTextSelected = TextureManager::create_text("Play", renderer, font, selectedColor);

	// query texture dimensions for each text texture.
	SDL_QueryTexture(mHighscoresText, nullptr, nullptr, &mHighscoresTextPosition.w, &mHighscoresTextPosition.h);
	//SDL_QueryTexture(mLogo, nullptr, nullptr, &mLogoPosition.w, &mLogoPosition.h);
	mLogoPosition.w = 400;
	mLogoPosition.h = 200;
	// get the rendering window size and calculate the center position.
	int windowWidth = 0, windowHeight = 0;
	SDL_GetWindowSize(mGame.getWindow(), &windowWidth, &windowHeight);
	int windowCenterX = (windowWidth / 2);

	// assign texts at the center of the screen.
#define CENTER(rect) (rect.x = windowCenterX - (rect.w / 2));
	CENTER(mHighscoresTextPosition);
	CENTER(mLogoPosition);

	int slotHeight = (windowHeight / 10);
	mLogoPosition.y = slotHeight;
	mHighscoresTextPosition.y = (5 * slotHeight);
}


HighscoreScene::~HighscoreScene()
{
#define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }
	std::cout << "Highscore scene destroyed" << std::endl;
	// release all reserved textures.
	RELEASE_TEXTURE(mHighscoresText);
	RELEASE_TEXTURE(mLogo);
}

void HighscoreScene::updateHighscore()
{
	auto mHighscoresText = "Highscore: " + (highscore->readFile());

}

void HighscoreScene::render()
{
	auto renderer = mGame.getRenderer();
	SDL_RenderCopy(renderer, mLogo, nullptr, &mLogoPosition);
	SDL_RenderCopy(renderer, mHighscoresText, nullptr, &mHighscoresTextPosition);
}

void HighscoreScene::enter()
{
}

void HighscoreScene::exit()
{
}

void HighscoreScene::keyUp(SDL_KeyboardEvent& event)
{
}

void HighscoreScene::keyDown(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym) {
	case SDLK_ESCAPE:
		mGame.enterScene(std::make_shared<MenuScene>(mGame));
		break;
	}
	
}
