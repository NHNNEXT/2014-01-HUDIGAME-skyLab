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

	PKT_SC_NEW = 11, // 새 플레이어나 오브젝트 생성

	PKT_MAX = 1024
};

#pragma pack(push, 1)

struct PacketHeader
{
	PacketHeader() : mSize( 0 ), mType( PKT_NONE ) 	{}
	unsigned short mSize;
	unsigned short mType;
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

	double mRotationX;
	double mRotationY;
	double mRotationZ;
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

	double mPosX;
	double mPosY;
	double mPosZ;

	double mVelocityX;
	double mVelocityY;
	double mVelocityZ;

	double mRotationX;
	double mRotationY;
	double mRotationZ;
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

	double mPosX;
	double mPosY;
	double mPosZ;
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

	double mRotationX;
	double mRotationY;
	double mRotationZ;
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

	double mRotationX;
	double mRotationY;
	double mRotationZ;
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

		mRotationX = 0.0f;
		mRotationY = 0.0f;
		mRotationZ = 0.0f;
	}

	int		mPlayerId;

	double mPosX;
	double mPosY;
	double mPosZ;

	double mVelocityX;
	double mVelocityY;
	double mVelocityZ;

	double mRotationX;
	double mRotationY;
	double mRotationZ;
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

	double mPosX;
	double mPosY;
	double mPosZ;

	double mVelocityX;
	double mVelocityY;
	double mVelocityZ;

	double mAccelerarionX;
	double mAccelerarionY;
	double mAccelerarionZ;

	double mRotationX;
	double mRotationY;
	double mRotationZ;
};

#pragma pack(pop)