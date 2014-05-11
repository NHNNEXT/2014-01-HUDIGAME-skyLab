#pragma once

#include "DDResourceManager.h"
#include "stdafx.h"
#include "GameMacro.h"
#include "GameOption.h"

// enum JsonDataListTag
// {
// 	JSON_DEBRIS_NUMBER,
// };

class GameData
{
public:
	GameData();
	~GameData();

	CREATE_FUNC( GameData );

	bool Init();
	// 조심해!!
	// 리턴해야 할 인자들이 엄청 많아지면 어떻게 컨트롤할지 생각해보자
	// 리턴 타입도 저마다 다를테니 ㅎㄷㄷ
	// 5. 4 문진상
	int GetDebrisNumber() { return m_Document[GetJsonKeyFromList(JsonKeyValues::JSON_DEBRIS_NUMBER)].GetInt(); }

private:
	static const std::string GAME_DATA_PATH;
	rapidjson::Document m_Document;
};

extern std::shared_ptr<GameData> g_GameData;