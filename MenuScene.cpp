#include "MenuScene.h"
#include "game.h"
#include "TextureManager.h"
#include <SDL.h>

using namespace Game;

MenuScene::MenuScene(Game& game) : Scene(game),
	mExitText(nullptr),
	mHighscoresText(nullptr),
	mPlayText(nullptr)
{

	SDL_Renderer* renderer = game.getRenderer();
	TTF_Font* font = game.getFont();


	// construct text textures used to render textual contents.
	mExitText = TextureManager::create_text("Exit game",renderer,font);
	mHighscoresText = TextureManager::createText("Highscores",renderer,font);
	mPlayText = TextureManager::createText("Play",renderer,font);

	// query texture dimensions for each text texture.
	SDL_QueryTexture(mTopicText, nullptr, nullptr, &mTopicTextPosition.w, &mTopicTextPosition.h);
	SDL_QueryTexture(mControlsText, nullptr, nullptr, &mControlTextPosition.w, &mControlTextPosition.h);
	SDL_QueryTexture(mSpacebarText, nullptr, nullptr, &mSpacebarTextPosition.w, &mSpacebarTextPosition.h);

	// get the rendering window size and calculate the center position.
	int windowWidth = 0, windowHeight = 0;
	SDL_GetWindowSize(mGame.getWindow(), &windowWidth, &windowHeight);
	int windowCenterX = (windowWidth / 2);

	// assign texts at the center of the screen.
#define CENTER(rect) (rect.x = windowCenterX - (rect.w / 2));
	CENTER(mTopicTextPosition);
	CENTER(mControlTextPosition);
	CENTER(mSpacebarTextPosition);
	CENTER(mLeftArrowTextPosition);
	CENTER(mRightArrowTextPosition);
	CENTER(mOnePlayerGameTextPosition);
	CENTER(mTwoPlayerGameTextPosition);

	// assign vertical positions for each texture.
	int slotHeight = (windowHeight / 10);
	mTopicTextPosition.y = slotHeight;
	mControlTextPosition.y = static_cast<int>(2.5 * slotHeight);
	mSpacebarTextPosition.y = (3 * slotHeight);
	mLeftArrowTextPosition.y = static_cast<int>(3.5 * slotHeight);
	mRightArrowTextPosition.y = (4 * slotHeight);
	mOnePlayerGameTextPosition.y = (6 * slotHeight);
	mTwoPlayerGameTextPosition.y = (7 * slotHeight);
}

MenuScene::~MenuScene()
{
	// define a helper function to be used to release textures.
#define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }

// release all reserved textures.
	RELEASE_TEXTURE(mTopicText);
	RELEASE_TEXTURE(mControlsText);
	RELEASE_TEXTURE(mSpacebarText);
	RELEASE_TEXTURE(mLeftArrowText);
	RELEASE_TEXTURE(mRightArrowText);
	RELEASE_TEXTURE(mOnePlayerGameText);
	RELEASE_TEXTURE(mTwoPlayerGameText);
}

void MenuScene::update(float dt)
{
	// ...
}

void MenuScene::render()
{
	// get a reference to the SDL renderer.
	auto& renderer = mGame.getRenderer();

	// draw all texts on the buffer.
	SDL_RenderCopy(&renderer, mTopicText, nullptr, &mTopicTextPosition);
	SDL_RenderCopy(&renderer, mControlsText, nullptr, &mControlTextPosition);
	SDL_RenderCopy(&renderer, mSpacebarText, nullptr, &mSpacebarTextPosition);
	SDL_RenderCopy(&renderer, mLeftArrowText, nullptr, &mLeftArrowTextPosition);
	SDL_RenderCopy(&renderer, mRightArrowText, nullptr, &mRightArrowTextPosition);
	SDL_RenderCopy(&renderer, mOnePlayerGameText, nullptr, &mOnePlayerGameTextPosition);
	SDL_RenderCopy(&renderer, mTwoPlayerGameText, nullptr, &mTwoPlayerGameTextPosition);
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
		mGame.enterScene(std::make_shared<GameScene>(mGame));
		break;
	}
}