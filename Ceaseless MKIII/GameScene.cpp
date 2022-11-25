#include "Scene.h"
#include "Assets.h"
#include "Score.h"

// Const
const int MAX_SPIKES = 15;
const int MAX_COINS = MAX_SPIKES - 1;

GameScene::GameScene()
{
	// Playing the music
	PlayMusicStream(Assets::Instance().GetMusic());

	m_resumeButton = nullptr;

	// Pause variables init
	m_isPaused = false;
	m_pauseText = "PAUSED";

	Init();
}

GameScene::~GameScene()
{
	m_entities.clear();
	delete m_resumeButton;
}

void GameScene::Init()
{
	// Ceiling init
	StaticEntity* ceiling = new StaticEntity(Vector2{ 0.0f, 10.0f }, Vector2{ GetScreenWidth() / 1.0f, 140.0f }, WHITE);
	m_entities.push_back(ceiling);

	// Ground init
	StaticEntity* ground = new StaticEntity(Vector2{ 0.0f, GetScreenHeight() / 1.0f - 70.0f }, Vector2{ GetScreenWidth() / 1.0f, 140.0f }, WHITE);
	m_entities.push_back(ground);

	// Player init
	Player* player = new Player(Vector2{ 50.0f, m_entities.at(1)->GetPos().y - 40.0f }, Vector2{ 20.0f, 20.0f }, LIGHTGRAY);
	m_entities.push_back(player);

	// Spikes init
	for (int i = 0; i < MAX_SPIKES; i++)
	{
		Spike* spikes = new Spike(Vector2{ i * 130.0f + GetScreenWidth() / 1.0f, m_entities.at(1)->GetPos().y }, 20.0f, 3, WHITE);
		m_entities.push_back(spikes);
	}

	// Coin init
	for (int i = 0; i < MAX_COINS; i++)
	{
		Coin* coins = new Coin(Vector2{ i * 130.0f + GetScreenWidth() / 1.0f + 60.0f, m_entities.at(1)->GetPos().y - 12.0f }, 7.0f, YELLOW);
		m_entities.push_back(coins);
	}

	// Resume button init
	m_resumeButton = new ui::Button(Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2 + 50.0f }, BUTTON_SIZE, "RESUME", BUTTON_COLOR, TEXT_BUTTON_COLOR);
}

void GameScene::Update()
{
	// Entities update
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		// Deleting those who are not worthy(active)
		if (!(*it)->IsActive() && (*it)->GetTag() != "Player") it = m_entities.erase(it);
		// Updating otherwise
		else (*it)->Update();

		// Pausing movements when...well, paused
		if ((*it)->GetTag() == "Player")
			dynamic_cast<Player*>((*it))->SetMoving(!m_isPaused);
		else if((*it)->GetTag() == "Spike")
			dynamic_cast<Spike*>((*it))->SetMoving(!m_isPaused);
		else if((*it)->GetTag() == "Coin")
			dynamic_cast<Coin*>((*it))->SetMoving(!m_isPaused);
	}

	// Button update
	m_resumeButton->Update();

	// Once the vector is at a specified size, new spikes and coins will spawn
	if (m_entities.size() < 14)
	{
		// Respawn some spikes
		for (int i = 0; i < MAX_SPIKES; i++)
		{
			Spike* spikes = new Spike(Vector2{ i * 130.0f + GetScreenWidth() / 1.0f, m_entities.at(1)->GetPos().y }, 20.0f, 3, WHITE);
			m_entities.push_back(spikes);
		}

		// Respawn some coins
		for (int i = 0; i < MAX_COINS; i++)
		{
			Coin* coins = new Coin(Vector2{ i * 130.0f + GetScreenWidth() / 1.0f + 60.0f, m_entities.at(1)->GetPos().y - 12.0f }, 7.0f, YELLOW);
			m_entities.push_back(coins);
		}
	}

	// Handaling the collisions of the player
	Player* player = dynamic_cast<Player*>(m_entities.at(2));
	player->CollisionUpdate(m_entities);

	// Going to Over screen when the player perishes
	if (!player->IsActive())
	{
		g_currentState = OVER;
		g_isSceneChanged = true;
	}

	// Pause handaling
	if (IsKeyPressed(KEY_P)) m_isPaused = true;
	else if (m_resumeButton->OnButtonClick()) m_isPaused = false;

	// Music handaling
	UpdateMusicStream(Assets::Instance().GetMusic());
	
	if (m_isPaused) PauseMusicStream(Assets::Instance().GetMusic());
	else ResumeMusicStream(Assets::Instance().GetMusic());

	// Score handaling
	score.Update();
	score.SetScore(player->GetCollectedItems());
	m_scoreText = std::to_string(score.GetScore());
}

void GameScene::Render()
{
	// Entities render
	for (auto& entity : m_entities)
		entity->Render();

	// UI render
	int scoreTextWidth = MeasureText(m_scoreText.c_str(), 20);
	DrawText(m_scoreText.c_str(), GetScreenWidth() / 2 - scoreTextWidth / 2, 20, 20, BLACK);

	// Pause screen render	
	if (m_isPaused) PauseMenu();
}

void GameScene::PauseMenu()
{
	// Pause title
	int pauseTextWidth = MeasureText(m_pauseText.c_str(), 30);
	DrawText(m_pauseText.c_str(), GetScreenWidth() / 2 - pauseTextWidth / 2, GetScreenHeight() / 2, 30, BLACK);

	// Resume button render
	m_resumeButton->Render();
}