#pragma once
#include "GameOption.h"

namespace DDWrapper
{
	// GameOption의 const 변수들을 참조하기 위한 클래스
	public ref class GameEnvironment
	{
	public:
		GameEnvironment();
		~GameEnvironment();

		// 주의 : int로 선언해놨지만 JsonENUM으로 넘겨줘야합니다
		System::String^ GetJsonKey( int key );

	};
};