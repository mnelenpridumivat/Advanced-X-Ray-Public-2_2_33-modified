#pragma once

#include "entity.h"


// Igor DEFINE_VECTOR(ref_shader, SHADER_VECTOR, SHADER_VECTOR_IT);
DEFINE_VECTOR(shared_str, STR_VECTOR, STR_VECTOR_IT);


class MONSTER_COMMUNITY;
class CEntityCondition;
class CWound;
class CCharacterPhysicsSupport;
class CMaterialManager;
class CVisualMemoryManager;
class CBlend;
class CEntityAlive : public CEntity {
private:
	typedef	CEntity			inherited;	
	u32						m_used_time;
public:
	CEntityAlive*				cast_entity_alive		() override {return this;}
public:

	bool					m_bMobility;
	float					m_fAccuracy;
	float					m_fIntelligence;
	u32						m_use_timeout;
	u8						m_squad_index;

	// EMI events (affect on electronic devices)
protected:
	xr_vector<CObject*> AffectedEmiZones = {};

public:

	IC void SetInEmi(CObject* Zone) { AffectedEmiZones.push_back(Zone); }
	IC void SetOutEmi(CObject* Zone) { AffectedEmiZones.remove(Zone); }
	IC bool IsInEmi() { return !AffectedEmiZones.empty(); }

	// end EMI events


protected:

	// Force ignore on PDA
	bool IgnoreOnPDA = false;

public:

	IC void SetIgnoreOnPDA(bool Ignore) { IgnoreOnPDA = Ignore; }
	IC bool IsIgnoreOnPDA() { return IgnoreOnPDA; }

	// end force ignore on PDA

private:
	bool					m_is_agresive;
	bool					m_is_start_attack;
	//m_PhysicMovementControl
	//CPHMovementControl		*m_PhysicMovementControl;
public:
	// General
							CEntityAlive			();
	~CEntityAlive			() override;

	// Core events
	DLL_Pure		*_construct				() override;
	void			Load					(LPCSTR section) override;
	void			reinit					() override;
	void			reload					(LPCSTR section) override;

	//object serialization
	void			save					(NET_Packet &output_packet) override;
	void			load					(IReader &input_packet) override;


	BOOL			net_Spawn				(CSE_Abstract* DC) override;
	void			net_Destroy				() override;
	BOOL			net_SaveRelevant		() override;

	void			shedule_Update			(u32 dt) override;
	void			create_anim_mov_ctrl	( CBlend *b, Fmatrix *start_pose, bool local_animation ) override;
	void			destroy_anim_mov_ctrl	( ) override;

	void			HitImpulse				(float amount, Fvector& vWorldDir, Fvector& vLocalDir) override;
	void			Hit						(SHit* pHDS) override;
	void			Die						(CObject* who) override;
	virtual void			g_WeaponBones			(int &L, int &R1, int &R2)										= 0;
			void			set_lock_corpse			(bool b_l_corpse);
			bool			is_locked_corpse		();
//	virtual float			GetfHealth				() const;
//	virtual float			SetfHealth				(float value);

//	virtual float			g_Health				()	const;
//	virtual float			g_MaxHealth				()	const;

	virtual float			g_Radiation				()	const;
	virtual	float			SetfRadiation			(float value);

	float			CalcCondition			(float hit) override;

	// Visibility related
	virtual	float			ffGetFov				()	const			= 0;	
	virtual	float			ffGetRange				()	const			= 0;	
	
	virtual bool			human_being				() const			{return	(false);}
public:
	//IC	CPHMovementControl*					PMovement					()						{return m_PhysicMovementControl;}

	u16								PHGetSyncItemsNumber		() override;
	CPHSynchronize*					PHGetSyncItem				(u16 item) override;
	void							PHUnFreeze					() override;
	void							PHFreeze					() override;

	void							PHGetLinearVell				(Fvector& velocity) override;
	CPHSoundPlayer*					ph_sound_player				() override;
	CIKLimbsController				*character_ik_controller	() override;
	ICollisionHitCallback			*get_collision_hit_callback	() override;
	void							set_collision_hit_callback	(ICollisionHitCallback *cc) override;
protected:
	DEFINE_VECTOR				(CWound*, WOUND_VECTOR, WOUND_VECTOR_IT);
	WOUND_VECTOR				m_ParticleWounds;


