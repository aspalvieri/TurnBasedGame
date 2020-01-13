#include "../header/Game.h"

void Game::handleEvents() {
	capFPS.start();
	//Reset button release pointers
	*leftReleased = false;
	*rightReleased = false;

	while (SDL_PollEvent(&e) != 0) {
		//Update the user's mouse properties
		if (e.type == SDL_MOUSEMOTION) {
			SDL_GetMouseState(&mPos->x, &mPos->y);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				*leftDown = true;
			}
			if (e.button.button == SDL_BUTTON_RIGHT) {
				*rightDown = true;
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			if (e.button.button == SDL_BUTTON_LEFT) {
				*leftDown = false;
				*leftReleased = true;
			}
			if (e.button.button == SDL_BUTTON_RIGHT) {
				*rightDown = false;
				*rightReleased = true;
			}
		}

		////Global Events

		//User presses exit button (top-right)
		if (e.type == SDL_QUIT) {
			gameRunning = false;
			cout << "Exited game.\n";
			break;
		}

		//User pressed a key down
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			//Closes game
			case SDLK_ESCAPE:
				gameRunning = false;
				cout << "Exited game.\n";
				return;
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
			default:
				break;
			}
		}

		//Handle events for current game screen
		routeManager(2);
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
