#pragma once
#include "DDObject.h"

struct ID3DXFont;

class InfoPrinter : public DDObject
{
public:
	virtual~InfoPrinter();
	
	CREATE_OBJECT( InfoPrinter );

	void init();

	virtual void RenderItSelf();

	void InfoOnOff() { m_InfoOnOff = !m_InfoOnOff; };
	void UpdateInfo();

private:
	void	DrawServerInfo();
	void	DrawClientInfo();

	bool			m_InfoOnOff = false;
	ID3DXFont*		m_pFont = nullptr;
	LPRECT			m_pRect;

	ID3DXFont*		m_pCharacterStatusFont = nullptr;
	ID3DXFont*		m_pNavigationFont = nullptr;

	// 봉인. Create로 만들 것
	InfoPrinter() {};
};

extern InfoPrinter* GInfoPrinter;

