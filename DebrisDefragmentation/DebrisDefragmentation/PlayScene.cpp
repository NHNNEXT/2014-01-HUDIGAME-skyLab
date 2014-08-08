#include "stdafx.h"
#include "PlayScene.h"
#include "DebrisModel.h"
#include "DDInputSystem.h"
#include "DDApplication.h"
#include "DDLight.h"
#include "DDUI.h"
#include "Player.h"
#include "NetworkManager.h"
#include "PlayerManager.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "SkyBox.h"
#include "GameData.h"
#include "InfoPrinter.h"
#include "EnvironmentManager.h"
#include "DebugData.h"
#include "DDBillboardEffect.h"
#include "ParticleSystem.h"
#include "SoundManager.h"


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
	delete GDebugData;
	delete GNetworkManager;
}


void PlayScene::InitModelPool()
{
	m_ModelPool.InitModel( ModelType::DEBRIS, L"debris.x" );
	m_ModelPool.InitModel( ModelType::SKYBOX, L"skybox.x" );
	m_ModelPool.InitModel( ModelType::EARTH, L"earth.x" );
	m_ModelPool.InitModel( ModelType::PLAYER_MODEL, L"spaceMan.x" );
	m_ModelPool.InitModel( ModelType::PLAYER_MODEL_ANIMATION, L"x_file\\character_all.x", true );
}


void PlayScene::InitResourceDebris()
{
	srand( GObjectManager->GetRandomSeed() );
	for ( int i = 0; i < RESOURCE_DEBRIS_NUMBER; ++i )
	{
		DebrisModel* newResouceDebris = DebrisModel::Create();
		newResouceDebris->SetModelMesh( m_ModelPool.GetModel( ModelType::DEBRIS ) );
		newResouceDebris->GetTransform().SetPosition(
			( static_cast<float>( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) ),
			( static_cast<float>( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) ),
			( static_cast<float>( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) )
			);
		newResouceDebris->GetTransform().SetScale( RESOURCE_DEBRIS_SCALE );
		AddChild( newResouceDebris );
		GObjectManager->AddResourceDebris( i, newResouceDebris );
	}
}

void PlayScene::Init()
{	
	if ( !g_GameData->Init() )
	{
		// 무조건 ok 해야 하는 과정
		// 에러 발생시 프로그램 종료
		return;
	}

	GDebugData = new DebugData;

	// debugger 초기화
	GInfoPrinter = InfoPrinter::Create();
	GInfoPrinter->init();
	AddChild( GInfoPrinter );

	// model pool 초기화
	InitModelPool();
	
	// init objects
	m_pDirectonalLight = DDLight::Create();
	
	AddChild( m_pDirectonalLight );
	GEnvironmentManager->AddLight( ClientLightTag::DIRECTIONAL_MAIN, m_pDirectonalLight );
	
	// test skybox
	//SkyBox* sb = SkyBox::Create( L"skybox.x" );
	SkyBox* sb = SkyBox::Create();
	sb->SetModelMesh( m_ModelPool.GetModel( ModelType::SKYBOX ) );
	AddChild( sb );

	// earth :: 바닥에 지구를 깐다!
	//DDModel* earth = DDModel::Create( L"earth.x" );
	DDModel* earth = DDModel::Create();
	earth->SetModelMesh( m_ModelPool.GetModel( ModelType::EARTH ) );
	earth->GetTransform().SetPosition( EARTH_POSITION );
	AddChild( earth );

// 	DDBillboardEffect* bill = DDBillboardEffect::Create();
// 	bill->Init();
// 	bill->GetTransform().SetPosition( 90.0f, .0f, .0f );
// 	AddChild( bill );
		
	GEnvironmentManager->InitParticleEffects();
	//GEnvironmentManager->SetParticleEffect( Exp );
	//AddChild( Exp, 10 );

	// test debris
	// 이거 할당하느라 느리다. 테스트 끝나면 지울 것
	
	GObjectManager = new ObjectManager;

	unsigned int debrisCount = g_GameData->GetDebrisNumber();
	/*
	for ( unsigned int i = 0; i < debrisCount; ++i )
	{
		DDModel* newBackgroundDebris = DDModel::Create();
		newBackgroundDebris->SetModelMesh( m_ModelPool.GetModel( ModelType::DEBRIS ) );
		newBackgroundDebris->GetTransform().SetPosition(
			( static_cast<float>( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) ),
			( static_cast<float>( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) ),
			( static_cast<float>( rand() % DEBRIS_SPREAD_RANGE ) - ( DEBRIS_SPREAD_RANGE >> 1 ) )
			);
		newBackgroundDebris->GetTransform().SetScale( BACKGROUND_DEBRIS_SCALE );

		AddChild( newBackgroundDebris );
	}
	*/
	
	// UI
	GUIManager->Init();
	GUIManager->SetCurrentScene( this );
	GUIManager->GeneratePlaySceneUI();

	GNetworkManager = new NetworkManager;
	GNetworkManager->Init();
	GNetworkManager->Connect();

	// Sound
	GSoundManager = SoundManager::Create();
	GSoundManager->Init();
	GSoundManager->PlaySound( BGM_PLAY );

	PostMessage( DDApplication::GetInstance()->GetHWND(), SL_PLAYSCENE_LOADING_COMPLETE, NULL, NULL);
	
	// 마우스 커서 초기화
	MousePointer( false, { 0, 0 } );
}

