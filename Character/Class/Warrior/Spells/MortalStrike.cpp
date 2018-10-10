
#include "MortalStrike.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "CooldownReady.h"
#include "Flurry.h"
#include "DeepWounds.h"
#include "OverpowerBuff.h"

MortalStrike::MortalStrike(Character* pchar) :
    Spell("Mortal Strike", pchar, true, 6.0, 30),
    TalentRequirer(1, DisabledAtZero::Yes),
    warr(dynamic_cast<Warrior*>(pchar))
{
    this->enabled = false;
}

void MortalStrike::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    add_spell_cd_event();
    add_gcd_event();

    if (result == AttackResult::MISS) {
        increment_miss();
        warr->lose_rage(static_cast<unsigned>(resource_cost));
        return;
    }
    if (result == AttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == AttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double damage_dealt = damage_after_modifiers(warr->get_random_normalized_mh_dmg() + 160);

    if (result == AttackResult::CRITICAL) {
        damage_dealt *= warr->get_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)));
    }
    else if (result == AttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)));
    }

    warr->lose_rage(static_cast<unsigned>(resource_cost));
}

void MortalStrike::increase_talent_rank_effect(const QString&) {
}

void MortalStrike::decrease_talent_rank_effect(const QString&) {
}
