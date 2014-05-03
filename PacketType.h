#pragma once

#define MAX_CHAT_LEN	1024

#define MAX_NAME_LEN	30
#define MAX_COMMENT_LEN	40

enum PacketTypes
{
	PKT_NONE = 0,

	PKT_CS_LOGIN = 1,
	PKT_SC_LOGIN = 2,

	PKT_CS_ACCELERATION = 3,
	PKT_SC_ACCELERATION = 4,

	PKT_CS_STOP = 5,
	PKT_SC_STOP = 6,

	PKT_CS_ROTATION = 7,
	PKT_SC_ROTATION = 8,

	PKT_CS_SYNC = 9,
	PKT_SC_SYNC = 10,

	PKT_CS_NEW = 11, // 새 플레이어나 오브젝트 생성
	PKT_SC_NEW = 12,

	PKT_CS_SKILL_PUSH = 13,
	PKT_SC_SKILL_PUSH = 14,

	PKT_CS_SKILL_PULL = 15,
	PKT_SC_SKILL_PULL = 16,

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
	}

	int		mPlayerId;
};

// 가속 좀 하겠습니다.
struct AccelerarionRequest : public PacketHeader
{
	AccelerarionRequest()
	{
		mSize = sizeof( AccelerarionRequest );
		mType = PKT_CS_ACCELERATION;
		mPlayerId = -1;

		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mRotationZ = 0.0f;
	}

	int	mPlayerId;

	float mRotationX;
	float mRotationY;
	float mRotationZ;
};

// 가속 - id, 위치, 속도, 방향(현재 회전 각도 - 나중에는 행렬자체를 넘겨야 할 수도 있어)
struct AccelerarionResult : public PacketHeader
{
	AccelerarionResult()
	{
		mSize = sizeof( AccelerarionResult );
		mType = PKT_SC_ACCELERATION;
		mPlayerId = -1;

		mPosX = 0.0f;
		mPosY = 0.0f;
		mPosZ = 0.0f;

		mVelocityX = 0.0f;
		mVelocityY = 0.0f;
		mVelocityZ = 0.0f;

		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mRotationZ = 0.0f;
	}

	int	mPlayerId;

	float mPosX;
	float mPosY;
	float mPosZ;

	float mVelocityX;
	float mVelocityY;
	float mVelocityZ;

	float mRotationX;
	float mRotationY;
	float mRotationZ;
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

		mPosX = 0.0f;
		mPosY = 0.0f;
		mPosZ = 0.0f;
	}

	int		mPlayerId;

	float mPosX;
	float mPosY;
	float mPosZ;
};

// 회전 좀 하겠습니다. - 나중에는 각도만이 아니라 회전 변환 행렬 전체를 보내야?
struct RotationRequest : public PacketHeader
{
	RotationRequest()
	{
		mSize = sizeof( RotationRequest );
		mType = PKT_CS_ROTATION;
		mPlayerId = -1;

		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mRotationZ = 0.0f;
	}

	int		mPlayerId;

	float mRotationX;
	float mRotationY;
	float mRotationZ;
};

// 회전 해라.
struct RotationResult : public PacketHeader
{
	RotationResult()
	{
		mSize = sizeof( RotationResult );
		mType = PKT_SC_ROTATION;
		mPlayerId = -1;

		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mRotationZ = 0.0f;
	}

	int		mPlayerId;

	float mRotationX;
	float mRotationY;
	float mRotationZ;
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

		mPosX = 0.0f;
		mPosY = 0.0f;
		mPosZ = 0.0f;

		mVelocityX = 0.0f;
		mVelocityY = 0.0f;
		mVelocityZ = 0.0f;
	}

	int		mPlayerId;

	float mPosX;
	float mPosY;
	float mPosZ;

	float mVelocityX;
	float mVelocityY;
	float mVelocityZ;
};

// 일단 새 플레이어 생성하는 것에 대해서만
struct NewResult : public PacketHeader
{
	NewResult()
	{
		mSize = sizeof( NewResult );
		mType = PKT_CS_SYNC;
		mPlayerId = -1;

		mPosX = 0.0f;
		mPosY = 0.0f;
		mPosZ = 0.0f;

		mVelocityX = 0.0f;
		mVelocityY = 0.0f;
		mVelocityZ = 0.0f;

		mAccelerarionX = 0.0f;
		mAccelerarionY = 0.0f;
		mAccelerarionZ = 0.0f;

		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mRotationZ = 0.0f;
	}

	int		mPlayerId;

	float mPosX;
	float mPosY;
	float mPosZ;

	float mVelocityX;
	float mVelocityY;
	float mVelocityZ;

	float mAccelerarionX;
	float mAccelerarionY;
	float mAccelerarionZ;

	float mRotationX;
	float mRotationY;
	float mRotationZ;
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

		mPosX = 0.0f;
		mPosY = 0.0f;
		mPosZ = 0.0f;

		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mRotationZ = 0.0f;
	}

	int		mPlayerId;

	float mPosX;
	float mPosY;
	float mPosZ;

	float mRotationX;
	float mRotationY;
	float mRotationZ;
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

		mPosX = 0.0f;
		mPosY = 0.0f;
		mPosZ = 0.0f;

		mVelocityX = 0.0f;
		mVelocityY = 0.0f;
		mVelocityZ = 0.0f;

		mSpinAxisX = 0.0f;
		mSpinAxisY = 0.0f;
		mSpinAxisZ = 0.0f;

		mSpinAngularVelocity = 0.0f;
	}

	int		mPlayerId;
	int		mTargetId;

	float mPosX;
	float mPosY;
	float mPosZ;

	float mVelocityX;
	float mVelocityY;
	float mVelocityZ;

	float mSpinAxisX;
	float mSpinAxisY;
	float mSpinAxisZ;

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

		mPosX = 0.0f;
		mPosY = 0.0f;
		mPosZ = 0.0f;

		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mRotationZ = 0.0f;
	}

	int		mPlayerId;

	float mPosX;
	float mPosY;
	float mPosZ;

	float mRotationX;
	float mRotationY;
	float mRotationZ;
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

		mPosX = 0.0f;
		mPosY = 0.0f;
		mPosZ = 0.0f;

		mVelocityX = 0.0f;
		mVelocityY = 0.0f;
		mVelocityZ = 0.0f;

		mSpinAxisX = 0.0f;
		mSpinAxisY = 0.0f;
		mSpinAxisZ = 0.0f;

		mSpinAngularVelocity = 0.0f;
	}

	int		mPlayerId;
	int		mTargetId;

	float mPosX;
	float mPosY;
	float mPosZ;

	float mVelocityX;
	float mVelocityY;
	float mVelocityZ;

	float mSpinAxisX;
	float mSpinAxisY;
	float mSpinAxisZ;

	float mSpinAngularVelocity;
};

#pragma pack(pop)