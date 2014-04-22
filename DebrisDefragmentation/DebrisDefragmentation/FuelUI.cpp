#include "FuelUI.h"


FuelUI::FuelUI()
{
}


FuelUI::~FuelUI()
{
}

void FuelUI::init()
{
	std::wstring filePath = L".\\Resources\\Image\\FuelUI.bmp";
	Init( filePath, 25, 75 );
}
