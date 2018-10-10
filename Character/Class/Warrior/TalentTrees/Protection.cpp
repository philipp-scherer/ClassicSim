
#include "Protection.h"
#include "Talent.h"
#include "GenericTalent.h"
#include <QDebug>

Protection::Protection(Character *pchar, QObject* parent) :
    TalentTree("Protection", "Assets/warrior/warrior_protection.jpg", parent)
{
    QString base_url = "Assets/warrior/protection/";

    QMap<QString, Talent*> tier1 {{"1ML", new GenericTalent(pchar, this, "Shield Specialization", "1ML", base_url + "tier1/Inv_shield_06.png", 5, "Increases your chance to block attacks with a shield by %1% and has a %2% chance to generate 1 rage when a block occurs.", QVector<QPair<int, int>>{QPair<int, int>(1, 1), QPair<int, int>(20, 20)})},
                                  {"1MR", new GenericTalent(pchar, this, "Anticipation", "1MR", base_url + "tier1/Spell_nature_mirrorimage.png", 5, "Increases your Defense skill by %1.", QVector<QPair<int, int>>{QPair<int, int>(2, 2)})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new GenericTalent(pchar, this, "Improved Bloodrage", "2LL", base_url + "tier2/Ability_racial_bloodrage.png", 2, "Increases the instant Rage generated by your Bloodrage ability by %1.", QVector<QPair<int, int>>{QPair<int, int>(2, 3)})},
                                  {"2MR", new GenericTalent(pchar, this, "Toughness", "2MR", base_url + "tier2/Spell_holy_devotion.png", 5, "Increases your armor value from items by %1%.", QVector<QPair<int, int>>{QPair<int, int>(2, 2)})},
                                  {"2RR", new GenericTalent(pchar, this, "Iron Will", "2RR", base_url + "tier2/Spell_magic_magearmor.png", 5, "Increases your chance to resist Stun and Charm effects by an additional %1%.", QVector<QPair<int, int>>{QPair<int, int>(3, 3)})}};
    add_talents(tier2);

    // TODO: Improved Shield Block has a non-linear increase (r1 to r2 gives 0.5, while r2 to r3 gives 1)
    QMap<QString, Talent*> tier3 {{"3LL", new GenericTalent(pchar, this, "Last Stand", "3LL", base_url + "tier3/Spell_holy_ashestoashes.png", 1, "When activated, this ability temporarily grants you 30% of your maximum hit points for 20 seconds. After the effect expires, the hit points are lost.", QVector<QPair<int, int>>())},
                                  {"3ML", new GenericTalent(pchar, this, "Improved Shield Block", "3ML", base_url + "tier3/Ability_defend.png", 3, "Allows your Shield Block ability to block an additional attack and increases the duration by %1 seconds.", QVector<QPair<int, int>>{QPair<int, int>(1, 1)})},
                                  {"3MR", new GenericTalent(pchar, this, "Improved Revenge", "3MR", base_url + "tier3/Ability_warrior_revenge.png", 3, "Gives your Revenge ability a %1% chance to stun the target for 3 sec.", QVector<QPair<int, int>>{QPair<int, int>(15, 15)})},
                                  {"3RR", new GenericTalent(pchar, this, "Defiance", "3RR", base_url + "tier3/Ability_warrior_innerrage.png", 5, "Increases the threat generated by your attacks by %1% while in Defensive Stance.", QVector<QPair<int, int>>{QPair<int, int>(3, 3)})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new GenericTalent(pchar, this, "Improved Sunder Armor", "4LL", base_url + "tier4/Ability_warrior_sunder.png", 3, "Reduces the cost of your Sunder Armor ability by %1 rage.", QVector<QPair<int, int>>{QPair<int, int>(1, 1)})},
                                  {"4ML", new GenericTalent(pchar, this, "Improved Disarm", "4ML", base_url + "tier4/Ability_warrior_disarm.png", 3, "Increases the duration of your Disarm ability by %1 secs.", QVector<QPair<int, int>>{QPair<int, int>(1, 1)})},
                                  {"4MR", new GenericTalent(pchar, this, "Improved Taunt", "4MR", base_url + "tier4/Spell_nature_reincarnation.png", 2, "Reduces the cooldown of your Taunt ability by %1 secs.", QVector<QPair<int, int>>{QPair<int, int>(1, 1)})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new GenericTalent(pchar, this, "Improved Shield Wall", "5LL", base_url + "tier5/Ability_warrior_shieldwall.png", 2, "Increases the effect duration of your Shield Wall ability by %1 secs.", QVector<QPair<int, int>>{QPair<int, int>(3, 2)})},
                                  {"5ML", new GenericTalent(pchar, this, "Concussion Blow", "5ML", base_url + "tier5/Ability_thunderbolt.png", 1, "Stuns the opponent for 5 sec.", QVector<QPair<int, int>>())},
                                  {"5MR", new GenericTalent(pchar, this, "Improved Shield Bash", "5MR", base_url + "tier5/Ability_warrior_shieldbash.png", 2, "Gives your Shield Bash ability a %1% chance to silence the target for 3 sec.", QVector<QPair<int, int>>{QPair<int, int>(50, 50)})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new GenericTalent(pchar, this, "One-Handed Weapon Specialization", "6MR", base_url + "tier6/Inv_sword_20.png", 5, "Increases the damage you deal with One-Handed Melee weapons by %1%.", QVector<QPair<int, int>>{QPair<int, int>(2, 2)})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new GenericTalent(pchar, this, "Shield Slam", "7ML", base_url + "tier7/Inv_shield_05.png", 1, "Slam the target with your shield, causing 225 to 236 damage, modified by your shield block value, and has a 50% chance of dispelling 1 magic effect on the target. Also causes a high amount of threat.", QVector<QPair<int, int>>())}};
    add_talents(tier7);

    talents["1ML"]->talent->set_bottom_child(talents["3ML"]->talent);
    talents["3ML"]->talent->set_parent(talents["1ML"]->talent);

    talents["2LL"]->talent->set_bottom_child(talents["3LL"]->talent);
    talents["3LL"]->talent->set_parent(talents["2LL"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

Protection::~Protection() = default;
