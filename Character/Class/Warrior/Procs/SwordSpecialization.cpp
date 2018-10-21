
#include "SwordSpecialization.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Weapon.h"
#include "ItemNamespace.h"
#include "ProcInfo.h"

SwordSpecialization::SwordSpecialization(Character* pchar) :
    Proc("Sword Specialization", "Assets/warrior/arms/tier5/Inv_sword_27.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing,
                                    ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing}),
         pchar),
    TalentRequirer(5, DisabledAtZero::Yes),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false;
    this->talent_ranks = {0, 1, 2, 3, 4, 5};
}

SwordSpecialization::~SwordSpecialization() = default;

void SwordSpecialization::proc_effect() {
    warr->run_extra_mh_attack();
}

void SwordSpecialization::increase_talent_rank_effect(const QString&) {
    proc_range = talent_ranks[curr_talent_rank] * 100;
}

void SwordSpecialization::decrease_talent_rank_effect(const QString&) {
    proc_range = talent_ranks[curr_talent_rank] * 100;
}

bool SwordSpecialization::proc_specific_conditions_fulfilled() const {
    if (curr_proc_source == ProcInfo::Source::MainhandSpell || curr_proc_source == ProcInfo::Source::MainhandSwing)
        return weapon_is_sword(warr->get_stats()->get_equipment()->get_mainhand());

    if (curr_proc_source == ProcInfo::Source::OffhandSpell || curr_proc_source == ProcInfo::Source::OffhandSwing)
        return weapon_is_sword(warr->get_stats()->get_equipment()->get_offhand());

    assert(false);
    return false;
}

bool SwordSpecialization::weapon_is_sword(Weapon* weapon) const {
    if (weapon == nullptr)
        return false;

    int weapon_type = weapon->get_weapon_type();

    return weapon_type == WeaponTypes::SWORD || weapon_type == WeaponTypes::TWOHAND_SWORD;
}
