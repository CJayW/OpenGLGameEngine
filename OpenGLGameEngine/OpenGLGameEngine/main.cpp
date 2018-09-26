#include <iostream>

#include "Game.h"
#include "Input.h"

Game* game;
Input* input;
double lastFrameTime;

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

		game->Update(deltaTime);

		game->Render();
	}
	return 0;
}