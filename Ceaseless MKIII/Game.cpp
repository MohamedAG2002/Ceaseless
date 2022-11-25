#include "Game.h"
#include "Assets.h"

#include <raylib.h>

Game::Game(const int&& windowWidth, const int&& windowHeight, const std::string& windowName, const int&& fps)
{
	InitWindow(windowWidth, windowHeight, windowName.c_str());
	SetTargetFPS(fps);

	m_sceneManager = new SceneManager();
}

Game::~Game()
{
	// Unloading the assets
	Assets::Instance().UnloadAssets();

	// Closing the window instance
	CloseWindow();
}

void Game::Init()
{
	// Loading the audio
	Assets::Instance().LoadAudio();

	// Scenes init
	m_sceneManager->Init();
}

void Game::Update()
{
	// Updating the scenes
	m_sceneManager->Update();
}

void Game::Render()
{
	// Rendering stuff here
	BeginDrawing();
	ClearBackground(BLUE);

	// Rendering the scenes
	m_sceneManager->Render();

	DrawFPS(10, 10);
	EndDrawing();
}

void Game::Run()
{
	// Initializes the game
	Init();

	// Main game loop
	while (!WindowShouldClose() && g_isWindowExit)
	{
		// Handals the logic 
		Update();

		// Handals the visuals
		Render();
	}
}
