#include "pch_script.h"
#include "flesh.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CAI_Flesh::script_register(lua_State *L)
{
	module(L)
	[
		class_<CAI_Flesh,CGameObject>("CAI_Flesh")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CAI_Flesh, CObjectScript);
