#include "../header/Game.h"

// 0 = Render,,, 1 = Update,,, 2 = Events,,, 3 = Build,,, 4 = Destory
void Game::routeManager(int route) {
	// Render
	if (route == 0) {
		if (currentScreen == "mainGame")
			mainGameRender();
	}
	// Update
	else if (route == 1) {
		if (currentScreen == "mainGame")
			mainGameUpdate();
	}
	// Events
	else if (route == 2) {
		if (currentScreen == "mainGame")
			mainGameEvents();
	}
	// Build
	else if (route == 3) {
		if (currentScreen == "mainGame")
			mainGameBuild();
	}
	// Destroy
	else if (route == 4) {
		if (currentScreen == "mainGame")
			mainGameDestroy();
	}
}

Game::Game() {
	gRenderer = SDLR::gRenderer;
	gWindow = SDLR::gWindow;

	camera = &SDLR::camera;
	leftDown = &SDLR::leftDown;
	leftReleased = &SDLR::leftReleased;
	rightDown = &SDLR::rightDown;
	rightReleased = &SDLR::rightReleased;
	mPos = &SDLR::mPos;
	mPosCam = &SDLR::mPosCam;
}

Game::~Game() {

}

void Game::initialize() {
	buildFontManager();
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	srand((unsigned)time(0));
	gameRunning = true;
	FPS.start();
	routeManager(3);
}

bool Game::running() {
	return gameRunning;
}

void Game::buildFontManager() {
	//Load font sizes into fontManager for later use
	for (int i = 12; i <= 24; i += 2) {
		//Old font
		//fontManager[i] = TTF_OpenFont("bin/fonts/codenewroman.ttf", i);
		fontManager[i] = TTF_OpenFont("bin/fonts/montserratmedium.ttf", i);
		fontManagerBold[i] = TTF_OpenFont("bin/fonts/montserratbold.ttf", i);
	}
}

void Game::newText(string key, string text, TTF_Font * gFont, int x, int y, SDL_Color textColor, int wrapLength) {
	dynamicMap[key].loadFont(text, textColor, gFont, wrapLength);
	dynamicMap[key].x = x;
	dynamicMap[key].y = y;
	dynamicMap[key].font = gFont;
	dynamicMap[key].textColor = textColor;
	dynamicMap[key].wrapLength = wrapLength;
}

void Game::updateText(string key, string text) {
	dynamicMap[key].loadFont(text, dynamicMap[key].textColor, dynamicMap[key].font, dynamicMap[key].wrapLength);
}
void Game::updateText(string key, int x, int y) {
	dynamicMap[key].x = x;
	dynamicMap[key].y = y;
}
void Game::updateText(string key, string text, int x, int y) {
	dynamicMap[key].loadFont(text, dynamicMap[key].textColor, dynamicMap[key].font, dynamicMap[key].wrapLength);
	dynamicMap[key].x = x;
	dynamicMap[key].y = y;
}

void Game::newImage(string key, std::string path, int x, int y) {
	dynamicMap[key].loadImage(path);
	dynamicMap[key].x = x;
	dynamicMap[key].y = y;
}

void Game::clearDynamicMap() {
	for (auto& line : dynamicMap) {
		line.second.free();
	}
	dynamicMap.clear();
}
