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

	void RenderDebuggingInfo();
	void InfoOnOff() { m_InfoOnOff = !m_InfoOnOff; };
	void UpdateInfo();

private:
	bool			m_InfoOnOff = false;
	ID3DXFont*		m_pFont = nullptr;
	LPRECT*			m_pRect;

	// 봉인. Create로 만들 것
	InfoPrinter() {};
};

extern InfoPrinter* GInfoPrinter;

