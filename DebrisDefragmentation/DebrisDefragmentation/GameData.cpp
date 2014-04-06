#include "GameData.h"
#include <cstdio>
#include <fstream>

using namespace rapidjson;

const std::wstring GameData::GAME_DATA_PATH = L"game_data.json";

GameData::GameData()
{
}


GameData::~GameData()
{
}

bool GameData::Init()
{
	std::ifstream srcFile( GAME_DATA_PATH.c_str() );
	std::string json( std::istreambuf_iterator<char>( srcFile ), ( std::istreambuf_iterator<char>() ) );

	m_Document.Parse<0>( json.c_str() );

	return true;
}

const std::string GameData::GetTestString()
{
	return m_Document[SizeType( 0 )].GetString();
}