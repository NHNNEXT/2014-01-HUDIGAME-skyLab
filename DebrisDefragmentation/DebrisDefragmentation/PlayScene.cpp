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
	// �̰� �Ҵ��ϴ��� ������. �׽�Ʈ ������ ���� ��
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

	// ������! �ϵ� �ڵ�
	// scene �Լ��� ȭ�� �߽� ��ǥ ���ϴ� �Լ� ���� �ű�� ���� �� ��
	if ( !SetCursorPos( 500, 500 ) )
	{
		// error!
		return;
	}



// 	RECT rect;
// 	GetWindowRect( DDApplication::GetInstance()->GetHWND(), &rect );
// 	ClipCursor( &rect );
}

// ������!!
// ���� �κ��� ���߿� ���� �Ŵ����� �����ϴ� �ɷ�~!
void PlayScene::UpdateItSelf( float dTime )
{
	// ���� wŰ�� ���ȴ��� Ȯ���Ѵ�
	// �������� ĳ���� ���ӵ� �����϶�� ��Ŵ
	// sŰ�� ���ȴٸ� ����
	
	if ( KEY_DOWN == GetKeyState( 0x57 ) )
	{
		m_pPlayer->SetAcceleration();
	}
	
	if ( KEY_DOWN == GetKeyState( 0x53 ) )
	{
		m_pPlayer->Stop( );
	}

	// ���콺 ��ǥ ��ȭ�� �޾ƿ´�
	// ��ȭ���� �������� ĳ�����ѵ� ȸ���϶�� ��Ų��.	
	DDPoint currentMousePos = GetMousePosition( );
	m_pPlayer->RotateDicrection( 
		currentMousePos.GetX() - m_PrevMousePosition.GetX(), 
		currentMousePos.GetY() - m_PrevMousePosition.GetY()
		);
	
	HideMousePointer();

}

void PlayScene::HideMousePointer()
{
	// ���콺 Ŀ�� 500, 500�� ����
	POINT pt = { 500, 500 };
	::ClientToScreen( DDApplication::GetInstance()->GetHWND(), &pt );
	::SetCursorPos( pt.x, pt.y );

	// ���� ������ ��ġ�� 500, 500�� ����
	m_PrevMousePosition = DDPoint( 500, 500 );

	// Ŀ�� �����
	::ShowCursor( false );
}
