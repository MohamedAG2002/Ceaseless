#pragma once

#include <unordered_map>
#include <string>

#include <raylib.h>

// The singelton Assets class
class Assets
{
private:
	Assets();
	~Assets();

private:
	std::unordered_map<std::string, Sound> m_soundsMap;
	Music m_backgroundMusic;

public:
	// Gets the instatnce of the singelton
	static Assets& Instance()
	{
		static Assets instance;
		return instance;
	}

	// Deleting the constructor
	Assets(Assets const&) = delete;

	// Making it impossible to assign it to anything
	void operator=(Assets const&) = delete;

	// Gets the sound from the map by the specified name
	Sound GetSound(const std::string&& name) { return m_soundsMap[name]; }
	
	// Return the music
	Music GetMusic() { return m_backgroundMusic; }

	// Loads all of the audio(sounds and music alike)
	void LoadAudio();

	// Unloads all of the assets
	void UnloadAssets();
};