#include "stdafx.h"
#include "PlayScene.h"
#include "Debris.h"
#include "DDInputSystem.h"
#include "DDApplication.h"
#include "DDLight.h"
#include "Player.h"

PlayScene::PlayScene()
{
	m_SceneName = L"DefaultPlayScene";
}

PlayScene::PlayScene( std::wstring sceneName )
{
	m_SceneName = sceneName;
	Init();
}


PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{	
	// init objects
	m_pDirectonalLight = DDLight::Create();

	m_pPlayer = Player::Create();
	m_pPlayer->Init();
	
	AddChild( m_pDirectonalLight );
	AddChild( m_pPlayer );

	
	// test debris
	// 이거 할당하느라 느리다. 테스트 끝나면 지울 것
	Debris* tempDebris = nullptr;
	for ( unsigned int i = 0; i < 1000; ++i )
	{
		tempDebris = Debris::Create( L"debris.x" );
		tempDebris->SetPosition(
			static_cast<float>( ( rand( ) % 200 ) - 100 ) / 20, 
			static_cast<float>( ( rand( ) % 200 ) - 100 ) / 20,
			static_cast<float>( ( rand( ) % 200 ) - 100 ) / 20
			);
		tempDebris->SetScale( 0.01f, 0.01f, 0.01f );
		
		AddChild( tempDebris );
	}

	// 조심해! 하드 코딩
	// scene 함수에 화면 중심 좌표 구하는 함수 만들어서 거기로 가게 할 것
	if ( !SetCursorPos( 500, 500 ) )
	{
		// error!
		return;
	}



// 	RECT rect;
// 	GetWindowRect( DDApplication::GetInstance()->GetHWND(), &rect );
// 	ClipCursor( &rect );
}

// 조심해!!
// 로직 부분은 나중에 게임 매니저에 구현하는 걸로~!
void PlayScene::UpdateItSelf( float dTime )
{
	// 현재 w키가 눌렸는지 확인한다
	// 눌렸으면 캐릭터 가속도 세팅하라고 시킴
	// s키가 눌렸다면 정지
	
	if ( KEY_DOWN == GetKeyState( 0x57 ) )
	{
		m_pPlayer->SetAcceleration();
	}
	
	if ( KEY_DOWN == GetKeyState( 0x53 ) )
	{
		m_pPlayer->Stop( );
	}

	// 마우스 좌표 변화를 받아온다
	// 변화량을 기준으로 캐릭터한데 회전하라고 시킨다.	
	DDPoint currentMousePos = GetMousePosition( );
	m_pPlayer->RotateDicrection( 
		currentMousePos.GetX() - m_PrevMousePosition.GetX(), 
		currentMousePos.GetY() - m_PrevMousePosition.GetY()
		);
	
	HideMousePointer();

}

void PlayScene::HideMousePointer()
{
	// 마우스 커서 500, 500에 놓기
	POINT pt = { 500, 500 };
	::ClientToScreen( DDApplication::GetInstance()->GetHWND(), &pt );
	::SetCursorPos( pt.x, pt.y );

	// 이전 포지션 위치를 500, 500에 놓기
	m_PrevMousePosition = DDPoint( 500, 500 );

	// 커서 숨기기
	::ShowCursor( false );
}
