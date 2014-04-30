#pragma once

#include "stdafx.h"
#include "GameMacro.h"
#include "GameOption.h"


///# 헤더파일에서 stdafx.h 같은거 인클루드 웬만하면 하지마라.. 그럴 목적으로 만들어 놓은게 아님..

// ↑ client 에서 Gameconfig를 include하니 
// precompiled header를 framework것, GameLogic것 두번 인클루드해서 
// Max_player_number같은거 따로 사용하기 위해 option으로 분리해놓음.

