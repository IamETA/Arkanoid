#include "MenuScene.h"
#include "GameScene.h"
#include "game.h"

MenuScene::MenuScene(Game& game) : Scene(game),
	mExitText(nullptr),
	mHighscoresText(nullptr),
	mPlayText(nullptr)
{

	SDL_Renderer* renderer = game.getRenderer();
	TTF_Font* font = game.getFont();


	// construct text textures used to render textual contents.
	mExitText = TextureManager::create_text("Exit game",renderer,font);
	mHighscoresText = TextureManager::create_text("Highscores",renderer,font);
	mPlayText = TextureManager::create_text("Play",renderer,font);

	// query texture dimensions for each text texture.
	SDL_QueryTexture(mExitText, nullptr, nullptr, &mExitTextPosition.w, &mExitTextPosition.h);
	SDL_QueryTexture(mHighscoresText, nullptr, nullptr, &mHighscoresTextPosition.w, &mHighscoresTextPosition.h);
	SDL_QueryTexture(mPlayText, nullptr, nullptr, &mPlayTextPosition.w, &mPlayTextPosition.h);

	// get the rendering window size and calculate the center position.
	int windowWidth = 0, windowHeight = 0;
	SDL_GetWindowSize(mGame.getWindow(), &windowWidth, &windowHeight);
	int windowCenterX = (windowWidth / 2);

	// assign texts at the center of the screen.
#define CENTER(rect) (rect.x = windowCenterX - (rect.w / 2));
	CENTER(mExitTextPosition);
	CENTER(mHighscoresTextPosition);
	CENTER(mPlayTextPosition);

	// assign vertical positions for each texture.
	int slotHeight = (windowHeight / 10);
	mPlayTextPosition.y = 2 * slotHeight;
	//mControlTextPosition.y = static_cast<int>(2.5 * slotHeight);
	mHighscoresTextPosition.y = (3 * slotHeight);
	mExitTextPosition.y = (4 * slotHeight);
}

MenuScene::~MenuScene()
{
	// define a helper function to be used to release textures.
#define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }

// release all reserved textures.
	RELEASE_TEXTURE(mExitText);
	RELEASE_TEXTURE(mHighscoresText);
	RELEASE_TEXTURE(mPlayText);
}

void MenuScene::update(unsigned int dt)
{
	// ...
}

void MenuScene::render()
{
	// get a reference to the SDL renderer.
	SDL_Renderer* renderer = mGame.getRenderer();

	// draw all texts on the buffer.
	SDL_RenderCopy(renderer, mExitText, nullptr, &mExitTextPosition);
	SDL_RenderCopy(renderer, mHighscoresText, nullptr, &mHighscoresTextPosition);
	SDL_RenderCopy(renderer, mPlayText, nullptr, &mPlayTextPosition);
}

void MenuScene::enter()
{
	// ...
}

void MenuScene::exit()
{
	// ...
}


void MenuScene::keyUp(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym) {
	case SDLK_1:
		///mGame.enterScene(std::make_shared<GameScene>(mGame));
		break;
	}
}
void MenuScene::keyDown(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym) {
	case SDLK_1:
		///mGame.enterScene(std::make_shared<GameScene>(mGame));
		break;
	}
}