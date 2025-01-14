﻿#include "stdafx.h"
#include "pch_script.h"
#include "ActorCondition.h"
#include "Wound.h"

#pragma optimize("s",on)
void CEntityCondition::script_register(lua_State* L)
{
    using namespace luabind;

    module(L)
    [
        class_<CEntityCondition>("CEntityCondition")
            .def("AddWound",                    &CEntityCondition::AddWound)
            .def("ClearWounds",                 &CEntityCondition::ClearWounds)
            .def("GetWhoHitLastTimeID",         &CEntityCondition::GetWhoHitLastTimeID)
            .def("GetPower",                    &CEntityCondition::GetPower)
            .def("SetPower",                    &CEntityCondition::SetPower)
            .def("GetRadiation",                &CEntityCondition::GetRadiation)
            .def("GetPsyHealth",                &CEntityCondition::GetPsyHealth)
            .def("GetSatiety",                  &CEntityCondition::GetSatiety)
            .def("GetEntityMorale",             &CEntityCondition::GetEntityMorale)
            .def("GetHealthLost",               &CEntityCondition::GetHealthLost)
            .def("IsLimping",                   &CEntityCondition::IsLimping)
            .def("ChangeSatiety",               &CEntityCondition::ChangeSatiety)
            .def("ChangeHealth",                &CEntityCondition::ChangeHealth)
            .def("ChangePower",                 &CEntityCondition::ChangePower)
            .def("ChangeRadiation",             &CEntityCondition::ChangeRadiation)
            .def("ChangePsyHealth",             &CEntityCondition::ChangePsyHealth)
            .def("ChangeAlcohol",               &CEntityCondition::ChangeAlcohol)
            .def("SetMaxPower",                 &CEntityCondition::SetMaxPower)
            .def("GetMaxPower",                 &CEntityCondition::GetMaxPower)
            .def("ChangeEntityMorale",          &CEntityCondition::ChangeEntityMorale)
            .def("ChangeBleeding",              &CEntityCondition::ChangeBleeding)
            .def("BleedingSpeed",               &CEntityCondition::BleedingSpeed)
            .enum_("EBoostParams")
            [
                value("eBoostHpRestore",                int(EBoostParams::eBoostHpRestore)),
                value("eBoostPowerRestore",             int(EBoostParams::eBoostPowerRestore)),
                value("eBoostRadiationRestore",         int(EBoostParams::eBoostRadiationRestore)),
                value("eBoostBleedingRestore",          int(EBoostParams::eBoostBleedingRestore)),
                value("eBoostMaxWeight",                int(EBoostParams::eBoostMaxWeight)),
                value("eBoostRadiationProtection",      int(EBoostParams::eBoostRadiationProtection)),
                value("eBoostTelepaticProtection",      int(EBoostParams::eBoostTelepaticProtection)),
                value("eBoostChemicalBurnProtection",   int(EBoostParams::eBoostChemicalBurnProtection)),
                value("eBoostBurnImmunity",             int(EBoostParams::eBoostBurnImmunity)),
                value("eBoostShockImmunity",            int(EBoostParams::eBoostShockImmunity)),
                value("eBoostRadiationImmunity",        int(EBoostParams::eBoostRadiationImmunity)),
                value("eBoostTelepaticImmunity",        int(EBoostParams::eBoostTelepaticImmunity)),
                value("eBoostChemicalBurnImmunity",     int(EBoostParams::eBoostChemicalBurnImmunity)),
                value("eBoostExplImmunity",             int(EBoostParams::eBoostExplImmunity)),
                value("eBoostStrikeImmunity",           int(EBoostParams::eBoostStrikeImmunity)),
                value("eBoostFireWoundImmunity",        int(EBoostParams::eBoostFireWoundImmunity)),
                value("eBoostWoundImmunity",            int(EBoostParams::eBoostWoundImmunity)),

                value("eBoostSatietyRestore",           int(EBoostParams::eBoostSatietyRestore)),
                value("eBoostThirstRestore",            int(EBoostParams::eBoostThirstRestore)),
                value("eBoostPsyHealthRestore",         int(EBoostParams::eBoostPsyHealthRestore)),
                value("eBoostIntoxicationRestore",      int(EBoostParams::eBoostIntoxicationRestore)),
                value("eBoostSleepenessRestore",        int(EBoostParams::eBoostSleepenessRestore)),
                value("eBoostAlcoholRestore",           int(EBoostParams::eBoostAlcoholRestore)),
                value("eBoostAlcoholismRestore",        int(EBoostParams::eBoostAlcoholismRestore)),
                value("eBoostHangoverRestore",          int(EBoostParams::eBoostHangoverRestore)),
                value("eBoostDrugsRestore",             int(EBoostParams::eBoostDrugsRestore)),
                value("eBoostNarcotismRestore",         int(EBoostParams::eBoostNarcotismRestore)),
                value("eBoostWithdrawalRestore",        int(EBoostParams::eBoostWithdrawalRestore)),
                value("eBoostTimeFactor",               int(EBoostParams::eBoostTimeFactor))
            ]
    ];
};

SCRIPT_EXPORT1(CEntityCondition);

