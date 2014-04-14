#include "stdafx.h"
#include "Character.h"
#include "DDRenderer.h"
#include "DDApplication.h"


Character::Character()
{
	tmpTimeCounter = 0;
}

Character::Character( wchar_t* modelPath )
{
	m_pD3DDevice = DDApplication::GetInstance()->GetRenderer()->GetDevice();
	initModel( modelPath );
	SetNormalVector();
}


Character::~Character()
{
}

Character* Character::Create( wchar_t* modelPath )
{
	Character* pInstance = new Character( modelPath );
	return pInstance;
}

void Character::UpdateItSelf( float dTime )
{
	// player, playscene, character class�� update �� updateitself �Լ� �������.
	// ������ �Ź� ��ӹ޴� Ŭ�������� update �Լ��� ���Ͱ��� �������� �Ѵٴ� ��.(invisible�̸� return�ϴ� �κе� �߰��ؾ���..)
	// ����� �÷��̾� �ؿ� ī�޶�, Ÿ�̰� �ִµ� �� ĳ���� �Լ����� ȣ���̸� ������ �����̴� ��.
	// ** ���߿� tmp ���� ������ �� ������ ��.
	//tmpTimeCounter += dTime;
	//m_Position = D3DXVECTOR3( 0.0f, 0.0f, tmpTimeCounter );
	
	// increasePosition test
	//IncreasePositionX( tmpTimeCounter );
	UNREFERENCED_PARAMETER(dTime);
}
