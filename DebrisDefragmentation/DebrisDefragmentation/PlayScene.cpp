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
	// �̰� �Ҵ��ϴ��� ������. �׽�Ʈ ������ ���� ��
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
	// ���� wŰ�� ���ȴ��� Ȯ���Ѵ�
	// �������� ĳ���� ���ӵ� �����϶�� ��Ŵ
	// sŰ�� ���ȴٸ� ����
	if ( KEY_DOWN == GetKeyState( *"w" ) )
	{
		m_pPlayer->SetAcceleration();
	}

	if ( KEY_DOWN == GetKeyState( *"s" ) )
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

	m_PrevMousePosition = currentMousePos;
}
