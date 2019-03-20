#ifndef MELEEWHITEHITTABLE_H
#define MELEEWHITEHITTABLE_H

#include "PhysicalAttackResult.h"

class Random;

class MeleeWhiteHitTable {
public:
    MeleeWhiteHitTable(Random* random,
                  const int wpn_skill,
                  const double miss,
                  const double dodge,
                  const double parry,
                  const double glancing,
                  const double block);

    int get_outcome(const unsigned roll,
                    const double crit_chance,
                    const bool include_dodge = true,
                    const bool include_parry = true,
                    const bool include_block = true,
                    const bool include_miss = true);

    void update_miss_chance(const double miss);
    void update_dodge_chance(const double dodge);
    void update_parry_chance(const double parry);
    void update_glancing_chance(const double glancing);
    void update_block_chance(const double block);

    int get_wpn_skill();

    void update_ranges();

private:
    Random* random;
    const int wpn_skill;

    double miss;
    double dodge;
    double parry;
    double glancing;
    double block;
    double critical;

    unsigned range{};
    unsigned miss_range{};
    unsigned dodge_range{};
    unsigned parry_range{};
    unsigned glancing_range{};
    unsigned block_range{};
};

#endif // MELEEWHITEHITTABLE_H