void CActorCondition::script_register(lua_State* L)
{
    using namespace luabind;

    module(L)
    [
        class_<SBooster>("SBooster")
            .def(constructor<>())
            .def_readwrite("fBoostTime",        &SBooster::fBoostTime)
            .def_readwrite("fBoostValue",       &SBooster::fBoostValue)
            .def_readwrite("m_type",            &SBooster::m_type)
            .def_readwrite("m_booster_type",    &SBooster::m_booster_type)
            .enum_("EBoostType")
            [
                value("eBoostTypeMedkit", int(EBoostType::eBoostTypeMedkit)),
                value("eBoostTypeSyringe", int(EBoostType::eBoostTypeSyringe)),
                value("eBoostTypePills", int(EBoostType::eBoostTypePills)),
                value("eBoostTypeLiquid", int(EBoostType::eBoostTypeLiquid)),
                value("eBoostTypePhysical", int(EBoostType::eBoostTypePhysical))
            ],

        class_<CWound>("CWound")
            .def("TypeSize",                    &CWound::TypeSize)
            .def("BloodSize",                   &CWound::BloodSize)
            .def("AddHit",                      &CWound::AddHit)
            .def("Incarnation",                 &CWound::Incarnation)
            .def("TotalSize",                   &CWound::TotalSize)
            .def("SetBoneNum",                  &CWound::SetBoneNum)
            .def("GetBoneNum",                  &CWound::GetBoneNum)
            .def("GetParticleBoneNum",          &CWound::GetParticleBoneNum)
            .def("SetParticleBoneNum",          &CWound::SetParticleBoneNum)
            .def("SetDestroy",                  &CWound::SetDestroy)
            .def("GetDestroy",                  &CWound::GetDestroy),

        class_<CActorCondition, CEntityCondition>("CActorCondition")
            .def("ClearAllBoosters",            &CActorCondition::ClearAllBoosters)
            .def("ApplyBooster",                &CActorCondition::ApplyBooster_script)
            .def("BoosterForEach",              &CActorCondition::BoosterForEach)
            .def("WoundForEach",                &CActorCondition::WoundForEach)
            .def("GetSatiety",                  &CActorCondition::GetSatiety)
            .def("BoostMaxWeight",              &CActorCondition::BoostMaxWeight)
            .def("BoostHpRestore",              &CActorCondition::BoostHpRestore)
            .def("BoostPowerRestore",           &CActorCondition::BoostPowerRestore)
            .def("BoostRadiationRestore",       &CActorCondition::BoostRadiationRestore)
            .def("BoostBleedingRestore",        &CActorCondition::BoostBleedingRestore)
            .def("BoostBurnImmunity",           &CActorCondition::BoostBurnImmunity)
            .def("BoostShockImmunity",          &CActorCondition::BoostShockImmunity)
            .def("BoostRadiationImmunity",      &CActorCondition::BoostRadiationImmunity)
            .def("BoostTelepaticImmunity",      &CActorCondition::BoostTelepaticImmunity)
            .def("BoostChemicalBurnImmunity",   &CActorCondition::BoostChemicalBurnImmunity)
            .def("BoostExplImmunity",           &CActorCondition::BoostExplImmunity)
            .def("BoostStrikeImmunity",         &CActorCondition::BoostStrikeImmunity)
            .def("BoostFireWoundImmunity",      &CActorCondition::BoostFireWoundImmunity)
            .def("BoostWoundImmunity",          &CActorCondition::BoostWoundImmunity)
            .def("BoostRadiationProtection",    &CActorCondition::BoostRadiationProtection)
            .def("BoostTelepaticProtection",    &CActorCondition::BoostTelepaticProtection)
            .def("BoostChemicalBurnProtection", &CActorCondition::BoostChemicalBurnProtection)
            .def("BoostSatietyRestore",         &CActorCondition::BoostSatietyRestore)
            .def("BoostThirstRestore",          &CActorCondition::BoostThirstRestore)
            .def("BoostPsyHealthRestore",       &CActorCondition::BoostPsyHealthRestore)
            .def("BoostIntoxicationRestore",    &CActorCondition::BoostIntoxicationRestore)
            .def("BoostSleepenessRestore",      &CActorCondition::BoostSleepenessRestore)
            .def("BoostAlcoholRestore",         &CActorCondition::BoostAlcoholRestore)
            .def("BoostAlcoholismRestore",      &CActorCondition::BoostAlcoholismRestore)
            .def("BoostHangoverRestore",        &CActorCondition::BoostHangoverRestore)
            .def("BoostDrugsRestore",           &CActorCondition::BoostDrugsRestore)
            .def("BoostNarcotismRestore",       &CActorCondition::BoostNarcotismRestore)
            .def("BoostWithdrawalRestore",      &CActorCondition::BoostWithdrawalRestore)
            .def("BoostTimeFactor",             &CActorCondition::BoostTimeFactor)
            .def("IsLimping",                   &CActorCondition::IsLimping)
            .def("IsCantWalk",                  &CActorCondition::IsCantWalk)
            .def("IsCantWalkWeight",            &CActorCondition::IsCantWalkWeight)
            .def("IsCantSprint",                &CActorCondition::IsCantSprint)
            .def_readwrite("m_MaxWalkWeight",   &CActorCondition::m_MaxWalkWeight)
    ];
};

SCRIPT_EXPORT2(CActorCondition, CEntityCondition);