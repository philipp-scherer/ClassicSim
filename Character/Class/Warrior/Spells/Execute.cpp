
#include "Execute.h"
#include "Warrior.h"
#include "Flurry.h"
#include "DeepWounds.h"

Execute::Execute(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Execute", engine, pchar, roll, 0, 10)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
    spell_ranks = {600};
    talent_ranks = {15, 12, 10};
}

int Execute::spell_effect(const int resource_level) {
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
    }

    int damage_dealt = spell_ranks[rank_spell];
    damage_dealt += (resource_level - talent_ranks[rank_talent - 1]) * resource_level;

    if (result->is_critical()) {
        // TODO: Remove hardcoding of 2/2 Impale.
        damage_dealt *= 2.2;
        pchar->critical_effect();
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    add_gcd_event();

    return resource_level;
}
