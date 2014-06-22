#include "stdafx.h"
#include "SoundSystem.h"


SoundSystem::SoundSystem()
{
}


SoundSystem::~SoundSystem()
{
	m_pSystem->release();
	m_pSystem->close();
}

void SoundSystem::InitSoundSystem()
{
	System_Create( &m_pSystem );

	m_pSystem->init( 5, FMOD_INIT_NORMAL, 0 );
}

void SoundSystem::AddSound( int key, std::string fileName )
{
	Sound* sound;

	m_pSystem->createSound( fileName.c_str(), FMOD_HARDWARE, 0, &sound );
	m_pSoundList.insert( std::make_pair(key, sound) );
}

void SoundSystem::PlaySound( int key )
{
	std::unordered_map<int, Sound*>::iterator finder = m_pSoundList.find( key );

	if ( finder != m_pSoundList.end() )
	{
		m_pSystem->playSound( FMOD_CHANNEL_FREE, finder->second, 0, &m_pBGMChannel );
	}
}

void SoundSystem::StopAllSound()
{
	m_pBGMChannel->stop();
}

void SoundSystem::Update()
{
	m_pSystem->update();
}

