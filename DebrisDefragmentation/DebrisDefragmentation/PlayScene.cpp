#include "PlayScene.h"
#include "Debris.h"

PlayScene::PlayScene()
{
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
		tempDebris = Debris::Create( L"debris2.x" );
		tempDebris->SetPosition(
			static_cast<float>( ( rand( ) % 200 ) - 100 ) / 20, 
			static_cast<float>( ( rand( ) % 200 ) - 100 ) / 20,
			static_cast<float>( ( rand( ) % 200 ) - 100 ) / 20
			);
		//tempDebris->SetScale( 2.0f, 2.0f, 2.0f );
		
		AddChild( tempDebris );
	}
}

void PlayScene::Update( float dTime )
{	
	UpdateChildNodes( dTime );
	UpdateItSelf( dTime );
}

void PlayScene::UpdateItSelf( float dTime )
{
	// 현재 w키가 눌렸는지 확인한다
	// 눌렸으면 캐릭터 가속도 세팅하라고 시킴
	// s키가 눌렸다면 정지
	if ( KEY_DOWN == GetKeyState( *"w" ) )
	{
		m_pPlayer->SetAcceleration();
	}

	if ( KEY_DOWN == GetKeyState( *"s" ) )
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

	m_PrevMousePosition = currentMousePos;
}
