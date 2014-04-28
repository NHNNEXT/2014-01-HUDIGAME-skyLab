#include "stdafx.h"
#include "PlayScene.h"
#include "Debris.h"
#include "DDInputSystem.h"
#include "DDApplication.h"
#include "DDLight.h"
#include "DDUI.h"
#include "Player.h"
#include "NetworkManager.h"
#include "FuelUI.h"
#include "OxygenUI.h"
#include "PlayerManager.h"
#include "UIManager.h"
#include "ObjectManager.h"
#include "SkyBox.h"

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
	delete GObjectManager;
	delete GNetworkManager;
}

void PlayScene::Init()
{	
	// init JSON
	FILE* file;
	// 이 파일은 실행폴더에 있어야 한다! VS에서 실행할 때는 클래스 파일과 같이 있어야 함
	const char* filePath = "Config.json";
	if ( !fopen_s( &file, filePath, "r" ) )
	{
		char line[100] = { 0, };
		while ( !feof( file ) )
		{
			fgets( line, 100, file );
			m_JsonConfig += line;
		}
		
		fclose( file );
	}
	// 설정 파일 로드 실패시 프로그램 죽음
	else
	{
		MessageBox( NULL, L"JSON File Load Fail!", L"Message Box", MB_OK );
		return;
	}

	// Json File Mapping
	rapidjson::Document jConfig;
	jConfig.Parse<0>( m_JsonConfig.c_str() );

	// init objects
	m_pDirectonalLight = DDLight::Create();
	
// 	unsigned int cp = GGameLogic->GetCurrentPlayers();
// 	for ( unsigned int i = 0; i < cp; ++i )
// 	{
// 		AddChild( GGameLogic->GetPlayer(i) );
// 	}	
	AddChild( m_pDirectonalLight );
	
	// test skybox
	SkyBox* sb = SkyBox::Create( L"skybox.x" );
	AddChild( sb );

	// test debris
	// 이거 할당하느라 느리다. 테스트 끝나면 지울 것
	Debris* tempDebris = nullptr;
	int debrisCount = jConfig["debriNumbers"].GetInt();

	for ( unsigned int i = 0; i < debrisCount; ++i )
	{
		tempDebris = Debris::Create( L"debris.x" );
		tempDebris->SetPosition(
			static_cast<float>( ( rand() % 200 ) - 100 ) / 20,
			static_cast<float>( ( rand() % 200 ) - 100 ) / 20,
			static_cast<float>( ( rand() % 200 ) - 100 ) / 20
			);
		tempDebris->SetScale( 0.01f, 0.01f, 0.01f );

		AddChild( tempDebris );
	}

	///////////////////////////////////////////////////////////////////
	////////////복잡한 데브리 잘 들어가는지 확인하는 함수//////////////
	////////////   생각보다 로딩이 많이 느려져서 봉인    //////////////
	///////////////////////////////////////////////////////////////////
// 	for ( unsigned int i = 0; i < 100; ++i )
// 	{
// 		int randX = rand();
// 		int randY = rand();
// 		int randZ = rand();
// 
// 		tempDebris = Debris::Create( L"debrisOne.x" );
// 		tempDebris->SetPosition(
// 			static_cast<float>( ( randX % 200 ) - 100 ) / 20,
// 			static_cast<float>( ( randY % 200 ) - 100 ) / 20,
// 			static_cast<float>( ( randZ % 200 ) - 100 ) / 20
// 			);
// 		tempDebris->SetScale( 0.02f, 0.02f, 0.02f );
// 		tempDebris->SetRotation( randX % 360, randX % 360, randX % 360 );
// 		
// 		AddChild( tempDebris );
// 	}

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

	// 조심해!
	// 내부 구현 아직 제대로 안 된 상태
	GObjectManager = new ObjectManager;

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

	// 키 고유 넘버는 아래를 참조하자 
	// http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	// 현재 w키가 눌렸는지 확인한다
	// 눌렸으면 캐릭터 가속도 세팅하라고 시킴
	// s키가 눌렸다면 정지	
	if ( KEY_DOWN == GetKeyState( 0x57 ) )
	{
		// w : 현재 몸체가 바라보는 방향으로 가속
		GNetworkManager->SendAcceleration();
	}
	
	if ( KEY_DOWN == GetKeyState( 0x53 ) )
	{
		// s : 정지!
		GNetworkManager->SendStop();
	}

	if ( KEY_DOWN == GetKeyState( 0x31 ) )
	{
		// 1 : 밀기 스킬 시전!
		GNetworkManager->SendSkillPush();
	}

	if ( KEY_DOWN == GetKeyState( 0x32 ) )
	{
		// 2 : 당기기 스킬 시전!
		GNetworkManager->SendSkillPull();
	}

	if ( KEY_DOWN == GetKeyState( VK_SPACE ) )
	{
		GNetworkManager->SendTurnBody();
	}
	// 문교수 커피가 든 컵을 들고 오다가 커피가 손에 닿자...
	// 문교수 : 보강 간섭이 일어나지 않게 엇박자로 걸었어야 되는데...라고 말씀하셨다.
	// ㅋㅋㅋㅋ 카멕님이 적으셨습니까

	// 마우스 좌표 변화를 받아온다
	// 변화량을 기준으로 캐릭터한데 회전하라고 시킨다.	
	DDPoint currentMousePos = GetMousePosition( );
	
	// 고개 돌리기는 서버로 보낼 필요 없이 클라이언트에서만 적용
	// 04.27 김성환
	if ( GNetworkManager->GetMyPlayerId() != -1 ) {
		g_PlayerManager->GetPlayer( GNetworkManager->GetMyPlayerId() )->LookAt(
		currentMousePos.GetY() - m_PrevMousePosition.GetY(),
			currentMousePos.GetX() - m_PrevMousePosition.GetX(),
			0
		);
	}
	

	MousePointer(MOUSE_POINTER_ON, currentMousePos);

	UpdateUI();
}

