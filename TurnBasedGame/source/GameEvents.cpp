#include "../header/Game.h"

void Game::handleEvents() {
	capFPS.start();
	while (SDL_PollEvent(&e) != 0) {
		//Update the user's mouse properties
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
			*mouseButton = SDL_GetMouseState(&mousePos->first, &mousePos->second);
			mPos->x = mousePos->first;
			mPos->y = mousePos->second;
		}

		//User pressed a key down
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			//Closes game
			case SDLK_ESCAPE:
				gameRunning = false;
				cout << "Exited game.\n";
				break;
			default:
				break;
			}
		}

		//User released a key
		if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
			//Resets fps
			case SDLK_p:
				averageFPS = 0;
				countedFrames = 0;
				FPS.reset();
				cout << "Reset FPS.\n";
				break;
			case SDLK_w:
				newline(0, "I was created in the initialize function.", fontManager[16], 0, 30);
				newline(0, "I exist forever without any new updates.", fontManager[16], 0, 60);
				newline(0, "Just render me. Off I go.", fontManager[16], 0, 90);
				break;
			case SDLK_a:
				clearLineLayer(0);
				break;
			case SDLK_d:
				clearAllLineLayers();
				break;
			default:
				break;
			}
		}

		//User presses exit button (top-right)
		if (e.type == SDL_QUIT) {
			gameRunning = false;
			cout << "Exited game.\n";
			break;
		}
	}
}

void Game::limitFPS() {
	//Cap FPS
	countedFrames++;
	if (averageFPS > (SCREEN_FPS + 1)) {
		int frameTicks = capFPS.getTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME) {
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}
	}
}
