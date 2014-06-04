#include "stdafx.h"
#include "DDUIModule.h"
#include "DDScene.h"

DDUIModule::DDUIModule()
{
}

DDUIModule::~DDUIModule()
{
}

bool DDUIModule::Init( DDScene* scene )
{
	if ( GenerateUI() )
		RegisterUI( scene );
	else
		return false;

	return true;
}

void DDUIModule::RegisterUI( DDScene* scene )
{
	for ( std::map<ClientUITag, DDUI*>::const_iterator it = m_UIComponentList.begin(); it != m_UIComponentList.end(); ++it )
	{
		scene->AddChild( it->second );
	}
}

void DDUIModule::Update( float dt )
{
	// 등록된 UI들 update
	for ( std::map<ClientUITag, DDUI*>::const_iterator it = m_UIComponentList.begin(); it != m_UIComponentList.end(); ++it )
	{
		it->second->Update( dt );
	}
}

void DDUIModule::MakeUIComponent( ClientUITag tag )
{
	std::wstring filePath = UI_FILE_PATH;
	filePath.append( MAP_UI_FILENAME.at( tag ) );

	// 해당하는 List 인덱스에 UI를 만든다
	DDUI* newComponent = DDUI::Create();
	newComponent->InitUI( filePath );

	m_UIComponentList.insert( std::map<ClientUITag, DDUI*>::value_type( tag, newComponent ) );
}