// Mouse Pointer 가릴지 살려둘지 결정
// true 시키면 커서가 계속 가운데로 이동함
// 04.21 김성환
void PlayScene::MousePointer( bool mousePointer, DDPoint currentMousePos )
{
	if ( !mousePointer )
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
	// UI 생성 및 추가 부분을 UI Manager가 처리하도록 뺐음
	// UI Manager 내부에 UI들을 관리하는 자료구조가 필요함 지금은 일단 노가다로 create함수도 2개 만듬
	// DDUI 및 UIManager 참고
	std::wstring filePathFuel = L".\\Resources\\Image\\FuelUI.bmp";
	std::wstring filePathOxygen = L".\\Resources\\Image\\OxygenUI.bmp";
	AddChild( g_UIManager->CreateUIOxygen( filePathOxygen, UI_OXYGEN_POSITION_X, UI_OXYGEN_POSITION_Y ) );
	AddChild( g_UIManager->CreateUIFuel( filePathFuel, UI_FUEL_POSITION_X, UI_FUEL_POSITION_Y ) );

}

void PlayScene::UpdateUI()
{
	// 조심해!! UI가 늘어날 경우 좋은 코드가 아닙니다.
	// 되는지 확인하는 용도입니다.
	// >>> 되긴 되네요. 그런데 스케일을 바꾸면 좌표도 바뀌어서 위치를 재조정해야 함 ㅡㅡ;;
	// 좀 더 좋은 방법을 찾아봐야 할 듯...
	
	unsigned int myId = GNetworkManager->GetMyPlayerId();
	
	// 초기화 덜 됨
	if ( myId >= g_PlayerManager->GetCurrentPlayers() )
	{
		return;
	}

	int currentOxygen = g_PlayerManager->GetPlayer(myId)->GetOxygen();
	int currentFuel = g_PlayerManager->GetPlayer( myId )->GetGas();

	// 현재는 front가 pFuelUI
	g_UIManager->GetUIOxygen()->SetScale( currentOxygen /static_cast<float>(DEFAULT_OXYGEN), 1, 1 );
	g_UIManager->GetUIFuel()->SetScale( currentFuel / static_cast<float>(DEFAULT_FUEL), 1, 1 );
}

void PlayScene::LoadJSON()
{

}
