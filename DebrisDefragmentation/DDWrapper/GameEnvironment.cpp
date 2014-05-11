#include "stdafx.h"
#include "GameEnvironment.h"

namespace DDWrapper
{


	System::String^ GameEnvironment::GetJsonKey( int key )
	{
		return gcnew System::String( GetJsonKeyFromList( JsonKeyValues(key) ) );
	}

	GameEnvironment::GameEnvironment()
	{
		
	}

	GameEnvironment::~GameEnvironment()
	{

	}

};