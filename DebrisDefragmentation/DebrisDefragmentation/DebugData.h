#pragma once

#include "GameOption.h"

class DebugData
{
public:
	DebugData()
	{
		mPlayerTeam.fill( -1 );
		mPlayerTeam.fill( -1 );
		mModuleOwner.fill( -1 );
		mModuleHP.fill( 0.0f );
	}
	~DebugData();

	// server debug info
	std::array<int, REAL_PLAYER_NUM> mPlayerTeam;
	std::array<int, REAL_PLAYER_NUM> mPlayerClass;

	float		mIssPos = 0.0f;
	float		mIssVelocity = 0.0f;

	std::array<int, MODULE_NUMBER> mModuleOwner;
	std::array<float, MODULE_NUMBER> mModuleHP;

	// client debug info
	int		mPlayerId = -1;
	int		mClass = -1;

	D3DXVECTOR3 mPos;

	bool	mIsSpin = false;
	bool	mIsAccelerate = false;

	float		mSpeedConstant = 1.0f;
	D3DXVECTOR3 mAcceleration;
	D3DXVECTOR3 mVelocity;
	D3DXVECTOR3 mSpinAxis;

	float	mSpinAngularVelocity = 0.0f;

	float	mFuel = 0.0f;
	float	mOxygen = 0.0f;

	bool	mDisplayDebugInfoFlag = false;
};

extern DebugData* GDebugData;