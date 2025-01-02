#pragma once
#define _CRTDBG_MAP_ALLOC
#define GetKey(X) CKeyMgr::GetInst()->GetKeyState(X) == KEY_STATE::TAP