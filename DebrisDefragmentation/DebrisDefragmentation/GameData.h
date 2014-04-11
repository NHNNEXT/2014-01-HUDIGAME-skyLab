#pragma once

#include <string>		// agebreak : 프리컴파일드 헤더에 넣을것
#include "DDResourceManager.h"

class GameData
{
public:
	GameData();
	~GameData();

	bool Init();

	const std::string GetTestString();

private:
	static const std::wstring GAME_DATA_PATH;
	rapidjson::Document m_Document;
};

