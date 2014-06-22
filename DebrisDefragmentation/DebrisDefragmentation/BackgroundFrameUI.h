#pragma once

#include "DDUIModule.h"
#include "GameOption.h"

struct ID3DXFont;

class BackgroundFrameUI : public DDUIModule
{
public:
	BackgroundFrameUI();
	virtual ~BackgroundFrameUI();

	bool GenerateUI();

	void Update( float dt );

private:
	TeamColor		m_DisplayTeam = TeamColor::NO_TEAM;
	CharacterClass	m_DisplayClass = CharacterClass::NO_CLASS;
	float			m_IssPosition = 0.0f;

	// text
	ID3DXFont*		m_pFont = nullptr;
	LPRECT			m_pRect;
};

