#pragma once
#include "ClassComponent.h"
namespace DDWrapper
{
	ref class Logic
	{
	public:
		Logic();
		~Logic();

	private:
		ClassComponent* m_ClassComponent;
	};
}
