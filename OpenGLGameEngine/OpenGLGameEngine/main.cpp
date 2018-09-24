#include <iostream>

#include "Game.h"
#include "Input.h"

Game* game;

double lastFrameTime;

int main()
{
	game = new Game();


	game->Init(800,600,false,"Engine");

	while (Game::Running) {

		double currentTime = Game::getTime();
		double deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		Input::ProcessInput();

		game->Update(deltaTime);

		game->Render();
	}
	return 0;
}