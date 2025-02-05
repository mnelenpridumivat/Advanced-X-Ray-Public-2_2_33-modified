#include "pch_script.h"
#include "burer.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CBurer::script_register(lua_State *L)
{
	module(L)
	[
		class_<CBurer,CGameObject>("CBurer")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CBurer, CObjectScript);
