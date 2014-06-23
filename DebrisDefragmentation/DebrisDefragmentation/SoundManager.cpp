#include "stdafx.h"
#include "SoundManager.h"

std::shared_ptr<SoundManager> GSoundManager = nullptr;

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::Init()
{
	m_SoundSystem = new SoundSystem();
	m_SoundSystem->InitSoundSystem();
	for ( auto iter : SoundTable )
	{
		m_SoundSystem->AddSound( iter.first, iter.second );
	}
}

void SoundManager::PlaySound( SOUND_LIST key )
{
	m_SoundSystem->PlaySoundW( key );
}

void SoundManager::StopAllSound()
{
	m_SoundSystem->StopAllSound();
}
