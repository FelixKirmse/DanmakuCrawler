#include "Danmaku/Stats.h"
#include <ctime>

namespace Danmaku
{
Stats::StatsMap Stats::_baseStats;
Stats::RandomSeed Stats::_rng(time(0));
typedef boost::random::uniform_int_distribution<> IntGenerator;

// Base Stats
// General formula is (base + (base * items) + bonus) * buffs
float Stats::GetTotalBaseStat(BaseStat baseStat)
{
  SingleStat& stat = BaseStats[baseStat];
  if(baseStat == HP || baseStat == MP)
    return stat[0] * (stat[6] + stat[1] + stat[2] + stat[3]);
  else
    return (stat[0] * (stat[6] + stat[1] + stat[2] + stat[3])) * stat[4];
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

void Stats::LvlUp(int currentLevel, int amount)
{
  int newLevel(currentLevel + amount);
  for(int i = 0; i < amount; ++i)
  {
    BaseStats[HP][6] += 0.03f;
    BaseStats[MP][6] += 0.02f;
    BaseStats[AD][6] += 0.02f;
    BaseStats[MD][6] += 0.02f;
    BaseStats[DEF][6] += 0.02f;
    BaseStats[MR][6] += 0.02f;
    BaseStats[CHA][6] += 0.02f;
    BaseStats[EVA][6] += 0.02f;
    BaseStats[SPD][6] += 0.000645f;

    BaseStats[HP][0] += BaseStats[HP][5];
    BaseStats[MP][0] += BaseStats[MP][5];
    BaseStats[AD][0] += BaseStats[AD][5];
    BaseStats[MD][0] += BaseStats[MD][5];
    BaseStats[DEF][0] += BaseStats[DEF][5];
    BaseStats[MR][0] += BaseStats[MR][5];
    BaseStats[CHA][0] += BaseStats[CHA][5];

    BaseStats[EVA][0] += BaseStats[EVA][5];

    BaseStats[SPD][0] = 100.f + BaseStats[SPD][6] * newLevel * BaseStats[SPD][5];
  }
}

void Stats::BuffBaseStat(BaseStat baseStat, float amount)
{
  SingleStat& stat = BaseStats[baseStat];
  stat[4] += amount;
  stat[4] = (stat[4] > 2.f) ? 2.f : stat[4] < 0.5f ? 0.5f : stat[4];
}

void Stats::ReduceBuffEffectiveness()
{
  for(int i = 0; i < 8; ++i)
  {
    float& stat = BaseStats[(BaseStat)i][4];
    if(stat < 1.f)
    {
      stat += .1f;
      stat = stat > 1.f ? 1.f : stat;
    }
    if(stat > 1.f)
    {
      stat -= .1f;
      stat = stat < 1.f ? 1.f : stat;
    }
  }
}

void Stats::RemoveStatDebuffs()
{
  for(int i = 0; i < 9; ++i)
  {
    float& stat = BaseStats[(BaseStat)i][4];
    if(stat < 1.f)
      stat = 1.f;
  }
}

void Stats::RemoveBuffs()
{
  for(int i = 0; i < 9; ++i)
  {
    float& stat = BaseStats[(BaseStat)i][4];
    if(stat > 1.f)
      stat = 1.f;
  }
}

bool Stats::TryToApplyDebuff(DebuffResistance type, int successChance)
{
  IntGenerator applyRoll(0,99);
  int resistance(GetTotalResistance(type) * 3);
  return applyRoll(_rng) < successChance - resistance;
}


}
