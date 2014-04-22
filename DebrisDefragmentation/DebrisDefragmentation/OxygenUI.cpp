#include "OxygenUI.h"


OxygenUI::OxygenUI()
{
}


OxygenUI::~OxygenUI()
{
}

void OxygenUI::init()
{
	std::wstring filePath = L".\\Resources\\Image\\OxygenUI.bmp";
	Init( filePath, 25, 25 );
}
