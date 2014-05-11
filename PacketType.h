#pragma once

#include <d3dx9.h>

#define MAX_CHAT_LEN	1024

#define MAX_NAME_LEN	30
#define MAX_COMMENT_LEN	40

// POD type
// http://en.wikipedia.org/wiki/Plain_Old_Data_Structures
struct Float3D
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};

// Float3D가 POD 이므로 사용자 지정 생성자를 만들 수 없음
// D3DXVECTOR3와 Float3D 사이의 변환을 간단하게 하는 함수를 따로 정의
// 복사 대입 생성자도 정의할 수 없으므로 참조자를 이용한 연산으로 구현
static void Float3DtoD3DXVECTOR3( _Out_ D3DXVECTOR3& target, _In_ const Float3D& src )
{
	target.x = src.x;
	target.y = src.y;
	target.z = src.z;
}

static void D3DXVECTOR3toFloat3D( _Out_ Float3D& target, _In_ const D3DXVECTOR3& src )
{
	target.x = src.x;
	target.y = src.y;
	target.z = src.z;
}


// 조심해!!
// 패킷 종류 - 스킬인지, 게임 진행 상태인지에 따라서 숫자 구간 나눠서 사용하자
enum PacketTypes
{
	PKT_NONE = 0,

	// 로그인 및 기타 초반 접속에 관련된 패킷
	PKT_CS_LOGIN = 1,
	PKT_SC_LOGIN = 2,

	PKT_CS_NEW = 3, // 새 플레이어나 오브젝트 생성
	PKT_SC_NEW = 4,


	// 게임 내 상태 전달에 관련된 패킷
	PKT_CS_GAME_STATE = 101,
	PKT_SC_GAME_STATE = 102,

	PKT_CS_ISS_STATE = 103,
	PKT_SC_ISS_STATE = 104,

	PKT_CS_ISS_MODULE_STATE = 105,
	PKT_SC_ISS_MODULE_STATE = 106,


	// 플레이어 상태에 관련된 패킷
	PKT_CS_DEAD = 201,
	PKT_SC_DEAD = 202,

	PKT_CS_RESPAWN = 203,
	PKT_SC_RESPAWN = 204,

	PKT_CS_COLLISION = 205,
	PKT_SC_COLLISION = 206,


	// 플레이어 기본 스킬에 관련된 패킷
	PKT_CS_ACCELERATION = 301,
	PKT_SC_ACCELERATION = 302,

	PKT_CS_STOP = 303,
	PKT_SC_STOP = 304,

	PKT_CS_ROTATION = 305,
	PKT_SC_ROTATION = 306,

	PKT_CS_SKILL_PUSH = 307,
	PKT_SC_SKILL_PUSH = 308,

	PKT_CS_SKILL_PULL = 309,
	PKT_SC_SKILL_PULL = 310,

	PKT_CS_OCCUPY = 311,
	PKT_SC_OCCUPY = 312,

	PKT_CS_DESTROY = 313,
	PKT_SC_DESTROY = 314,


	// 플레이어 특수 스킬에 관련된 패킷


	// 기타 패킷
	PKT_CS_SYNC = 901,
	PKT_SC_SYNC = 902,

	PKT_MAX = 1024
};

#pragma pack(push, 1)

struct PacketHeader
{
	PacketHeader() : mSize( 0 ), mType( PKT_NONE ) 	{}
	unsigned short mSize;
	short mType;
};


// 로그인 요청
struct LoginRequest : public PacketHeader
{
	LoginRequest()
	{
		mSize = sizeof( LoginRequest );
		mType = PKT_CS_LOGIN;
	}
};

// 아이디 할당해서 전송
struct LoginResult : public PacketHeader
{
	LoginResult()
	{
		mSize = sizeof( LoginResult );
		mType = PKT_SC_LOGIN;
		mPlayerId = -1;

		mTeamColor = -1;
	}

	int		mPlayerId;
	int		mTeamColor;
};

// 가속 좀 하겠습니다.
struct AccelerarionRequest : public PacketHeader
{
	AccelerarionRequest()
	{
		mSize = sizeof( AccelerarionRequest );
		mType = PKT_CS_ACCELERATION;
		mPlayerId = -1;
	}

	int	mPlayerId;
};

// 가속 - id, 위치, 속도, 방향(현재 회전 각도 - 나중에는 행렬자체를 넘겨야 할 수도 있어)
struct AccelerarionResult : public PacketHeader
{
	AccelerarionResult()
	{
		mSize = sizeof( AccelerarionResult );
		mType = PKT_SC_ACCELERATION;
		mPlayerId = -1;
	}

	int	mPlayerId;

	Float3D mPos;
	Float3D mVelocity;
	Float3D mRotation;
};

// 장비를 정지합니다.
struct StopRequest : public PacketHeader
{
	StopRequest()
	{
		mSize = sizeof( StopRequest );
		mType = PKT_CS_STOP;
		mPlayerId = -1;
	}

	int		mPlayerId;
};

