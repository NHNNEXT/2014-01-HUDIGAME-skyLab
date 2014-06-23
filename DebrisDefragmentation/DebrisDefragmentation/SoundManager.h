#pragma once
#include "SoundSystem.h"
#include "GameOption.h"
#include "GameMacro.h"


class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	CREATE_FUNC( SoundManager );

	void Update() { if(!m_SoundSystem) m_SoundSystem->Update(); };
	void Init();
	void PlaySound( SOUND_LIST key );
	void StopAllSound();

private:
	SoundSystem* m_SoundSystem = nullptr;
};

extern std::shared_ptr<SoundManager> GSoundManager;