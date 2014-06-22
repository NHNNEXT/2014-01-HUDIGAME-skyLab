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
	m_SoundSystem->AddSound( 0, std::string(".\\Resources\\Sound\\BGM01.mp3") );
}

void SoundManager::PlaySound( int key )
{
	m_SoundSystem->PlaySoundW( key );
}

void SoundManager::StopAllSound()
{
	m_SoundSystem->StopAllSound();
}
