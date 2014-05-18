#pragma once
#include "DDModel.h"
class CompassUI :
	public DDModel
{
public:
	CompassUI();
	//CompassUI( std::wstring modelPath );
	virtual ~CompassUI();

	void Init();

	//CREATE_OBJECT_WSTRING( CompassUI, modelPath );
	CREATE_OBJECT( CompassUI );

private:
	virtual void UpdateItSelf( float dTime );
	virtual void RenderItSelf();

	LPDIRECT3DVERTEXBUFFER9 m_pVB = NULL; // Buffer to hold vertices
	LPDIRECT3DTEXTURE9      m_pTexture = NULL; // Our texture
};