#pragma once
#include "GameObject.h"

namespace DDWrapper
{

	public ref class GameLight : public GameObject
	{
	public:
		GameLight();
		~GameLight();

	protected:
		ClientObject* Create() { return new ClientObject(); };
	};
}