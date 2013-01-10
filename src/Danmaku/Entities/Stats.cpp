#include "Danmaku/Stats.h"
#include <ctime>

namespace Danmaku
{
Stats::StatsMap Stats::_baseStats;
Stats::RandomSeed Stats::_rng(time(0));
typedef boost::random::uniform_int_distribution<> IntGenerator;

Stats::Stats()
  : BaseStats(), Masteries(), Resistances(), XPMultiplier(1.0f)
{
}

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
    BaseStats[HP][6] += BaseStats[HP][6] < 6.66f ? 0.03f : 0.f;
    //BaseStats[MP][6] += BaseStats[MP][6] < 5.f ? 0.02f : 0.f;
    BaseStats[AD][6] += BaseStats[AD][6] < 5.f ? 0.02f : 0.f;
    BaseStats[MD][6] += BaseStats[MD][6] < 5.f ? 0.02f : 0.f;
    BaseStats[DEF][6] += BaseStats[DEF][6] < 5.f ? 0.02f : 0.f;
    BaseStats[MR][6] += BaseStats[MR][6] < 5.f ? 0.02f : 0.f;
    BaseStats[CHA][6] += BaseStats[CHA][6] < 5.f ? 0.02f : 0.f;
    BaseStats[EVA][6] += BaseStats[EVA][6] < 5.f ? 0.02f : 0.f;
    BaseStats[SPD][6] += 0.000645f;

    BaseStats[HP][0] += BaseStats[HP][5];
    //BaseStats[MP][0] += BaseStats[MP][5];
    BaseStats[AD][0] += BaseStats[AD][5];
    BaseStats[MD][0] += BaseStats[MD][5];
    BaseStats[DEF][0] += BaseStats[DEF][5];
    BaseStats[MR][0] += BaseStats[MR][5];
    BaseStats[CHA][0] += BaseStats[CHA][5];

    BaseStats[EVA][0] += BaseStats[EVA][5];

    BaseStats[SPD][0] = 100.f + BaseStats[SPD][6] * newLevel * BaseStats[SPD][5];
  }
  BaseStats[MP][0] = 200.f;
  BaseStats[MP][6] = 1.f;
}

void Stats::BuffBaseStat(BaseStat baseStat, float amount)
{
  SingleStat& stat = BaseStats[baseStat];
  stat[4] += amount;
  stat[4] = (stat[4] > 2.f) ? 2.f : stat[4] < 0.5f ? 0.5f : stat[4];
}

void Stats::ReduceBuffEffectiveness(int times)
{
  for(int k = 0; k < times; ++k)
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

float Stats::GetEVAChance(int level)
{
  float stat = GetTotalBaseStat(EVA);
  if(EVAType == Block)
    return stat;

  return stat / level;
}

Stats Stats::GetRandomStats()
{
  Stats stats;

  IntGenerator hpBaseRoll(75, 200);
  IntGenerator hpBonusRoll(5, 25);

  stats.BaseStats[HP][0] = hpBaseRoll(_rng);
  stats.BaseStats[HP][5] = hpBonusRoll(_rng);
  stats.BaseStats[HP][4] = 1.f;
  stats.BaseStats[HP][6] = 1.f;

  stats.BaseStats[MP][0] = 200.f;
  stats.BaseStats[MP][5] = 0.f;
  stats.BaseStats[MP][6] = 1.f;

  IntGenerator baseStatRoll(20, 80);
  IntGenerator baseStatBonusRoll(1, 20);
  for(int i = 2; i <= 5; ++i)
  {
    stats.BaseStats[(BaseStat)i][0] = baseStatRoll(_rng);
    stats.BaseStats[(BaseStat)i][5] = baseStatBonusRoll(_rng);    
    stats.BaseStats[(BaseStat)i][4] = 1.f;
    stats.BaseStats[(BaseStat)i][6] = 1.f;
  }

  IntGenerator evaTypeRoll(0, 99);
  stats.EVAType = evaTypeRoll(_rng) < 10 ? Block : Dodge;

  if(stats.EVAType == Dodge)
  {
    IntGenerator evaBonusRoll(1, 8);
    stats.BaseStats[EVA][0] = 2;
    stats.BaseStats[EVA][5] = evaBonusRoll(_rng);    
  }
  else
  {
    IntGenerator blockRoll(20, 80);
    IntGenerator blockBonusRoll(0, 1);
    stats.BaseStats[EVA][0] = blockRoll(_rng);
    stats.BaseStats[EVA][5] = blockBonusRoll(_rng);
  }
  stats.BaseStats[EVA][4] = 1.f;
  stats.BaseStats[EVA][6] = 1.f;

  IntGenerator spdBonusRoll(5, 15);
  stats.BaseStats[SPD][0] = 100.f;
  stats.BaseStats[SPD][5] = spdBonusRoll(_rng);
  stats.BaseStats[SPD][6] = 0.0225f;
  stats.BaseStats[SPD][4] = 1.f;

  IntGenerator masteryRoll(50, 200);
  IntGenerator resiRoll(0, 30);
  for(int i = 0; i <= 8; ++i)
  {
    stats.Masteries[(EleMastery)i][0] = masteryRoll(_rng);    
    if(i < 6)
      stats.Resistances[(DebuffResistance)i][0] = resiRoll(_rng);
  }

  IntGenerator xpMultiplier(70, 140);
  stats.XPMultiplier = (float)xpMultiplier(_rng) / 100.f;

  return stats;
}


}
