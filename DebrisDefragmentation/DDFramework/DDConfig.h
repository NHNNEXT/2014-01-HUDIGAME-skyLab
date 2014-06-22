#pragma once 

#include "d3dx9.h"
#include <unordered_map>
#include <memory>
#include <windows.h>
#include <list>

typedef		D3DXVECTOR3		DDVECTOR3;


// 사용자 정의 윈도우즈 메시지
// 조심해! 프레임워크에 넣어도 될런지!
#define SL_LOADINGSCENE_LOADING_START	WM_USER + 1
#define SL_PLAYSCENE_LOADING_COMPLETE	WM_USER + 2
#define SL_PLASCENE_GAME_END			WM_USER + 3