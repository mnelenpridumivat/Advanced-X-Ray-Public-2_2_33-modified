////////////////////////////////////////////////////////////////////////////
//	Module 		: smart_cover_planner_target_provider.h
//	Created 	: 18.09.2007
//	Author		: Alexander Dudin
//	Description : Target provider for target selector
////////////////////////////////////////////////////////////////////////////

#ifndef SMART_COVER_PLANNER_TARGET_PROVIDER_H_INCLUDED
#define SMART_COVER_PLANNER_TARGET_PROVIDER_H_INCLUDED

#include <boost/noncopyable.hpp>
#include "smart_cover_detail.h"
#include "action_base.h"
#include "smart_cover_planner_target_selector.h"
#include "stalker_decision_space.h"

namespace smart_cover {

class target_provider : 
	public	CActionBase<animation_planner>,
	private boost::noncopyable
{
private:
	typedef CActionBase<animation_planner> inherited;

public:
						target_provider					(animation_planner *object, LPCSTR name, StalkerDecisionSpace::EWorldProperties const &world_property, u32 const &loophole_value);
	void		setup							(animation_planner *object, CPropertyStorage *storage) override;
	void		initialize						() override;
	void		finalize						() override;

private:
	StalkerDecisionSpace::EWorldProperties m_world_property;
	u32					m_loophole_value;
};

////////////////////////////////////////////////////////////////////////////
//	class target_idle
////////////////////////////////////////////////////////////////////////////

class target_idle final :
	public target_provider
{
private:
	typedef target_provider inherited;

public:
						target_idle						(animation_planner *object, LPCSTR name, StalkerDecisionSpace::EWorldProperties const &world_property, u32 const &loophole_value);
	void		execute							() override;
};

////////////////////////////////////////////////////////////////////////////
//	class target_fire
////////////////////////////////////////////////////////////////////////////

class target_fire final : public target_provider
{
private:
	typedef target_provider inherited;

public:
						target_fire						(animation_planner *object, LPCSTR name, StalkerDecisionSpace::EWorldProperties const &world_property, u32 const &loophole_value);
	void		initialize						() override;
	void		execute							() override;
};

////////////////////////////////////////////////////////////////////////////
//	class target_fire_no_lookout
////////////////////////////////////////////////////////////////////////////

class target_fire_no_lookout final : public target_provider
{
private:
	typedef target_provider inherited;

public:
						target_fire_no_lookout			(animation_planner *object, LPCSTR name, StalkerDecisionSpace::EWorldProperties const &world_property, u32 const &loophole_value);
	void		initialize						() override;
	~target_fire_no_lookout() override {}

private:
	StalkerDecisionSpace::EWorldProperties m_world_property;
	u32					m_loophole_value;
};

} // namespace smart_cover

#endif // SMART_COVER_PLANNER_TARGET_PROVIDER_H_INCLUDED