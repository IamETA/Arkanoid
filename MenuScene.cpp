#include "MenuScene.h"
#include "GameScene.h"
#include "game.h"
#include "Highscores.h"

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
	mLogo = TextureManager::load_texture(".\\textures\\logo.png", renderer);

	SDL_Color selectedColor{ 0x0, 0xff, 0x0, 0xff };
	// construct text textures used to render textual contents.
	mExitTextSelected = TextureManager::create_text("Exit game", renderer, font, selectedColor);
	mHighscoresTextSelected = TextureManager::create_text("Highscores", renderer, font, selectedColor);
	mPlayTextSelected = TextureManager::create_text("Play", renderer, font, selectedColor);

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

MenuScene::~MenuScene()
{
	// define a helper function to be used to release textures.
#define RELEASE_TEXTURE(x) if (x != nullptr) { SDL_DestroyTexture(x); }

// release all reserved textures.
	RELEASE_TEXTURE(mExitText);
	RELEASE_TEXTURE(mHighscoresText);
	RELEASE_TEXTURE(mPlayText);
	RELEASE_TEXTURE(mLogo);
}

void MenuScene::update(float delta)
{
	// ...
}

void MenuScene::render()
{
	// get a reference to the SDL renderer.
	SDL_Renderer* renderer = mGame.getRenderer();
	if (selectedItem == 0) {
		SDL_RenderCopy(renderer, mPlayTextSelected, nullptr, &mPlayTextPosition);
	}
	else {
		SDL_RenderCopy(renderer, mPlayText, nullptr, &mPlayTextPosition);
	}
	if (selectedItem == 1) {
		SDL_RenderCopy(renderer, mHighscoresTextSelected, nullptr, &mHighscoresTextPosition);
	}
	else {
		SDL_RenderCopy(renderer, mHighscoresText, nullptr, &mHighscoresTextPosition);
	}
	if (selectedItem == 2) {
		SDL_RenderCopy(renderer, mExitTextSelected, nullptr, &mExitTextPosition);
	}
	else {
		SDL_RenderCopy(renderer, mExitText, nullptr, &mExitTextPosition);
	}

	SDL_RenderCopy(renderer, mLogo, nullptr, &mLogoPosition);

}

void MenuScene::enter()
{
	// ...
}

void MenuScene::exit()
{
	// ...
}
void MenuScene::executeMenu(int selection) {
	switch (selection) {
	case 0:
		mGame.enterScene(std::make_shared<GameScene>(mGame));
		break;
	case 1:
		break;
	case 2:
		mGame.exit();
		break;
	}
}

void MenuScene::keyUp(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym) {
	case SDLK_DOWN:
		selectedItem++;
		if (selectedItem > 2)selectedItem = 0;
		break;
	case SDLK_UP:
		selectedItem--;
		if (selectedItem < 0)selectedItem = 2;
		break;
	case SDLK_RETURN:
		executeMenu(selectedItem);
		break;
	}
}
void MenuScene::keyDown(SDL_KeyboardEvent& event)
{
}