
// DDWrapper.h
// warning!! ���� lib�� ��µǴ� ������ �ٲ�� �Ʒ� �ɼǵ� �ٲ�� �Ѵ�
#include "../DDFramework/DDRenderer.h"
#pragma comment( lib, "../Debug/DDFramework.lib")

using namespace System;

namespace DDWrapper {

	public ref class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();

		DDRenderer* GetInstance();

	protected:
		DDRenderer* m_pDDRenderer;
		// TODO: ���⿡ �� Ŭ������ ���� �޼��带 �߰��մϴ�.
	};
}
