#include "stdafx.h"
#include "PHDestroyableNotificate.h"
#include "alife_space.h"
#include "hit.h"
#include "PHDestroyable.h"
#include "Level.h"
#include "xrServer_Object_Base.h"
#include "../xrEngine/xr_object.h"
#include "PhysicsShellHolder.h"
#include "xrServer_Objects.h"
void CPHDestroyableNotificate::spawn_notificate(CSE_Abstract* so)
{
	CPHDestroyableNotificator* D	= nullptr;
	CSE_PHSkeleton			 * po	=smart_cast<CSE_PHSkeleton*>(so);
	u16						 id		=static_cast<u16>(-1);
	if(po)
							id		=po->get_source_id();
	if(id!=static_cast<u16>(-1))
		D= smart_cast<CPHDestroyableNotificator*>(Level().Objects.net_Find(id));
	if(D)
		D->NotificateDestroy(this);
	po->source_id=BI_NONE;
}
