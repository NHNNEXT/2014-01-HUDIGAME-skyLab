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

	void Update() { m_SoundSystem->Update(); };
	void Init();
	void PlaySound( int key );

private:
	SoundSystem* m_SoundSystem;
};

extern std::shared_ptr<SoundManager> GSoundManager;