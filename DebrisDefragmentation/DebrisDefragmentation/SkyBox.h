#pragma once
#include "DDModel.h"
class SkyBox :
	public DDModel
{
public:
	SkyBox();
	//SkyBox( std::wstring modelPath );
	virtual ~SkyBox();

	//CREATE_OBJECT_WSTRING( SkyBox, modelpath );
	CREATE_OBJECT( SkyBox );

	// 아직까진 스카이박스에서 업뎃할 것이 없습니다
	virtual void UpdateItSelf( float dTime ) { UNREFERENCED_PARAMETER( dTime ); }
};

