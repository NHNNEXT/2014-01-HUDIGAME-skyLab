#include "stdafx.h"
#include "ClientObject.h"


ClientObject::ClientObject()
{
}


ClientObject::~ClientObject()
{
}

void ClientObject::AffineTransfrom()
{
	m_Matrix = m_Transform.MatrixTransform();
	DDObject::AffineTransfrom();
}
