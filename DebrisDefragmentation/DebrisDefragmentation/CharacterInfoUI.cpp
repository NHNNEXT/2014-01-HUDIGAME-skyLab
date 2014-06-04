#include "stdafx.h"
#include "CharacterInfoUI.h"
#include "PlayerManager.h"

CharacterInfoUI::CharacterInfoUI()
{
}


CharacterInfoUI::~CharacterInfoUI()
{
}

bool CharacterInfoUI::GenerateUI()
{
	// 하나씩 만들어서 m_UIComponentList에 추가한다.
	MakeUIComponent( ClientUITag::UI_OXYGEN_TAG );
	MakeUIComponent( ClientUITag::UI_FUEL_TAG );

	return true;
}

void CharacterInfoUI::Update( float dt )
{
	Player* myPlayer = GPlayerManager->GetMyPlayer();

	if ( !myPlayer )
		return;

	float currentOxygen = myPlayer->GetOxygen();
	float currentFuel = myPlayer->GetGas();

	// 조심해!
	// 여백도 스케일 적용이 되는 문제 있음
	m_UIComponentList[ClientUITag::UI_OXYGEN_TAG]->GetTransform().SetScale( currentOxygen / DEFAULT_OXYGEN, 1, 1 );
	m_UIComponentList[ClientUITag::UI_OXYGEN_TAG]->GetTransform().SetPosition( UI_OXYGEN_POSITION_X, UI_OXYGEN_POSITION_Y, 0.0f );
	m_UIComponentList[ClientUITag::UI_FUEL_TAG]->GetTransform().SetScale( currentFuel / DEFAULT_FUEL, 1, 1 );
	m_UIComponentList[ClientUITag::UI_FUEL_TAG]->GetTransform().SetPosition( UI_FUEL_POSITION_X, UI_FUEL_POSITION_Y, 0.0f );
}