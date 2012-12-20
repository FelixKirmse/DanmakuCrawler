#pragma once
#include <boost/array.hpp>
#include <boost/unordered_map.hpp>
#include <string>
#include <SFML/System.hpp>
#include <boost/random.hpp>


#include <fstream>
#include "SerializeUnorderedMap.h"
#include <boost/serialization/array.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

namespace Danmaku
{
/*
 * Each stat in the struct has 7 fields.
 * Stat[0] contains the base value of a stat
 * Stat[1] - Stat[3] contain the modifiers from items in the respective slot
 * Stat[4] contains temporary battle modifiers (buffs/debuffs)
 * Stat[5] contains the growth of a stat on levelup
 * Stat[6] contains the stat multiplier
 */

enum BaseStat
{
  HP = 0,     // Health Points
  MP = 1,     // Magic Points
  AD = 2,     // Attack Damage
  MD = 3,     // Magic Damage
  DEF = 4,    // Defense
  MR = 5,     // Magic Resist
  EVA = 6,    // Evasion Stat
  SPD = 7,    // Speed
  CHA = 8     // Charisma
};

enum EleMastery // increase damage done, decrease damage taken
{
  FIR = 0,    // Fire
  WAT = 1,    // Water
  ICE = 2,    // Ice
  ARC = 3,    // Arcane
  WND = 4,    // Wind
  HOL = 5,    // Holy
  DRK = 6,    // Dark
  GRN = 7,    // Ground
  LGT = 8     // Lightning
};

enum DebuffResistance
{
  PSN = 0,    // Poison
  PAR = 1,    // Paralyze
  SLW = 2,    // Slow -- OBSOLETE
  STD = 3,    // Statdrop -- OBSOLETE
  DTH = 4,    // Instant-Death
  SIL = 5     // Silence
};

struct Stats
{
  typedef boost::array<float, 7> SingleStat;
  typedef boost::unordered::unordered_map<BaseStat, SingleStat> BaseStatMap;
  typedef boost::unordered::unordered_map<EleMastery, SingleStat> MasteryMap;
  typedef boost::unordered::unordered_map<DebuffResistance, SingleStat> ResiMap;
  typedef boost::unordered::unordered_map<std::string, Stats> StatsMap;
  typedef boost::random::mt19937 RandomSeed;

  enum
  {
    Dodge = 0,
    Block = 1
  } EVAType;      // Type of Evasion Stat

  BaseStatMap BaseStats;
  MasteryMap Masteries;
  ResiMap Resistances;
  float XPMultiplier;

  float GetTotalBaseStat(BaseStat baseStat);
  float GetTotalMastery(EleMastery mastery);
  float GetTotalResistance(DebuffResistance resistance);

  void LvlUp(int currentLevel, int amount);
  void BuffBaseStat(BaseStat baseStat, float amount);
  void ReduceBuffEffectiveness(int times = 1);
  void RemoveStatDebuffs();
  void RemoveBuffs();
  bool TryToApplyDebuff(DebuffResistance type, int successChance);

  float GetEVAChance(int level);

  static Stats GetRandomStats();

  static StatsMap _baseStats;
  static RandomSeed _rng;

  template<class Archive>
  void serialize(Archive& ar, unsigned int const /*version*/);
};

#include "Danmaku/Inline/Stats.inl"

}
