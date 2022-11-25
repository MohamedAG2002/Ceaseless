#pragma once

#include "Scene.h"

#include <string>

class Game
{
public:
	Game(const int&& windowWidth, const int&& windowHeight, const std::string& windowName, const int&& fps);
	~Game();

public:
	void Init();
	void Update();
	void Render();
	void Run();

private:
	SceneManager* m_sceneManager;
};