// 장비를 정지해라.
struct StopResult : public PacketHeader
{
	StopResult()
	{
		mSize = sizeof( StopResult );
		mType = PKT_SC_STOP;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mPos;
};

// 회전 좀 하겠습니다. - 나중에는 각도만이 아니라 회전 변환 행렬 전체를 보내야?
struct RotationRequest : public PacketHeader
{
	RotationRequest()
	{
		mSize = sizeof( RotationRequest );
		mType = PKT_CS_ROTATION;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mRotation;
};

// 회전 해라.
struct RotationResult : public PacketHeader
{
	RotationResult()
	{
		mSize = sizeof( RotationResult );
		mType = PKT_SC_ROTATION;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mRotation;
};

// 주기적인 동기화를 위해서 - 오브젝트들은 어떻게 하지... 일단 플레이어만 하자
struct SyncRequest : public PacketHeader
{
	SyncRequest()
	{
		mSize = sizeof( SyncRequest );
		mType = PKT_CS_SYNC;
		mPlayerId = -1;
	}

	int		mPlayerId;
};

struct SyncResult : public PacketHeader
{
	SyncResult()
	{
		mSize = sizeof( SyncResult );
		mType = PKT_SC_SYNC;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mPos; 
	Float3D mVelocity;
};


// 캐릭터 hp가 0일 때 보냄.
struct DeadRequest : public PacketHeader
{
	DeadRequest()
	{
		mSize = sizeof( DeadRequest );
		mType = PKT_CS_DEAD;
		mPlayerId = -1;
	}

	int		mPlayerId;
};

struct DeadResult : public PacketHeader
{
	DeadResult()
	{
		mSize = sizeof ( DeadResult );
		mType = PKT_SC_DEAD;
		mPlayerId = -1;
	}

	int		mPlayerId;
};

struct RespawnRequest : public PacketHeader
{
	RespawnRequest()
	{
		mSize = sizeof ( RespawnRequest );
		mType = PKT_CS_RESPAWN;
		mPlayerId = -1;
		mCharacterClass = 0; // no_class
	}
	int		mPlayerId;
	int		mCharacterClass;
};

struct RespawnResult : public PacketHeader
{
	RespawnResult()
	{
		mSize = sizeof ( RespawnResult );
		mType = PKT_SC_RESPAWN;
		mPlayerId = -1;
		mCharacterClass = 0; // no_class
	}

	int		mPlayerId;
	int		mCharacterClass;

	Float3D mPos;
	Float3D mRotation;
};

// 일단 안씀.. 충돌체크는 서버에서
struct CollisionRequest : public PacketHeader
{

};

struct CollisionResult : public PacketHeader
{
	CollisionResult()
	{
		mSize = sizeof ( CollisionResult );
		mType = PKT_SC_COLLISION;
		mPlayerId = -1;		
	}

	int		mPlayerId; 
	
	Float3D mPos;
	Float3D mVelocity;
};


// 일단 새 플레이어 생성하는 것에 대해서만
// 나중에는 플레이어 오브젝트 구분해야 함
struct NewResult : public PacketHeader
{
	NewResult()
	{
		mSize = sizeof( NewResult );
		mType = PKT_SC_NEW;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mPos;
	Float3D mVelocity;
	Float3D mRotation;
};

// 밀기 스킬 시전!
// 지금 보는 방향을 기준으로 스킬 시전
struct SkillPushRequest : public PacketHeader
{
	SkillPushRequest()
	{
		mSize = sizeof( SkillPushRequest );
		mType = PKT_CS_SKILL_PUSH;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mPos;
	Float3D mRotation;
};

// 타겟이 있으면 운동 상태를 바꿔놓고, 바뀐 운동 상태를 전송
// 플러스 시전한 애가 누군지는 알려주자
// 주의!! 여기에 적힌 mPlayerId는 스킬 시전자 / mTargetId는 스킬을 당한 애
// 기타 패킷에 적힌 상태 정보는 mTargetId의 상태
struct SkillPushResult : public PacketHeader
{
	SkillPushResult()
	{
		mSize = sizeof( SkillPushResult );
		mType = PKT_SC_SKILL_PUSH;
		mPlayerId = -1;
		mTargetId = -1;

		mSpinAngularVelocity = 0.0f;
	}

	int		mPlayerId;
	int		mTargetId;

	Float3D mPos;
	Float3D mVelocity;
	Float3D mSpinAxis;
	Float3D mForce;

	float mSpinAngularVelocity;
};

// 당기기 스킬 시전!
// 지금 보는 방향을 기준으로 스킬 시전
struct SkillPullRequest : public PacketHeader
{
	SkillPullRequest()
	{
		mSize = sizeof( SkillPullRequest );
		mType = PKT_CS_SKILL_PULL;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mPos;
	Float3D mRotation;
};

// 타겟이 있으면 운동 상태를 바꿔놓고, 바뀐 운동 상태를 전송
// 플러스 시전한 애가 누군지는 알려주자
// 주의!! 여기에 적힌 mPlayerId는 스킬 시전자 / mTargetId는 스킬을 당한 애
// 기타 패킷에 적힌 상태 정보는 mTargetId의 상태
struct SkillPullResult : public PacketHeader
{
	SkillPullResult()
	{
		mSize = sizeof( SkillPullResult );
		mType = PKT_SC_SKILL_PULL;
		mPlayerId = -1;
		mTargetId = -1;

		mSpinAngularVelocity = 0.0f;
	}

