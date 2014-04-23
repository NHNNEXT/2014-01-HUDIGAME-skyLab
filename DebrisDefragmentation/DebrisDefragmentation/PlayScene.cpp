﻿#include "stdafx.h"
#include "PlayScene.h"
#include "Debris.h"
#include "DDInputSystem.h"
#include "DDApplication.h"
#include "DDLight.h"
#include "Player.h"
#include "NetworkManager.h"
#include "FuelUI.h"
#include "OxygenUI.h"
#include "PlayerManager.h"

PlayScene::PlayScene()
{
	m_SceneName = L"DefaultPlayScene";
}

PlayScene::PlayScene( std::wstring sceneName )
{
	m_SceneName = sceneName;
}

PlayScene::~PlayScene()
{
	delete GNetworkManager;
}

void PlayScene::Init()
{	
	// init objects
	m_pDirectonalLight = DDLight::Create();
	
// 	unsigned int cp = GGameLogic->GetCurrentPlayers();
// 	for ( unsigned int i = 0; i < cp; ++i )
// 	{
// 		AddChild( GGameLogic->GetPlayer(i) );
// 	}	
	AddChild( m_pDirectonalLight );
	
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

	GNetworkManager = new NetworkManager;
	GNetworkManager->Init();
	GNetworkManager->Connect();

// 	RECT rect;
// 	GetWindowRect( DDApplication::GetInstance()->GetHWND(), &rect );
// 	ClipCursor( &rect );

	// UI를 추가합니다. 근데 함수 이름이 너무 짧아서 알아보기 힘드네요. 좋은 이름 추천받습니다
	AddUI();
}

// 조심해!!
// 로직 부분은 나중에 게임 매니저에 구현하는 걸로~!
// 4. 23. UI 업데이트 하는 부분을 추가했습니다. 문진상
void PlayScene::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );

	// 현재 w키가 눌렸는지 확인한다
	// 눌렸으면 캐릭터 가속도 세팅하라고 시킴
	// s키가 눌렸다면 정지	
	if ( KEY_DOWN == GetKeyState( 0x57 ) )
	{
		// m_pPlayer->SetAcceleration();
		// 서버로 날리자
		GNetworkManager->SendAcceleration();
	}
	
	if ( KEY_DOWN == GetKeyState( 0x53 ) )
	{
		// m_pPlayer->Stop( );
		// 서버로 날려야지
		GNetworkManager->SendStop();
	}
	// 문교수 커피가 든 컵을 들고 오다가 커피가 손에 닿자...
	// 문교수 : 보강 간섭이 일어나지 않게 엇박자로 걸었어야 되는데...
	// ㅋㅋㅋㅋ 카멕님이 적으셨습니까

	// 마우스 좌표 변화를 받아온다
	// 변화량을 기준으로 캐릭터한데 회전하라고 시킨다.	
	DDPoint currentMousePos = GetMousePosition( );
	// m_pPlayer->RotateDicrection( 
	//	currentMousePos.GetX() - m_PrevMousePosition.GetX(), 
	//	currentMousePos.GetY() - m_PrevMousePosition.GetY()
	//	);
	
	// 이것도 서버로 보내야지
	GNetworkManager->SendRotateDirection(		
		currentMousePos.GetY() - m_PrevMousePosition.GetY(),
		currentMousePos.GetX() - m_PrevMousePosition.GetX()
		);

	MousePointer(false, currentMousePos);

	UpdateUI();
}

// Mouse Pointer 가릴지 살려둘지 결정
// true 시키면 커서가 계속 가운데로 이동함
// 04.21 김성환
void PlayScene::MousePointer( bool mousePointer, DDPoint currentMousePos )
{
	if ( mousePointer )
	{
		// 마우스 커서 500, 500에 놓기
		/// config.h
		POINT pt = { 500, 500 };
		::ClientToScreen( DDApplication::GetInstance()->GetHWND(), &pt );
		::SetCursorPos( pt.x, pt.y );

		// 이전 포지션 위치를 500, 500에 놓기
		m_PrevMousePosition = DDPoint( 500, 500 );

		// 커서 숨기기
		::ShowCursor( false );
	}
	else
	{
		m_PrevMousePosition = currentMousePos;
	}
}

void PlayScene::AddUI()
{
	// Add UI
	FuelUI* pFuelUI = new FuelUI();
	OxygenUI* pOxygenUI = new OxygenUI();

	pFuelUI->init();
	pOxygenUI->init();

	m_UICollection.push_back( pFuelUI );
	m_UICollection.push_back( pOxygenUI );
}

void PlayScene::UpdateUI()
{
	// 조심해!! UI가 늘어날 경우 좋은 코드가 아닙니다.
	// 되는지 확인하는 용도입니다.
	// >>> 되긴 되네요. 그런데 스케일을 바꾸면 좌표도 바뀌어서 위치를 재조정해야 함 ㅡㅡ;;
	// 좀 더 좋은 방법을 찾아봐야 할 듯...
	
	int myId = GNetworkManager->GetMyPlayerId();
	
	// 초기화 덜 됨
	if ( myId >= g_PlayerManager->GetCurrentPlayers() )
	{
		return;
	}

	int currentOxygen = g_PlayerManager->GetOxygen( myId );
	int currentFuel = g_PlayerManager->GetFuel( myId );

	// 현재는 front가 pFuelUI
	m_UICollection.front()->SetTransform(  currentFuel / 1000.0f, 1, 1 );
	m_UICollection.back()->SetTransform( currentOxygen / 1000.0f, 1, 1 );
}
