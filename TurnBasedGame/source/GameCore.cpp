#include "../header/Game.h"

// 0 = Render,,, 1 = Update,,, 2 = Events
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
	// Error
	else {
		cout << "ERROR: Route '" << route << "' not found.\n";
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
	mainGameDestroy();
}

void Game::initialize() {
	buildFontManager();
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	srand((unsigned)time(0));
	gameRunning = true;
	FPS.start();
	//routeManager(3);

	mainGameBuild();
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
	updateText(key, text);
	updateText(key, x, y);
}

void Game::newImage(string key, string path, int x, int y) {
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

void Game::clearMapKey(string key) {
	if (dynamicMap.find(key) != dynamicMap.end()) {
		dynamicMap[key].free();
		dynamicMap.erase(key);
	}
}

//Rounds the variable to the given decimal places
string Game::roundTo(double var, int dec) {
	stringstream ss;
	ss << fixed << setprecision(dec) << var;
	return ss.str();
}
