#include "stdafx.h"
#include "NetworkManager.h"
#include "DDNetwork.h"
#include "PacketType.h"
#include "PlayerManager.h"
#include "ObjectManager.h"
#include "MatrixTransform.h"
#include "SceneManager.h"
#include "CompassUI.h"
#include "PlayScene.h"
#include "GameOption.h"

NetworkManager* GNetworkManager = nullptr;
int NetworkManager::m_MyPlayerId = -1;

NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
}

void NetworkManager::Init()
{
	RegisterHandles();
}

void NetworkManager::Connect()
{
	bool connection = false;

	/// config.h
#ifdef USE_LOCAL_SERVER
	connection = DDNetwork::GetInstance()->Connect( "localhost", 9001 );
#else
	connection = DDNetwork::GetInstance()->Connect( "10.73.45.144", 9001 );
#endif	
	
	if ( connection )
	{
		// 로그인 요청 전송
		LoginRequest outPacket;
		DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
	}
	else
	{
		printf_s( "failed to connection\n" );
	}
}

void NetworkManager::Disconnect()
{
	DDNetwork::GetInstance()->Disconnect();
}

void NetworkManager::SendAcceleration()
{
	if ( m_MyPlayerId == -1 )
		return;

	AccelerarionRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;
	

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendStop()
{
	if ( m_MyPlayerId == -1 )
		return;

	StopRequest  outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

// lookat 방향으로 몸을 회전
// 04.27 김성환
void NetworkManager::SendTurnBody()
{
	if ( m_MyPlayerId == -1 )
		return;

	printf( "send turn body\n" );
	RotationRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	// 카메라 플레이어 분리 후 getcameraviewingdirection은 사용X

	outPacket.mRotation.m_X = g_PlayerManager->GetCamera()->GetTransform().GetRotationX();
	outPacket.mRotation.m_Y = g_PlayerManager->GetCamera()->GetTransform().GetRotationY();
	outPacket.mRotation.m_Z = g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetRotationZ();

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendSkillPush()
{
	if ( m_MyPlayerId == -1 )
		return;

	SkillPushRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mPos = Float3D( g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetPosition() );
	outPacket.mRotation = Float3D( g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetRotation() );

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendSkillPull()
{
	if ( m_MyPlayerId == -1 )
		return;

	SkillPullRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mPos = Float3D( g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetPosition() );
	outPacket.mRotation = Float3D( g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetRotation() );

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}


// 캐릭터가 죽으면 보냄..
// 05.03 김성환
void NetworkManager::SendDeadRequest()
{
	if ( m_MyPlayerId == -1 )
		return;

	DeadRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;
	// player가 update되지 않도록 막음.. 계속 senddeadrequest를 호출할 수 없도록..
	g_PlayerManager->GetPlayer( m_MyPlayerId )->SetUpdatable( false );

	// 지금은 게임 로직 계산은 서버에서만 하므로 일단 보내지 않음
	// DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

// 캐릭터가 리스폰될 때 보냄.
void NetworkManager::SendRespawnRequest( CharacterClass characterClass )
{
	if ( m_MyPlayerId == -1 )
		return;

	RespawnRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;
	outPacket.mCharacterClass = static_cast<int>( characterClass );

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendSkillOccupy()
{
	if ( m_MyPlayerId == -1 )
		return;

	SkillOccupyRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mPos = Float3D( g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetPosition() );
	outPacket.mRotation = Float3D( g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetRotation() );

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::SendSkillDestroy()
{
	if ( m_MyPlayerId == -1 )
		return;

	SkillDestroyRequest outPacket;

	outPacket.mPlayerId = m_MyPlayerId;

	outPacket.mPos = Float3D( g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetPosition() );
	outPacket.mRotation = Float3D( g_PlayerManager->GetPlayer( m_MyPlayerId )->GetTransform().GetRotation() );

	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::RegisterHandles()
{
	// 여기에서 핸들러를 등록하자
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_LOGIN, HandleLoginResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ACCELERATION, HandleGoForwardResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_STOP, HandleStopResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ROTATION, HandleTurnBodyResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SYNC, HandleSyncResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SKILL_PUSH, HandlePushResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_SKILL_PULL, HandlePullResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_NEW, HandleNewResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_DEAD, HandleDeadResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_RESPAWN, HandleRespawnResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_COLLISION, HandleCollisionResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_OCCUPY, HandleOccupyResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_DESTROY, HandleDestroyResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ISS_STATE, HandleIssStateResult );
	DDNetwork::GetInstance()->RegisterHandler( PKT_SC_ISS_MODULE_STATE, HandleIssModuleStateResult );
}

void NetworkManager::HandleLoginResult( DDPacketHeader& pktBase )
{
	// 일단 저기서 얼마만큼 읽어와서 해당 패킷을 구성하고
	LoginResult inPacket = reinterpret_cast<LoginResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// 사용자의 player가 최초 로그인한 경우
	m_MyPlayerId = inPacket.mPlayerId;

	if ( g_PlayerManager->AddPlayer( m_MyPlayerId ) )
	{
		// camera 설정
		DDCamera* camera = DDCamera::Create();
		g_PlayerManager->SetCamera( camera );
		g_SceneManager->GetScene()->AddChild(camera, ORDER_COMPASS_UI);
		camera->SetFollowingObject( g_PlayerManager->GetPlayer( m_MyPlayerId ) );

		// 콤파스 설정
		CompassUI* compassUI = CompassUI::Create( L"tiger.x" );
		compassUI->Init();
		camera->AddChild( compassUI, ORDER_COMPASS_UI );

		// 팀 설정
		g_PlayerManager->GetPlayer( m_MyPlayerId )->SetTeam( static_cast<TeamColor>(inPacket.mTeamColor) );
	}

	GameStateRequest outPacket;
	outPacket.mPlayerId = m_MyPlayerId;
	DDNetwork::GetInstance()->Write( (const char*)&outPacket, outPacket.mSize );
}

void NetworkManager::HandleGoForwardResult( DDPacketHeader& pktBase )
{
	AccelerarionResult inPacket = reinterpret_cast<AccelerarionResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );
		
	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	Player* player = g_PlayerManager->GetPlayer( inPacket.mPlayerId );
	
	// printf_s( "player %d gofoward\ninputVel   : %f %f %f\ncurrentVel : %f %f %f\n", inPacket.mPlayerId, inPacket.mVelocity.x, inPacket.mVelocity.y, inPacket.mVelocity.z, player->GetVelocity().x, player->GetVelocity().y, player->GetVelocity().z);
	// printf_s( "currentAcc : %f %f %f\n", player->GetAcceleration().x, player->GetAcceleration().y, player->GetAcceleration().z );

	player->GoForward();

	player->GetTransform().SetPosition( inPacket.mPos.GetD3DVEC() );
	player->GetTransform().SetRotation( inPacket.mRotation.GetD3DVEC() );
	player->GetClassComponent().SetVelocity( inPacket.mVelocity.GetD3DVEC() );
}

void NetworkManager::HandleStopResult( DDPacketHeader& pktBase )
{
	StopResult inPacket = reinterpret_cast<StopResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );
		
	g_PlayerManager->AddPlayer( inPacket.mPlayerId );		
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->Stop();
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->GetTransform().SetPosition( inPacket.mPos.GetD3DVEC() );
}

void NetworkManager::HandleTurnBodyResult( DDPacketHeader& pktBase )
{
	RotationResult inPacket = reinterpret_cast<RotationResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->TurnBody( inPacket.mRotation.m_X, inPacket.mRotation.m_Y, inPacket.mRotation.m_Z );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->StopSpin();
}

void NetworkManager::HandleSyncResult( DDPacketHeader& pktBase )
{
	SyncResult inPacket = reinterpret_cast<SyncResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// 서버의 충돌박스 그리기 용 임시..
#ifdef USE_CHARACTER_COLLISION_BOX
	int dummyPlayerID = -1;
	if ( inPacket.mPlayerId != -1 )
	{
		dummyPlayerID = inPacket.mPlayerId + REAL_PLAYER_NUM;

		g_PlayerManager->AddPlayer( dummyPlayerID );
		g_PlayerManager->GetPlayer( dummyPlayerID )->GetTransform().SetPosition( inPacket.mPos.GetD3DVEC() );
		g_PlayerManager->GetPlayer( dummyPlayerID )->GetClassComponent().SetVelocity( inPacket.mVelocity.GetD3DVEC() );
	}
#else
#endif
}

void NetworkManager::HandlePushResult( DDPacketHeader& pktBase )
{
	SkillPushResult inPacket = reinterpret_cast<SkillPushResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mTargetId );
	Player* targetPlayer = g_PlayerManager->GetPlayer( inPacket.mTargetId );
	//targetPlayer->GoForward();
	targetPlayer->GetClassComponent().AddForce( inPacket.mForce.GetD3DVEC() );
	targetPlayer->GetTransform().SetPosition( inPacket.mPos.GetD3DVEC() );
	targetPlayer->GetClassComponent().SetVelocity( inPacket.mVelocity.GetD3DVEC() );

	if ( inPacket.mSpinAxis.m_X == 0.0f && inPacket.mSpinAxis.m_Y == 0.0f && inPacket.mSpinAxis.m_Z == 0.0f )
		return;

	targetPlayer->SetSpin( inPacket.mSpinAxis.GetD3DVEC(), inPacket.mSpinAngularVelocity );
	// player->SetSpin( DDVECTOR3( 1.0f, 1.0f, 0.0f ), inPacket.mSpinAngularVelocity );

	printf_s( "[SKILL] PUSH from %d player\n", inPacket.mPlayerId );
}

void NetworkManager::HandlePullResult( DDPacketHeader& pktBase )
{
	SkillPullResult inPacket = reinterpret_cast<SkillPullResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mTargetId );
	Player* targetPlayer = g_PlayerManager->GetPlayer( inPacket.mTargetId );
	targetPlayer->GetClassComponent().AddForce( inPacket.mForce.GetD3DVEC() );
	targetPlayer->GetTransform().SetPosition( inPacket.mPos.GetD3DVEC() );
	targetPlayer->GetClassComponent().SetVelocity( inPacket.mVelocity.GetD3DVEC() );

	if ( inPacket.mSpinAxis.m_X == 0.0f && inPacket.mSpinAxis.m_Y == 0.0f && inPacket.mSpinAxis.m_Z == 0.0f )
		return;

	targetPlayer->SetSpin( inPacket.mSpinAxis.GetD3DVEC(), inPacket.mSpinAngularVelocity );

	printf_s( "[SKILL] PULL from %d player\n", inPacket.mPlayerId );
}

void NetworkManager::HandleNewResult( DDPacketHeader& pktBase )
{
	NewResult inPacket = reinterpret_cast<NewResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->GetTransform().SetPosition( inPacket.mPos.GetD3DVEC() );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->GetTransform().SetRotation( inPacket.mRotation.GetD3DVEC() );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->GetClassComponent().SetVelocity( inPacket.mVelocity.GetD3DVEC() );
}


void NetworkManager::HandleDeadResult( DDPacketHeader& pktBase )
{
	DeadResult inPacket = reinterpret_cast<DeadResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// 죽으면 처리할 부분 추가할 것
	// fps 게임에서 죽으면 다른 캐릭터 보는 view로 바꿔준다거나, scene을 바꿔준다거나...	

	// 죽어라
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->GetClassComponent().SetHP( 0.0f );
}

void NetworkManager::HandleRespawnResult( DDPacketHeader& pktBase )
{
	RespawnResult inPacket = reinterpret_cast<RespawnResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	Player* player = g_PlayerManager->GetPlayer( m_MyPlayerId );
	// player::changeClass 내용 구현 후 적용할 것. 지금은 껍데기만 있음..
	//g_PlayerManager->GetPlayer( m_MyPlayerId )->ChangeClass( static_cast<CharacterClass>( inPacket.mCharacterClass ) );


	printf_s( "respawn player" );
	player->GetClassComponent().SetOxygen( DEFAULT_OXYGEN );
	player->GetClassComponent().SetHP( DEFAULT_HP );
	player->GetClassComponent().SetFuel( DEFAULT_FUEL );
	player->SetUpdatable( true );

	player->GetClassComponent().SetVelocity( ZERO_VECTOR3 );
	player->GetTransform().SetPosition( inPacket.mPos.GetD3DVEC() );
	player->GetTransform().SetRotation( inPacket.mRotation.GetD3DVEC() );
}

void NetworkManager::HandleCollisionResult( DDPacketHeader& pktBase )
{
	CollisionResult inPacket = reinterpret_cast<CollisionResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );
	
	g_PlayerManager->AddPlayer( inPacket.mPlayerId );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->GetTransform().SetPosition( inPacket.mPos.GetD3DVEC() );
	g_PlayerManager->GetPlayer( inPacket.mPlayerId )->GetClassComponent().SetVelocity( inPacket.mVelocity.GetD3DVEC() );
}

void NetworkManager::HandleOccupyResult( DDPacketHeader& pktBase )
{
	SkillOccupyResult inPacket = reinterpret_cast<SkillOccupyResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// ISS의 운동 상태를 바꾼다.
	GObjectManager->GetISS()->SetOwner(inPacket.mModule, inPacket.mOccupyTeam );
	GObjectManager->GetISS()->GetTransform().SetPosition( DDVECTOR3( 0.0f, 0.0f, inPacket.mIssPositionZ ) );
	GObjectManager->GetISS()->SetVelocity( DDVECTOR3( 0.0f, 0.0f, inPacket.mIssVelocityZ ) );
}

void NetworkManager::HandleDestroyResult( DDPacketHeader& pktBase )
{
	SkillDestroyResult inPacket = reinterpret_cast<SkillDestroyResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// ISS의 체력을 바꾼다.
	GObjectManager->GetISS()->SetHP( inPacket.mModule, inPacket.mModuleHP );
}

void NetworkManager::HandleIssStateResult( DDPacketHeader& pktBase )
{
	IssStateResult inPacket = reinterpret_cast<IssStateResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// ISS의 위치와 속도를 바꾼다.
	GObjectManager->GetISS()->GetTransform().SetPosition( DDVECTOR3( 0.0f, 0.0f, inPacket.mIssPositionZ ) );
	GObjectManager->GetISS()->SetVelocity( DDVECTOR3( 0.0f, 0.0f, inPacket.mIssVelocityZ ) );

	for ( int i = 0; i < MODULE_NUMBER; ++i )
	{
		GObjectManager->GetISS( )->SetOwner( i, inPacket.mModuleOwner[i] );
		GObjectManager->GetISS( )->SetHP( i, inPacket.mModuleHP[i] );
	}
}

void NetworkManager::HandleIssModuleStateResult( DDPacketHeader& pktBase )
{
	IssModuleStateResult inPacket = reinterpret_cast<IssModuleStateResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// ISS의 체력을 바꾼다.
	GObjectManager->GetISS()->SetOwner( inPacket.mModuleIdx, inPacket.mOwner );
	GObjectManager->GetISS()->SetHP( inPacket.mModuleIdx, inPacket.mHP );
}

void NetworkManager::HandleGameResultResult( DDPacketHeader& pktBase )
{
	GameResultResult inPacket = reinterpret_cast<GameResultResult&>( pktBase );
	DDNetwork::GetInstance()->GetPacketData( (char*)&inPacket, inPacket.mSize );

	// ISS의 체력을 바꾼다.
	printf_s( "winner id %d\n", inPacket.mWinnerTeam );

	// 일단 다른 씬들이 없으므로 게임을 종료시킨다.
	DDNetwork::GetInstance()->Disconnect();
}