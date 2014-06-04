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
	MakeUIComponent( ClientUITag::UI_FRAME_TAG );

	m_UIComponentList[ClientUITag::UI_FRAME_TAG]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_FRAME_TAG]->GetTransform().SetPosition( UI_FRAME_POSITION_X, UI_FRAME_POSITION_Y, 0.0f );

	return true;
}

void BackgroundFrameUI::Update( float dt )
{
	UNREFERENCED_PARAMETER( dt );
}