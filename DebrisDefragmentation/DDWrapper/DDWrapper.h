
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

		bool Init( INT32 hWnd, int Width, int Height );
		bool Release();

		bool Clear();
		bool BeginDraw();
		bool EndDraw();

	protected:
		DDRenderer* GetInstance();
		DDRenderer* m_pDDRenderer;
		// TODO: ���⿡ �� Ŭ������ ���� �޼��带 �߰��մϴ�.
	};
}
