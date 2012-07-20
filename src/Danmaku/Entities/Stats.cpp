#include "Danmaku/Stats.h"

namespace Danmaku
{
// Base Stats
// General formula is (base + (base * items) + bonus) * buffs
float Stats::GetTotalBaseStat(BaseStat baseStat)
{
  SingleStat& stat = BaseStats[baseStat];
  if(baseStat == HP || baseStat == MP)
    return stat[0] + (stat[0] * (stat[1] + stat[2] + stat[3])) +
        (stat[6] * stat[5]);
  else
    return (stat[0] + (stat[0] * (stat[1] + stat[2] + stat[3])) +
            (stat[6] * stat[5])) * stat[4];
}

// Elemental Masteries
// General formular is base + items + bonus
float Stats::GetTotalMastery(EleMastery mastery)
{
  SingleStat& stat = Masteries[mastery];
  return stat[0] + stat[1] + stat[2] + stat[3] + stat[6];
}

// Debuff Resistances
// General formular is base + items
float Stats::GetTotalResistance(DebuffResistance resistance)
{
  SingleStat& stat = Resistances[resistance];
  return stat[0] + stat[1] + stat[2] + stat[3];
}

void Stats::LvlUp()
{
  BaseStats[HP][0] += BaseStats[HP][5];
  BaseStats[MP][0] += BaseStats[MP][5];
  BaseStats[AD][0] += BaseStats[AD][5];
  BaseStats[MD][0] += BaseStats[MD][5];
  BaseStats[DEF][0] += BaseStats[DEF][5];
  BaseStats[MR][0] += BaseStats[MR][5];
}


Stats::StatsMap Stats::StatMap;
void Stats::LoadStatMap()
{

}
}