void PlayScene::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );
	
	// player가 로그인해있지 않으면 루프는 패스.
	if ( !GNetworkManager->IsPlayerLogon() )
	{
		return;
	}

	// 캐릭터가 죽어있으면.. 아래는 실행이 안되고 종료..
	// 캐릭터 컴포넌트까지 접근이 좀 구구절절하다...ㅠㅠ	
	if ( !GPlayerManager->GetPlayer( GNetworkManager->GetMyPlayerId() )->GetClassComponent()->IsAlive() )
	{
		// space 누르면 respawn request보낸다.
		if ( KEY_DOWN == GetKeyState( VK_SPACE ) )
		{
			// 조심해!!
			// 일단은 striker만 보내보자..
			// 뭘 보낼지 선택하는 부분은 나중에 추가할 것!
			GNetworkManager->SendRespawnRequest( GNetworkManager->GetMyClass() );
		}

		// player 조정이 playscene에 있으므로 여기서 return 함.
		// 동시에 player의 updatable을 꺼줘야 player가 계속 sendDeadrequest하는 것을 막을 수 있음..
		return;
	}


	// 키 고유 넘버는 아래를 참조하자 
	// http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	// 현재 w키가 눌렸는지 확인한다
	// 눌렸으면 캐릭터 가속도 세팅하라고 시킴
	// s키가 눌렸다면 정지	
	if ( KEY_DOWN == GetKeyState( VK_W ) )
	{
		// w : 현재 몸체가 바라보는 방향으로 가속
		GNetworkManager->SendAcceleration();
	}
	
	if ( KEY_DOWN == GetKeyState( VK_S ) )
	{
		// s : 정지!
		GNetworkManager->SendStop();
	}

	if ( KEY_DOWN == GetKeyState( VK_1 ) )
	{
		// 1 : 밀기 스킬 시전!
		GNetworkManager->SendUsingSkill( ClassSkill::PUSH );
	}

	if ( KEY_DOWN == GetKeyState( VK_2 ) )
	{
		// 2 : 채취 스킬 시전!
		GNetworkManager->SendUsingSkill( ClassSkill::GATHER );
	}

	if ( KEY_DOWN == GetKeyState( VK_SPACE ) )
	{
		GNetworkManager->SendTurnBody();
	}

	if ( KEY_DOWN == GetKeyState( VK_F12 ) )
	{
		GDebugData->mDisplayDebugInfoFlag = GDebugData->mDisplayDebugInfoFlag ? false : true;
	}

	// 문교수 커피가 든 컵을 들고 오다가 커피가 손에 닿자...
	// 문교수 : 보강 간섭이 일어나지 않게 엇박자로 걸었어야 되는데...라고 말씀하셨다.
	// ㅋㅋㅋㅋ 카멕님이 적으셨습니까

	// 마우스 좌표 변화를 받아온다
	// 변화량을 기준으로 캐릭터한데 회전하라고 시킨다.		
	// 고개 돌리기는 서버로 보낼 필요 없이 클라이언트에서만 적용
	
	DDPoint currentMousePos = GetMousePosition();
	GPlayerManager->GetPlayer( GNetworkManager->GetMyPlayerId() )->LookAt(
		currentMousePos.GetY() - m_PrevMousePosition.GetY(),
		currentMousePos.GetX() - m_PrevMousePosition.GetX(),
		0
		);

	MousePointer( MOUSE_POINTER_ON, currentMousePos );

	GUIManager->UpdateUI( dTime );

	// Sound System Update
	GSoundManager->Update();
}

// Mouse Pointer 가릴지 살려둘지 결정
// true 시키면 커서가 계속 가운데로 이동함
void PlayScene::MousePointer( bool mousePointer, DDPoint currentMousePos )
{
	if ( !mousePointer )
	{
		// 마우스 커서를 게임화면 중앙에 놓기
		/// config.h
		POINT pt = { DDApplication::GetInstance()->GetScreenWidth() / 2, DDApplication::GetInstance()->GetScreenHeight() / 2 };
		::ClientToScreen( DDApplication::GetInstance()->GetHWND(), &pt );
		::SetCursorPos( pt.x, pt.y );

		// 이전 커서 위치를 게임 화면 중앙으로 설정
		m_PrevMousePosition = DDPoint( static_cast<float>( DDApplication::GetInstance()->GetScreenWidth() / 2 ), static_cast<float>( DDApplication::GetInstance()->GetScreenHeight() / 2) );

		// 커서 숨기기
		::ShowCursor( false );
	}
	else
	{
		m_PrevMousePosition = currentMousePos;
	}
}