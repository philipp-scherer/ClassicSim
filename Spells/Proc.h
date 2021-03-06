#pragma once

#include "ProcInfo.h"
#include "Spell.h"

class EnabledProcs;
class Random;
class StatisticsProc;
class StatisticsBuff;

class Proc : public Spell {
public:
    Proc(const QString& name,
         const QString& icon,
         const double proc_rate,
         const double inner_cooldown,
         const QVector<Proc*>& linked_procs,
         QVector<ProcInfo::Source> proc_sources,
         Character* pchar);
    ~Proc() override;

    virtual unsigned get_proc_range() const;

    void enable_proc();
    void disable_proc();

    void set_current_proc_source(const ProcInfo::Source);

    bool procs_from_source(ProcInfo::Source) const;
    bool check_proc_success() const;

    void prepare_set_of_combat_iterations() override;

protected:
    EnabledProcs* procs;
    Random* random;
    QVector<Proc*> linked_procs;
    QVector<ProcInfo::Source> proc_sources;
    ProcInfo::Source curr_proc_source {};
    StatisticsProc* statistics_proc;

    unsigned proc_range;

    void spell_effect() override final;
    virtual void proc_effect() = 0;
    virtual bool proc_specific_conditions_fulfilled() const;
};
