#pragma once

#include <string>		// agebreak : ���������ϵ� ����� ������
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