	int		mPlayerId;
	int		mTargetId;

	Float3D mPos;
	Float3D mVelocity;
	Float3D mSpinAxis;
	Float3D mForce;

	float mSpinAngularVelocity;
};

// 로그인을 성공하면 지금 게임 상태를 모두 전송 받는다.
struct GameStateRequest : public PacketHeader
{
	GameStateRequest()
	{
		mSize = sizeof( GameStateRequest );
		mType = PKT_CS_GAME_STATE;
		mPlayerId = -1;
	}

	int		mPlayerId;
};

// 오브젝트나 플레이어는 각각의 sync패킷으로 보내고
// 이 패킷에는 게임 현재 상태(시작하고 지난 시간, 각 팀 점수 등)를 전송
struct GameStateResult : public PacketHeader
{
	GameStateResult()
	{
		mSize = sizeof( GameStateResult );
		mType = PKT_SC_GAME_STATE;
		mPlayerId = -1;
	}

	int		mPlayerId;

	// 추가할 것
};

// 점령! - 빈 곳이면 점령하고 상대방 소유면 빈 곳으로, 우리편 소유면 그냥 그대로
struct SkillOccupyRequest : public PacketHeader
{
	SkillOccupyRequest( )
	{
		mSize = sizeof( SkillOccupyRequest );
		mType = PKT_CS_OCCUPY;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mPos;
	Float3D mRotation;
};

// 점령 상태가 바뀌면 어떤 것이 바뀌었는지, 소유팀은 어디인지, 스킬은 누가 썼는지 전송
struct SkillOccupyResult : public PacketHeader
{
	SkillOccupyResult( )
	{
		mSize = sizeof( SkillOccupyResult );
		mType = PKT_SC_OCCUPY;
		mPlayerId = -1;

		mModule = -1;
		mOccupyTeam = -1;

		mIssVelocityZ = 0.0f;
		mIssPositionZ = 0.0f;
	}

	int		mPlayerId;

	int		mModule;
	int		mOccupyTeam;

	float	mIssVelocityZ;
	float	mIssPositionZ;
};

// 파괴! - 걸리는 모듈이 있으면 체력을 깎자
struct SkillDestroyRequest : public PacketHeader
{
	SkillDestroyRequest( )
	{
		mSize = sizeof( SkillDestroyRequest );
		mType = PKT_CS_DESTROY;
		mPlayerId = -1;
	}

	int		mPlayerId;

	Float3D mPos;
	Float3D mRotation;
};

// 파괴! - 어떤 모듈인지, 누가 부순건지, 지금 체력은 얼마인지 
struct SkillDestroyResult : public PacketHeader
{
	SkillDestroyResult( )
	{
		mSize = sizeof( SkillDestroyResult );
		mType = PKT_SC_DESTROY;
		mPlayerId = -1;

		mModule = -1;
		mModuleHP = 1.0f;
	}

	int		mPlayerId;

	int		mModule;
	float	mModuleHP;
};

// 지금 ISS 위치, 속도 알려주세요
struct IssStateRequest : public PacketHeader
{
	IssStateRequest()
	{
		mSize = sizeof( IssStateRequest );
		mType = PKT_CS_ISS_STATE;
		mPlayerId = -1;
	}

	int		mPlayerId;
};

// 지금 ISS 위치, 속도 알려드립니다.
struct IssStateResult : public PacketHeader
{
	IssStateResult()
	{
		mSize = sizeof( IssStateResult );
		mType = PKT_SC_ISS_STATE;

		mIssPositionZ = 0.0f;
		mIssVelocityZ = 0.0f;
	}
	
	float	mIssPositionZ;
	float	mIssVelocityZ;
};

// 지금 ISS 모듈 소유자 및 체력 알려주세요
struct IssModuleStateRequest : public PacketHeader
{
	IssModuleStateRequest()
	{
		mSize = sizeof( IssModuleStateRequest );
		mType = PKT_CS_ISS_MODULE_STATE;
		mPlayerId = -1;
	}

	int		mPlayerId;
};

// 지금 ISS 모듈 소유자 및 체력 알려드립니다.
struct IssModuleStateResult : public PacketHeader
{
	IssModuleStateResult()
	{
		mSize = sizeof( IssModuleStateResult );
		mType = PKT_SC_ISS_MODULE_STATE;
		mModuleIdx = -1;

		mOwner = -1;
		mHP = 1.0f;
	}

	int		mModuleIdx;

	int		mOwner;
	float	mHP;
};

#pragma pack(pop)