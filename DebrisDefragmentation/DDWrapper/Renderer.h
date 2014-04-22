#pragma once
#include "DDWrapper.h"

namespace DDWrapper
{
	public ref class Renderer
	{
	public:
		Renderer();
		~Renderer();

		DDRenderer* GetInstance();

		bool Init( INT32 hWnd, int Width, int Height ) { return m_pDDRenderer->Init( reinterpret_cast<HWND>( hWnd ), Width, Height ); };
		bool Release() { return m_pDDRenderer->Release(); };

		bool Clear() { return m_pDDRenderer->Clear(); };
		bool BeginDraw() { return m_pDDRenderer->Begin(); };
		bool EndDraw() { return m_pDDRenderer->End(); };

		LPDIRECT3DDEVICE9 GetDevice() { return m_pDDRenderer->GetDevice(); };

	protected:
		DDRenderer* m_pDDRenderer;
	};
}