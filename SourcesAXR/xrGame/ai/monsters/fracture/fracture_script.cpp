#include "pch_script.h"
#include "fracture.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CFracture::script_register(lua_State *L)
{
	module(L)
	[
		class_<CFracture,CGameObject>("CFracture")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CFracture, CObjectScript);
