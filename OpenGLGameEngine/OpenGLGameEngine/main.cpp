#include <iostream>

#include "Game.h"
#include "Input.h"

Game* game;
Input* input;
double lastFrameTime;

bool gettingTime = false;
double currentFPSTime = 0;
int getTimeCount = 0;

int main()
{
	game = new Game();

	game->Init(800,600,false,"Engine");

	input = new Input();

	game->Start();

	while (Game::Running) {
		double currentTime = Game::getTime();
		double deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		input->ProcessInput();

		if (Input::getKeyDown(GLFW_KEY_P)) {
			
			gettingTime = true;
			currentFPSTime = 0;
			getTimeCount = 0;
			std::cout << "Start Average FPS Check" << std::endl;
		}

		if (gettingTime) {
			if (getTimeCount < 100000) {
				currentFPSTime += deltaTime;
				getTimeCount++;
			} else {
				std::cout << 1 / (currentFPSTime / getTimeCount) << " FPS" << std::endl;
				gettingTime = false;
			}
		}

		game->Update(deltaTime);

		game->Render();
	}
	return 0;
}