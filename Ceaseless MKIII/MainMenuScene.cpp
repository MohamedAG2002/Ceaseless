#include "Scene.h"

MainMenuScene::MainMenuScene()
{
	Init();
}

MainMenuScene::~MainMenuScene()
{
	m_buttons.clear();
}

void MainMenuScene::Init()
{
	// Title init
	m_title = "CEASELESS";

	// Play button init
	ui::Button* playButton = new ui::Button(Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f - 50.0f }, BUTTON_SIZE, "PLAY", BUTTON_COLOR, TEXT_BUTTON_COLOR);
	m_buttons.push_back(playButton);

	// Exit button init
	ui::Button* exitButton = new ui::Button(Vector2{ playButton->GetPos().x, playButton->GetPos().y + 50.0f }, BUTTON_SIZE, "EXIT", BUTTON_COLOR, TEXT_BUTTON_COLOR);
	m_buttons.push_back(exitButton);
}

void MainMenuScene::Update()
{
	// Updating the buttons
	for (auto& button : m_buttons)
		button->Update();

	// Menu to Game
	if (m_buttons.at(0)->OnButtonClick())
	{
		g_currentState = GAME;
		g_isSceneChanged = true;
	}
	
	// Exit the game
	if (m_buttons.at(1)->OnButtonClick()) g_isWindowExit = false;
}

void MainMenuScene::Render()
{
	// Rendering the buttons
	for (auto& button : m_buttons)
		button->Render();

	// Rendering the UI
	DrawText(m_title.c_str(), GetScreenWidth() / 2 - MeasureText(m_title.c_str(), 50) / 2, 10, 50, WHITE);
}