	virtual void				StartFireParticles(CWound* pWound);
	virtual void				UpdateFireParticles();
	virtual void				LoadFireParticles(LPCSTR section);
public:	
	static  void				UnloadFireParticles	();
protected:
	static STR_VECTOR*			m_pFireParticlesVector;
	static u32					m_dwMinBurnTime;
	static float				m_fStartBurnWoundSize;
	static float				m_fStopBurnWoundSize;


	virtual void				BloodyWallmarks			(float P, const Fvector &dir, s16 element, const Fvector& position_in_object_space);
	static  void				LoadBloodyWallmarks		(LPCSTR section);
public:	
	static  void				UnloadBloodyWallmarks	();

	void						ClearBloodWounds		() {m_BloodWounds.clear();};
protected:
	virtual void				PlaceBloodWallmark		(const Fvector& dir, const Fvector& start_pos, 
														float trace_dist, float wallmark_size,
														IWallMarkArray *pwallmarks_vector);

	//���������� � �������� �������� �� ������, ����� ��� ���� CEntityAlive
	static FactoryPtr<IWallMarkArray>	*m_pBloodMarksVector;
	static float						m_fBloodMarkSizeMax;
	static float						m_fBloodMarkSizeMin;
	static float						m_fBloodMarkDistance;
	static float						m_fNominalHit;

	//��������� ������ �����
	static FactoryPtr<IWallMarkArray>	*m_pBloodDropsVector;
	//������ ��� � ������� ������ �����
	
	DEFINE_VECTOR				(CWound*, WOUND_VECTOR, WOUND_VECTOR_IT);
	WOUND_VECTOR				m_BloodWounds;
	//������ ����, ���� ������ ������ �����
	static float				m_fStartBloodWoundSize;
	//������ ����, ���� ���������� �����
	static float				m_fStopBloodWoundSize;
	static float				m_fBloodDropSize;

	//���������� ���, � ��������� ������� �� �������� �����
	virtual void				StartBloodDrops			(CWound* pWound);
	virtual void				UpdateBloodDrops		();


	//��������� ����� ���������� � ����������� � ����
public:
	virtual	ALife::ERelationType tfGetRelationType	(const CEntityAlive *tpEntityAlive) const;
	virtual	bool				 is_relation_enemy	(const CEntityAlive *tpEntityAlive) const;	
public:	
	MONSTER_COMMUNITY*			monster_community;

private:
	CEntityCondition			*m_entity_condition;
	CMaterialManager			*m_material_manager;
	bool						b_eating;

protected:
	CEntityConditionSimple	*create_entity_condition	(CEntityConditionSimple* ec) override;

public:
	IC		CEntityCondition	&conditions					() const;
	IC		CMaterialManager	&material					() const {VERIFY(m_material_manager); return(*m_material_manager);}


protected:
	u32							m_ef_creature_type;
	u32							m_ef_weapon_type;
	u32							m_ef_detector_type;

public:
	u32					ef_creature_type			() const override;
	u32					ef_weapon_type				() const override;
	u32					ef_detector_type			() const override;

public:
	virtual	void				OnHitHealthLoss				(float NewHealth) {};	//���������� ���� entity ������ ��������
	virtual	void				OnCriticalHitHealthLoss		() {};	//���������� ���� entity ����� �� ���� 
	virtual	void				OnCriticalWoundHealthLoss	() {};	//���������� ���� entity ����� �� ������ ����� 
	virtual void				OnCriticalRadiationHealthLoss() {};	//���������� ���� entity ����� �� �������� 

	virtual	CVisualMemoryManager*visual_memory				() const {return(nullptr);}
	void				net_Relcase					(CObject *O) override;

public:
	virtual	Fvector				predict_position			(const float &time_to_check) const;
	virtual	Fvector				target_position				() const;
	IC		bool const			&is_agresive				() const;
	IC		void				is_agresive					(bool const &value);
	IC		bool const			&is_start_attack			() const;
	IC		void				is_start_attack				(bool const &value);


public:
	Fvector				get_new_local_point_on_mesh	( u16& bone_id ) const override;
	Fvector				get_last_local_point_on_mesh( Fvector const& last_point, u16 bone_id ) const override;
	void				OnChangeVisual				( ) override;

private:
			void				fill_hit_bone_surface_areas	( ) const;

private:
	typedef xr_vector< std::pair<u16,float> >	hit_bone_surface_areas_type;

private:
	mutable hit_bone_surface_areas_type	m_hit_bone_surface_areas;
	mutable CRandom						m_hit_bones_random;
	mutable bool						m_hit_bone_surface_areas_actual;
};

#include "entity_alive_inline.h"