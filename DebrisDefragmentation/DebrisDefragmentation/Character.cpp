#include "Character.h"
#include "DDRenderer.h"


Character::Character()
{
}

Character::Character( wchar_t* modelPath )
{
//	DDModel::DDModel( modelPath );
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
