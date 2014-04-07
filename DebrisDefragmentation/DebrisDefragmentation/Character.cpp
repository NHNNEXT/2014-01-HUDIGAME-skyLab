#include "Character.h"
#include "DDRenderer.h"


Character::Character()
{
	tmpTimeCounter = 0;
}

Character::Character( wchar_t* modelPath )
{
	m_pD3DDevice = DDRenderer::GetInstance()->GetDevice();
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

void Character::Update( float dTime )
{
	UpdateItSelf( dTime );
	UpdateChildNodes( dTime );
}

void Character::UpdateItSelf( float dTime )
{
	// player, playscene, character class에 update 및 updateitself 함수 만들었음.
	// 문제는 매번 상속받는 클래스마다 update 함수를 위와같이 만들어줘야 한다는 것.(invisible이면 return하는 부분도 추가해야함..)
	// 현재는 플레이어 밑에 카메라, 타이거 있는데 이 캐릭터 함수에서 호랑이만 앞으로 움직이는 중.
	// ** 나중에 tmp 관련 변수들 다 삭제할 것.
	//tmpTimeCounter += dTime;
	//m_Position = D3DXVECTOR3( 0.0f, 0.0f, tmpTimeCounter );
	
	// increasePosition test
	//IncreasePositionX( tmpTimeCounter );
}
