
// DDWrapper.h
// warning!! 만약 lib가 출력되는 폴더가 바뀌면 아래 옵션도 바꿔야 한다
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
		// TODO: 여기에 이 클래스에 대한 메서드를 추가합니다.
	};
}
