#pragma once

#include "stdafx.h"
#include "GameMacro.h"
#include "GameOption.h"
#include "../DDFramework/DDResourceManager.h"


//////////////////////////////////////
////////////Json Key Datas////////////

// 주의! 아래쪽의 JSON_KEY_LIST와 순서를 동기화시켜야 합니다
// 주의! Tool 에서 사용하는 JsonKeyValues와 동기화시켜야 합니다
enum JsonKeyValues : int
{
	JSON_DEBRIS_NUMBER = 0,
	JSON_ISS,
	JSON_TOTAL_KEY_COUNT
};

// 주의! JsonKeyVales를 바꾸면 이쪽도 같이 바꾸자
const std::map<JsonKeyValues, std::string> JSON_KEY_MAP =
{
	{ JsonKeyValues::JSON_DEBRIS_NUMBER, "debrisNumber" },
	{ JsonKeyValues::JSON_ISS, "ISS" },
};


// JSON 파일에서 불러오기 위한 ISSModule 변수
const std::map<ISSModuleName, std::string> JSON_ISS_PART_NAME =
{
	{ ISSModuleName::PART0, "0" },
	{ ISSModuleName::PART1, "1" },
	{ ISSModuleName::PART2, "2" },
	{ ISSModuleName::PART3, "3" },
	{ ISSModuleName::PART4, "4" },
	{ ISSModuleName::PART5, "5" },
	{ ISSModuleName::PART6, "6" },
	{ ISSModuleName::PART7, "7" },
	{ ISSModuleName::PART8, "8" },
	{ ISSModuleName::PART9, "9" },
};


////////////Json Key Datas////////////
//////////////////////////////////////



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
	D3DXVECTOR3 GetISSModuleAxisLength( ISSModuleName name );

private:
	static const std::string GAME_DATA_PATH;
	rapidjson::Document m_Document;
};

extern std::shared_ptr<GameData> g_GameData;