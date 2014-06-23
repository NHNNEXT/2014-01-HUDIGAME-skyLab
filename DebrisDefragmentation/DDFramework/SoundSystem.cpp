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

	m_pSystem->init( 64, FMOD_INIT_NORMAL, 0 );
}

// key에는 enum 캐스팅해서 넣어주십쇼
void SoundSystem::AddSound( int key, std::string fileName )
{
	Sound* sound;

	m_pSystem->createSound( fileName.c_str(), FMOD_HARDWARE, 0, &sound );
	m_pSoundList.insert( std::make_pair(key, sound) );

	Channel* channel;
	m_pSystem->getChannel( key, &channel );
	m_pChannelList.insert( std::make_pair( key, channel ) );
}

void SoundSystem::PlaySound( int key )
{
	std::unordered_map<int, Sound*>::iterator soundFinder = m_pSoundList.find( key );
	std::unordered_map<int, Channel*>::iterator channelFinder = m_pChannelList.find( key );
	if ( soundFinder != m_pSoundList.end() )
	{
		m_pSystem->playSound( FMOD_CHANNEL_FREE, soundFinder->second, 0, &(channelFinder->second) );
	}
}

void SoundSystem::StopAllSound()
{
	for ( auto iter : m_pChannelList )
	{
		iter.second->stop();
	}
}

void SoundSystem::Update()
{
	m_pSystem->update();
}

