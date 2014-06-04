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

	m_UIComponentList[ClientUITag::UI_OXYGEN_TAG]->GetTransform().SetScale( currentOxygen / DEFAULT_OXYGEN, 1, 1 );
	m_UIComponentList[ClientUITag::UI_FUEL_TAG]->GetTransform().SetScale( currentFuel / DEFAULT_FUEL, 1, 1 );
}