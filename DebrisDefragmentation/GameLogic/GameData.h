#pragma once

#include "stdafx.h"
#include "GameMacro.h"
#include "GameOption.h"
#include "../DDFramework/DDResourceManager.h"

class GameData
{
public:
	GameData();
	~GameData();

	CREATE_FUNC( GameData );

	bool Init();
	
	// 생각해보니 얼마 안 되겠네요 그냥 그때그때 만들어서 쓰면 됩니다
	int GetDebrisNumber();
	D3DXVECTOR3 GetISSPosition( ISSModuleName name );

private:
	static const std::string GAME_DATA_PATH;
	rapidjson::Document m_Document;
};

extern std::shared_ptr<GameData> g_GameData;