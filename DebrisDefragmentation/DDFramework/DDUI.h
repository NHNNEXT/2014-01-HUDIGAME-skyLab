#pragma once
#include "DDObject.h"
class DDUI :
	public DDObject
{
public:
	DDUI();
	virtual ~DDUI();

	CREATE_OBJECT( DDUI );

	bool InitUI( std::wstring path );
	bool Cleanup();

protected:	
	ID3DXSprite* m_pUIObject = nullptr;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;

	// m_pCenter == NULL �� ��������Ʈ ���� ������ �׸��ڴٴ� �̴ϴ�
	//DDVECTOR3	m_Center{ .0f, .0f, .0f };
	// m_pRect == NULL �� ��ü �ؽ��ĸ� �� ���ڴٴ� ���Դϴ�
	//RECT		m_Rect;
	D3DCOLOR	m_Color = 0xFFFFFFFF;  // ���� ����

private :
	virtual void RenderItSelf();
};

