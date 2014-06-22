#pragma once
#include "DDScene.h"
class ResultScene :
	public DDScene
{
public:
	ResultScene();
	ResultScene( std::wstring sceneName );
	virtual ~ResultScene();

	CREATE_OBJECT_WSTRING( ResultScene, sceneName );

	virtual void Init();
	virtual void UpdateItSelf( float dTime );

};

