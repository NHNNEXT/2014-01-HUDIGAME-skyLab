#include "stdafx.h"
#include "BackgroundFrameUI.h"
#include "PlayerManager.h"
#include "ObjectManager.h"

BackgroundFrameUI::BackgroundFrameUI()
{
	m_IssModuleOwnerList.fill( TeamColor::NO_TEAM );
}


BackgroundFrameUI::~BackgroundFrameUI()
{
	m_pFont->Release();
	delete m_pRect;
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

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_0_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_0_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_0_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_1_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_1_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_1_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_2_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_2_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_2_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_3_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_3_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_3_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_4_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_4_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_4_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_5_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_5_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_5_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_6_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_6_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_6_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_7_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_7_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_7_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_8_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_8_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_8_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_RED]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_9_NO );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_NO]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_NO]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_NO]->SetVisible( true );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_9_BLUE );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_BLUE]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_BLUE]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_BLUE]->SetVisible( false );

	MakeUIComponent( ClientUITag::UI_TAG_MODULE_9_RED );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_RED]->GetTransform().SetScale( 0.6f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_RED]->GetTransform().SetPosition( UI_SKELETON_POSITION_X, UI_ISS_MODULE_STATE_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_RED]->SetVisible( false );

	// test param
	D3DXFONT_DESC fontParam;
	ZeroMemory( &fontParam, sizeof( fontParam ) );
	fontParam.Height = 10;
	fontParam.Width = 10;
	fontParam.Weight = 100;
	fontParam.Italic = false;
	fontParam.CharSet = false;
	wcscpy_s( fontParam.FaceName, L"Segoe UI Light" );

	m_pRect = new RECT();
	m_pRect->top = 0;
	m_pRect->bottom = 0;
	m_pRect->left = 0;
	m_pRect->right = 0;

	HRESULT hr = D3DXCreateFontIndirect(
		DDRenderer::GetInstance()->GetDevice(),
		&fontParam,
		&m_pFont
		);

	if ( !SUCCEEDED( hr ) )
	{
		assert( false );
	}

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

	// iss 소유자 표시
	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		TeamColor currentModuleOwner = GObjectManager->GetISS()->GetModuleOwner( i );
		if ( m_IssModuleOwnerList[i] != currentModuleOwner )
		{
			m_IssModuleOwnerList[i] = currentModuleOwner;
			ChangeModuleOwner( i, currentModuleOwner );
		}
	}

	// text
	// infoPrinter에서 표시
}

void BackgroundFrameUI::ChangeModuleOwner( int moduleIdx, TeamColor owner )
{
	DDUI* no = nullptr;
	DDUI* blue = nullptr;
	DDUI* red = nullptr;

	switch ( moduleIdx )
	{
	case 0:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_0_RED];
		break;
	case 1:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_1_RED];
		break;
	case 2:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_2_RED];
		break;
	case 3:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_3_RED];
		break;
	case 4:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_4_RED];
		break;
	case 5:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_5_RED];
		break;
	case 6:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_6_RED];
		break;
	case 7:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_7_RED];
		break;
	case 8:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_8_RED];
		break;
	case 9:
		no = m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_NO];
		blue = m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_BLUE];
		red = m_UIComponentList[ClientUITag::UI_TAG_MODULE_9_RED];
		break;
	default:
		break;
	}

	ChangeModuleDisplayState( no, blue, red, owner );
}

void BackgroundFrameUI::ChangeModuleDisplayState( DDUI* no, DDUI* blue, DDUI* red, TeamColor owner )
{
	if ( !no || !red || !blue )
		return;

	switch ( owner )
	{
	case TeamColor::NO_TEAM:
		no->SetVisible( true );
		blue->SetVisible( false );
		red->SetVisible( false );
		break;
	case TeamColor::BLUE:
		no->SetVisible( false );
		blue->SetVisible( true );
		red->SetVisible( false );
		break;
	case TeamColor::RED:
		no->SetVisible( false );
		blue->SetVisible( false );
		red->SetVisible( true );
		break;
	default:
		break;
	}
}