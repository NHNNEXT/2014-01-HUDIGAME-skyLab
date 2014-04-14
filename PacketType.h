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

	PKT_SC_NEW = 11, // �� �÷��̾ ������Ʈ ����

	PKT_MAX = 1024
};

#pragma pack(push, 1)

struct PacketHeader
{
	PacketHeader() : mSize( 0 ), mType( PKT_NONE ) 	{}
	unsigned short mSize;
	unsigned short mType;
};


// �α��� ��û
struct LoginRequest : public PacketHeader
{
	LoginRequest()
	{
		mSize = sizeof( LoginRequest );
		mType = PKT_CS_LOGIN;
	}
};

// ���̵� �Ҵ��ؼ� ����
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

// ���� �� �ϰڽ��ϴ�.
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

// ���� - id, ��ġ, �ӵ�, ����(���� ȸ�� ���� - ���߿��� �����ü�� �Ѱܾ� �� ���� �־�)
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

// ��� �����մϴ�.
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

// ��� �����ض�.
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

// ȸ�� �� �ϰڽ��ϴ�. - ���߿��� �������� �ƴ϶� ȸ�� ��ȯ ��� ��ü�� ������?
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

// ȸ�� �ض�.
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

// �ֱ����� ����ȭ�� ���ؼ� - ������Ʈ���� ��� ����... �ϴ� �÷��̾ ����
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

// �ϴ� �� �÷��̾� �����ϴ� �Ϳ� ���ؼ���
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