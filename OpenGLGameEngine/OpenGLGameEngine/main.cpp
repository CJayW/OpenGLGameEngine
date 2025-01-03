#include "EditorDebug.h"

#include "Game.h"
#include "Input.h"
#include "Time.h"

#include <glm/glm.hpp>

Game* game;
Input* input;
double lastFrameTime;

bool gettingTime = false;
double currentFPSTime = 0;
int getTimeCount = 0;

int main()
{
	game = new Game();
	game->Init(800,600,true,"Engine");
	input = new Input();
	game->Start();

	while (Game::Running) {
		double currentTime = Game::getTime();
		double deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		input->ProcessInput();

#pragma region Average FPS Check
		if (Input::getKeyDown(GLFW_KEY_P)) {
			
			gettingTime = true;
			currentFPSTime = 0;
			getTimeCount = 0;
			EditorDebug::PermLog("Start Average FPS Check");
		}

		if (gettingTime) {
			if (getTimeCount < 10000) {
				currentFPSTime += deltaTime;
				getTimeCount++;
			} else {
				EditorDebug::PermLog(std::to_string(1 / (currentFPSTime / getTimeCount)) + std::string(" FPS"));
				gettingTime = false;
			}
		}
#pragma endregion

		Time::deltaTime = (float)deltaTime;

		game->Update(deltaTime * Time::timeScale);

		game->Render();
	}
	return 0;
}