#include "Scene.h"
#include "Score.h"
#include "File.h"
#include "Assets.h"

GameOverScene::GameOverScene()
{
	m_retryButton = nullptr;

	Init();
}

GameOverScene::~GameOverScene()
{
	delete m_retryButton;
}

void GameOverScene::Init()
{
	// Title init
	m_title = "GAME OVER!";

	// Retry button init
	m_retryButton = new ui::Button(Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}, BUTTON_SIZE, "RETRY", BUTTON_COLOR, TEXT_BUTTON_COLOR);
}

void GameOverScene::Update()
{
	// Updating the button
	m_retryButton->Update();

	// Going to GAME once the retry button is pressed
	if (m_retryButton->OnButtonClick())
	{
		g_currentState = GAME;
		g_isSceneChanged = true;
	}

	// Setting the score text
	m_scoreText = "SCORE:" + std::to_string(score.GetScore());

	// Setting the high score text
	m_highScoreText = "HIGH SCORE:" + std::to_string(File::Instance().LoadData());
}

void GameOverScene::Render()
{
	// Rendering the button
	m_retryButton->Render();

	// Rendering the texts
	DrawText(m_title.c_str(), GetScreenWidth() / 2 - MeasureText(m_title.c_str(), 50) / 2, 10, 50, WHITE);
	DrawText(m_scoreText.c_str(), GetScreenWidth() / 2 - MeasureText(m_scoreText.c_str(), 30) / 2, 150, 30, BLACK);
	DrawText(m_highScoreText.c_str(), GetScreenWidth() / 2 - MeasureText(m_highScoreText.c_str(), 30) / 2, 200, 30, BLACK);
}
