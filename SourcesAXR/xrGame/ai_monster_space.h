////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_monster_space.h
//	Created 	: 06.10.2003
//  Modified 	: 06.10.2003
//	Author		: Dmitriy Iassenev
//	Description : Monster types and structures
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "xrserver_space.h"

namespace MonsterSpace {
	enum EMentalState {
		eMentalStateDanger = static_cast<u32>(0),
		eMentalStateFree,
		eMentalStatePanic,
	};

	enum EBodyState {
		eBodyStateCrouch = static_cast<u32>(0),
		eBodyStateStand,
		eBodyStateDummy = static_cast<u32>(-1)
	};

	enum EMovementType {
		eMovementTypeWalk = 0,
		eMovementTypeRun,
		eMovementTypeStand,
	};

	enum EMovementDirection {
		eMovementDirectionForward = 0,
		eMovementDirectionBackward,
		eMovementDirectionLeft,
		eMovementDirectionRight,
	};

	enum EObjectAction {
		eObjectActionSwitch1,
		eObjectActionSwitch2,
		eObjectActionReload1,
		eObjectActionReload2,
		eObjectActionAim1,
		eObjectActionAim2,
		eObjectActionFire1,
		eObjectActionFireNoReload,
		eObjectActionFire2,
		eObjectActionIdle,
		eObjectActionStrapped,
		eObjectActionDrop,
		eObjectActionAimReady1,
		eObjectActionAimReady2,
		eObjectActionAimForceFull1,
		eObjectActionAimForceFull2,
		// for scripts only
		eObjectActionActivate,
		eObjectActionDeactivate,
		eObjectActionUse,
		eObjectActionTurnOn,
		eObjectActionTurnOff,
		// for old object handler only
		eObjectActionShow,
		eObjectActionHide,
		eObjectActionTake,
		eObjectActionMisfire1,
		eObjectActionEmpty1,
		eObjectActionNoItems		= eObjectActionIdle | static_cast<u16>(-1),
		// 
		eObjectActionDummy			= static_cast<u32>(-1),
	};

	struct SBoneRotation {
		SRotation		current;
		SRotation		target;
		float			speed;
	};

	enum EScriptMonsterMoveAction {
		eMA_WalkFwd,
		eMA_WalkBkwd,
		eMA_Run,
		eMA_Drag,
		eMA_Jump,
		eMA_Steal,
		eMA_WalkWithLeader,
		eMA_RunWithLeader
	};
	
	enum EScriptMonsterSpeedParam {
		eSP_Default				= static_cast<u32>(0),
		eSP_ForceSpeed,	
		eSP_None				= static_cast<u32>(-1),
	};

	enum EScriptMonsterAnimAction {
		eAA_StandIdle,
		eAA_CapturePrepare,
		eAA_SitIdle,			
		eAA_LieIdle,			
		eAA_Eat,				
		eAA_Sleep,				
		eAA_Rest,				
		eAA_Attack,				
		eAA_LookAround,
		eAA_Turn,
		eAA_NoAction			= static_cast<u32>(-1)
	};

	enum EScriptMonsterGlobalAction {
		eGA_Rest				= static_cast<u32>(0),
		eGA_Eat,
		eGA_Attack,
		eGA_Panic,
		eGA_None				= static_cast<u32>(-1)
	};

	enum EScriptSoundAnim {
		eAnimSoundCustom		= static_cast<u32>(0),
		eAnimSoundDefault,
	};

	enum EMonsterHeadAnimType {
		eHeadAnimNormal			= static_cast<u32>(0),
		eHeadAnimAngry,
		eHeadAnimGlad,
		eHeadAnimKind,

		eHeadAnimNone			= static_cast<u32>(-1),
	};
};
