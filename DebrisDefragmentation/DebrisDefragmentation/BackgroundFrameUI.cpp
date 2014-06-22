#include "stdafx.h"
#include "BackgroundFrameUI.h"
#include "PlayerManager.h"
#include "ObjectManager.h"

BackgroundFrameUI::BackgroundFrameUI()
{
}


BackgroundFrameUI::~BackgroundFrameUI()
{
}

bool BackgroundFrameUI::GenerateUI()
{
	// 하나씩 만들어서 m_UIComponentList에 추가한다.
	MakeUIComponent( ClientUITag::UI_TAG_FRAME );
	m_UIComponentList[ClientUITag::UI_TAG_FRAME]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_FRAME]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );

	MakeUIComponent( ClientUITag::UI_TAG_TEAM_RED );
	m_UIComponentList[ClientUITag::UI_TAG_TEAM_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_TEAM_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_TEAM_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_TEAM_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_TEAM_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_TEAM_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_TEAM_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_SK_ENGINEER );
	m_UIComponentList[ClientUITag::UI_TAG_SK_ENGINEER]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_SK_ENGINEER]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_SK_ENGINEER]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_SK_PROTECTOR );
	m_UIComponentList[ClientUITag::UI_TAG_SK_PROTECTOR]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_SK_PROTECTOR]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_SK_PROTECTOR]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_SK_STRIKER );
	m_UIComponentList[ClientUITag::UI_TAG_SK_STRIKER]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_SK_STRIKER]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_SK_STRIKER]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_DISASTER );
	m_UIComponentList[ClientUITag::UI_TAG_DISASTER]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_DISASTER]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_SKELETON_POSITION_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_DISASTER]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_ISS_POSITION );
	m_UIComponentList[ClientUITag::UI_TAG_ISS_POSITION]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_ISS_POSITION]->GetTransform().SetPosition( UI_ISS_NAV_DEFAULT_POSITION_X, UI_ISS_NAV_DEFAULT_POSITION_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_ISS_POSITION]->SetVisible( true );

	return true;
}

void BackgroundFrameUI::Update( float dt )
{
	if ( !GPlayerManager->GetMyPlayer() )
		return;

	TeamColor currentPlayerTeam = GPlayerManager->GetMyPlayer()->GetTeam();

	if ( m_DisplayTeam != currentPlayerTeam )
	{
		m_DisplayTeam = currentPlayerTeam;

		switch ( m_DisplayTeam )
		{
		case TeamColor::RED:
			m_UIComponentList[ClientUITag::UI_TAG_TEAM_BLUE]->SetVisible( false );
			m_UIComponentList[ClientUITag::UI_TAG_TEAM_RED]->SetVisible( true );
			break;
		case TeamColor::BLUE:
			m_UIComponentList[ClientUITag::UI_TAG_TEAM_BLUE]->SetVisible( true );
			m_UIComponentList[ClientUITag::UI_TAG_TEAM_RED]->SetVisible( false );
			break;
		default:
			break;
		}
	}

	CharacterClass currentPlayerClass = GPlayerManager->GetMyPlayer()->GetClassComponent()->GetCharacterClassName();

	if ( m_DisplayClass != currentPlayerClass )
	{
		m_DisplayClass = currentPlayerClass;

		switch ( m_DisplayClass )
		{
		case CharacterClass::ENGINEER:
			m_UIComponentList[ClientUITag::UI_TAG_SK_ENGINEER]->SetVisible( true );
			m_UIComponentList[ClientUITag::UI_TAG_SK_PROTECTOR]->SetVisible( false );
			m_UIComponentList[ClientUITag::UI_TAG_SK_STRIKER]->SetVisible( false );
			break;
		case CharacterClass::PROTECTOR:
			m_UIComponentList[ClientUITag::UI_TAG_SK_ENGINEER]->SetVisible( false );
			m_UIComponentList[ClientUITag::UI_TAG_SK_PROTECTOR]->SetVisible( true );
			m_UIComponentList[ClientUITag::UI_TAG_SK_STRIKER]->SetVisible( false );
			break;
		case CharacterClass::STRIKER:
			m_UIComponentList[ClientUITag::UI_TAG_SK_ENGINEER]->SetVisible( false );
			m_UIComponentList[ClientUITag::UI_TAG_SK_PROTECTOR]->SetVisible( false );
			m_UIComponentList[ClientUITag::UI_TAG_SK_STRIKER]->SetVisible( true );
			break;
		default:
			break;
		}
	}

	// disaster info 가져와서 표시

	// iss 위치 표시
	m_IssPosition = GObjectManager->GetObjectISSPosition().z;
	float positionRatio = m_IssPosition / WINNING_DISTANCE;

	m_UIComponentList[ClientUITag::UI_TAG_ISS_POSITION]->GetTransform().SetPosition( UI_ISS_NAV_DEFAULT_POSITION_X + ( positionRatio * UI_ISS_NAV_DEFAULT_RANGE ), UI_ISS_NAV_DEFAULT_POSITION_Y, 0.0f );
}