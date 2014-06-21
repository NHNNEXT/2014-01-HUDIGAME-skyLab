#pragma once
#include <unordered_map>
#include "..\external\fmod\inc\fmod.hpp"

#pragma comment (lib, "fmodex_vc.lib")

using namespace FMOD;

class SoundSystem
{
public:
	SoundSystem();
	~SoundSystem();

	void InitSoundSystem();
	void AddSound( int key, std::string fileName );
	void PlaySound( int key );
	void Update();

private:
	System* m_pSystem;
	std::unordered_map<int, Sound*> m_pSoundList;
	Channel* m_pChannel;
};

