#include "HighscoreScene.h"


HighscoreScene::HighscoreScene(Game& game) : Scene(game),
mExitText(nullptr),
mHighscoresText(nullptr),
mPlayText(nullptr)
{

	SDL_Renderer* renderer = game.getRenderer();
	TTF_Font* font = game.getFont();


	// construct text textures used to render textual contents.
	mExitText = TextureManager::create_text("Exit game", renderer, font);
	mHighscoresText = TextureManager::create_text("Highscores", renderer, font);
	mPlayText = TextureManager::create_text("Restart game", renderer, font);
	mLogo = TextureManager::load_texture(".\\textures\\logo.png", renderer);

	SDL_Color selectedColor{ 0x0, 0xff, 0x0, 0xff };
	// construct text textures used to render textual contents.
	mExitTextSelected = TextureManager::create_text("Exit game", renderer, font, selectedColor);
	mHighscoresText = TextureManager::create_text("Your highscore: ", renderer, font, selectedColor);
	//mPlayTextSelected = TextureManager::create_text("Play", renderer, font, selectedColor);

	// query texture dimensions for each text texture.
	SDL_QueryTexture(mExitText, nullptr, nullptr, &mExitTextPosition.w, &mExitTextPosition.h);
	SDL_QueryTexture(mHighscoresText, nullptr, nullptr, &mHighscoresTextPosition.w, &mHighscoresTextPosition.h);
	SDL_QueryTexture(mPlayText, nullptr, nullptr, &mPlayTextPosition.w, &mPlayTextPosition.h);
	//SDL_QueryTexture(mLogo, nullptr, nullptr, &mLogoPosition.w, &mLogoPosition.h);
	mLogoPosition.w = 400;
	mLogoPosition.h = 200;
	// get the rendering window size and calculate the center position.
	int windowWidth = 0, windowHeight = 0;
	SDL_GetWindowSize(mGame.getWindow(), &windowWidth, &windowHeight);
	int windowCenterX = (windowWidth / 2);

	// assign texts at the center of the screen.
#define CENTER(rect) (rect.x = windowCenterX - (rect.w / 2));
	CENTER(mExitTextPosition);
	CENTER(mHighscoresTextPosition);
	CENTER(mPlayTextPosition);
	CENTER(mLogoPosition);

	// assign vertical positions for each texture.
	int slotHeight = (windowHeight / 10);
	mPlayTextPosition.y = 4 * slotHeight;

	mLogoPosition.y = slotHeight;
	//mControlTextPosition.y = static_cast<int>(2.5 * slotHeight);
	mHighscoresTextPosition.y = (5 * slotHeight);
	mExitTextPosition.y = (6 * slotHeight);
}


HighscoreScene::~HighscoreScene()
{
#define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }

	// release all reserved textures.
	RELEASE_TEXTURE(mExitText);
	RELEASE_TEXTURE(mHighscoresText);
	RELEASE_TEXTURE(mPlayText);
}

void HighscoreScene::updateHighscore()
{
	auto mHighscoresText = "Highscore: " + (highscore->readFile());

}

void HighscoreScene::render()
{
	// get a reference to the SDL renderer.
	SDL_Renderer* renderer = mGame.getRenderer();
	if (selectedItem == 0) {
		SDL_RenderCopy(renderer, mPlayTextSelected, nullptr, &mPlayTextPosition);
	}
	else {
		SDL_RenderCopy(renderer, mPlayText, nullptr, &mPlayTextPosition);
	}
	if (selectedItem == 2) {
		SDL_RenderCopy(renderer, mExitTextSelected, nullptr, &mExitTextPosition);
	}
	else {
		SDL_RenderCopy(renderer, mExitText, nullptr, &mExitTextPosition);
	}

	SDL_RenderCopy(renderer, mLogo, nullptr, &mLogoPosition);
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
}
