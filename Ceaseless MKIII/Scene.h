#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "Ui.h"
#include "Entity.h"

// Consts 
const Vector2 BUTTON_SIZE = { 100.0f, 30.0f };
const Color BUTTON_COLOR = WHITE;
const Color TEXT_BUTTON_COLOR = BLACK;

enum SceneStates
{
	MENU = 0,
	GAME,
	OVER
};

// Global extern variables(or as I like to call them: Events)
extern SceneStates g_currentState;
extern bool g_isSceneChanged;
extern bool g_isWindowExit;

// Scene virtual class
class Scene
{
public:
	virtual void Init() {}
	virtual void Update() {}
	virtual void Render() {}
};


// Main menu scene
class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	~MainMenuScene();

public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	std::string m_title;
	std::vector<ui::Button*> m_buttons;
};


// Game scene
class GameScene : public Scene
{
public: 
	GameScene();
	~GameScene();

public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	std::string m_scoreText, m_pauseText;
	std::vector<Entity*> m_entities;
	bool m_isPaused;
	ui::Button* m_resumeButton;

private:
	void PauseMenu();
};


// Game over scene
class GameOverScene : public Scene
{
public:
	GameOverScene();
	~GameOverScene();

public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	std::string m_title, m_scoreText, m_highScoreText;
	ui::Button* m_retryButton;
};


// Scene manager class
class SceneManager : public Scene
{
public:
	SceneManager();
	~SceneManager();

private:
	std::vector<Scene*> m_scenes;
	Scene* m_currentScene;

public:
	void Init() override;
	void Update() override;
	void Render() override;
};