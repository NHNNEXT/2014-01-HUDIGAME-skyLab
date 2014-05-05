#include "ISSModel.h"


ISSModel::ISSModel()
{
}

ISSModel::ISSModel( std::wstring modelPath ) : DDModel( modelPath )
{
}

ISSModel::~ISSModel()
{
}

void ISSModel::UpdateItSelf( float dTime )
{
	UNREFERENCED_PARAMETER( dTime );
}
