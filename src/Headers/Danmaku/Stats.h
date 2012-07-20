#pragma once
#include <boost/array.hpp>
#include <boost/unordered_map.hpp>
#include <SFML/System.hpp>


#include <fstream>
#include "Danmaku/SerializeUnorderedMap.h"
#include <boost/serialization/array.hpp>

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

namespace Danmaku
{
/*
 * Each stat in the struct has 7 fields.
 * Stat[0] contains the base value of a stat
 * Stat[1] - Stat[3] contain modifiers from items in the respective slot
 * Stat[4] contains temporary battle modifiers (buffs/debuffs)
 * Stat[5] contains the growth of a stat on levelup
 * Stat[6] contains the invested bonus points in a stat
 */

enum BaseStat
{
  HP,     // Health Points
  MP,     // Magic Points
  AD,     // Attack Damage
  MD,     // Magic Damage
  DEF,    // Defense
  MR,     // Magic Resist
  EVA,    // Evasion Stat
  SPD,    // Speed
  CHA     // Charisma
};

enum EleMastery // increase damage done, decrease damage taken
{
  FIR,    // Fire
  WAT,    // Water
  ICE,    // Ice
  ARC,    // Arcane
  WND,    // Wind
  HOL,    // Holy
  DRK,    // Dark
  GRN,    // Ground
  LGT     // Lightning
};

enum DebuffResistance
{
  PSN,    // Poison
  PAR,    // Paralyze
  SLW,    // Slow
  STD,    // Statdrop
  DTH,    // Instant-Death
  SIL     // Silence
};

struct Stats
{
  typedef boost::array<float, 7> SingleStat;
  typedef boost::unordered::unordered_map<BaseStat, SingleStat> BaseStatMap;
  typedef boost::unordered::unordered_map<EleMastery, SingleStat> MasteryMap;
  typedef boost::unordered::unordered_map<DebuffResistance, SingleStat> ResiMap;
  typedef boost::unordered::unordered_map<sf::String, Stats> StatsMap;

  enum
  {
    Dodge,
    Block
  } EVAType;      // Type of Evasion Stat

  BaseStatMap BaseStats;
  MasteryMap Masteries;
  ResiMap Resistances;

  float GetTotalBaseStat(BaseStat baseStat);
  float GetTotalMastery(EleMastery mastery);
  float GetTotalResistance(DebuffResistance resistance);

  void LvlUp();

  static StatsMap StatMap;

  static void LoadStatMap();

  template<class Archive>
  void serialize(Archive& ar, unsigned int const version);
};

#include "Danmaku/Inline/Stats.inl"
}
