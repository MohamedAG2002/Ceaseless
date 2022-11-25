#include "Assets.h"

Assets::Assets()
{
	m_backgroundMusic = {};
}

Assets::~Assets()
{}

void Assets::LoadAudio()
{
	InitAudioDevice();

	auto Load = [&](std::string&& name, std::string&& path)
	{
		m_soundsMap[name] = LoadSound(path.c_str());
	};

	// Load the music
	m_backgroundMusic = LoadMusicStream("assets/audio/background_music.ogg");

	// Load sounds
	Load("Click", "assets/audio/button_click.wav");
	Load("Death", "assets/audio/player_death.wav");
	Load("Pickup", "assets/audio/pickup_coin.wav");
}

void Assets::UnloadAssets()
{
	// Unloading the audio
	UnloadMusicStream(m_backgroundMusic);
	UnloadSound(m_soundsMap.at("Click"));
	UnloadSound(m_soundsMap.at("Death"));
	UnloadSound(m_soundsMap.at("Pickup"));

	// Closing the audio device instance
	CloseAudioDevice();
}