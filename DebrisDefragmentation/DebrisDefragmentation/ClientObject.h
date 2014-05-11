#pragma once
#include "DDObject.h"
#include "Transform.h"

class ClientObject :
	public DDObject
{
public:
	ClientObject();
	virtual ~ClientObject();

	Transform& GetTransform() { return m_Transform; }

protected:
	void AffineTransfrom();
	Transform m_Transform;
};

