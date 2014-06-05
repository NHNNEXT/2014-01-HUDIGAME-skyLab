#include "stdafx.h"
#include "BackgroundFrameUI.h"

BackgroundFrameUI::BackgroundFrameUI()
{
}


BackgroundFrameUI::~BackgroundFrameUI()
{
}

bool BackgroundFrameUI::GenerateUI()
{
	// 하나씩 만들어서 m_UIComponentList에 추가한다.
	// MakeUIComponent( ClientUITag::UI_FRAME_TAG );

	// m_UIComponentList[ClientUITag::UI_FRAME_TAG]->GetTransform().SetScale( 0.6f );
	// m_UIComponentList[ClientUITag::UI_FRAME_TAG]->GetTransform().SetPosition( UI_FRAME_POSITION_X, UI_FRAME_POSITION_Y, 0.0f );

	MakeUIComponent( ClientUITag::UI_SKELETON_FRAME );
	m_UIComponentList[ClientUITag::UI_SKELETON_FRAME]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_SKELETON_FRAME]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );

	MakeUIComponent( ClientUITag::UI_SKELETON_CHARACTER_INFO );
	m_UIComponentList[ClientUITag::UI_SKELETON_CHARACTER_INFO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_SKELETON_CHARACTER_INFO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );

	MakeUIComponent( ClientUITag::UI_SKELETON_ISS );
	m_UIComponentList[ClientUITag::UI_SKELETON_ISS]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_SKELETON_ISS]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );

	// MakeUIComponent( ClientUITag::UI_SKELETON_DISASTER );
	// m_UIComponentList[ClientUITag::UI_SKELETON_DISASTER]->GetTransform().SetScale( 0.6f );
	// m_UIComponentList[ClientUITag::UI_SKELETON_DISASTER]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );

	MakeUIComponent( ClientUITag::UI_SKELETON_NAVIGATOR );
	m_UIComponentList[ClientUITag::UI_SKELETON_NAVIGATOR]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_SKELETON_NAVIGATOR]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );

	MakeUIComponent( ClientUITag::UI_SKELETON_TEAM );
	m_UIComponentList[ClientUITag::UI_SKELETON_TEAM]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_SKELETON_TEAM]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );

	return true;
}

void BackgroundFrameUI::Update( float dt )
{
	UNREFERENCED_PARAMETER( dt );
}