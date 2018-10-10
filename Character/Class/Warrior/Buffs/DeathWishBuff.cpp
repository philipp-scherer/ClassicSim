
#include "DeathWishBuff.h"
#include "Warrior.h"
#include "CharacterStats.h"

DeathWishBuff::DeathWishBuff(Character* pchar):
    Buff(pchar, "Death Wish", 30, 0),
    TalentRequirer(1, DisabledAtZero::Yes)
{}

void DeathWishBuff::buff_effect_when_applied() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->increase_total_phys_dmg_mod(20);
    dynamic_cast<Warrior*>(pchar)->get_stats()->add_phys_damage_taken_mod(20);
    dynamic_cast<Warrior*>(pchar)->get_stats()->add_spell_damage_taken_mod(20);
}

void DeathWishBuff::buff_effect_when_removed() {
    dynamic_cast<Warrior*>(pchar)->get_stats()->decrease_total_phys_dmg_mod(20);
    dynamic_cast<Warrior*>(pchar)->get_stats()->remove_phys_damage_taken_mod(20);
    dynamic_cast<Warrior*>(pchar)->get_stats()->remove_spell_damage_taken_mod(20);
}

void DeathWishBuff::increase_talent_rank_effect(const QString&) {
}

void DeathWishBuff::decrease_talent_rank_effect(const QString&) {
}
