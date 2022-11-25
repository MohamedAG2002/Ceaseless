#include "Scene.h"
#include "Assets.h"

// Extern variables init
SceneStates g_currentState;
bool g_isSceneChanged;
bool g_isWindowExit;

SceneManager::SceneManager()
{
	g_currentState = MENU;

	g_isSceneChanged = true;
	g_isWindowExit = true;

	m_currentScene = nullptr;
}

SceneManager::~SceneManager()
{
	m_scenes.clear();
	delete m_currentScene;
}

void SceneManager::Init()
{
	// Adding scenes to the map
	m_scenes.push_back(new MainMenuScene());
	m_scenes.push_back(new GameScene());
	m_scenes.push_back(new GameOverScene());
}

void SceneManager::Update()
{	
	// Only check for the state when a change of scenes was detected
	if (g_isSceneChanged)
	{
		// Determining the current scene depending on the current state
		switch (g_currentState)
		{
		case MENU: 
			m_currentScene = new MainMenuScene();
			StopMusicStream(Assets::Instance().GetMusic());
			break;
		case GAME: m_currentScene = new GameScene();
			break;
		case OVER: 
			m_currentScene =  new GameOverScene();
			StopMusicStream(Assets::Instance().GetMusic());
			break;
		}

		// Changing it back to false to not enter unless another change of scenes is detected
		g_isSceneChanged = false;
	}

	// Updating only the current scene
	m_currentScene->Update();
}

void SceneManager::Render()
{
	// Rendering only the current scene
	m_currentScene->Render();
}