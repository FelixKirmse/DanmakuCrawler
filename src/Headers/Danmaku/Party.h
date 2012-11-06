#pragma once
#include <array>
#include <vector>
#include "Danmaku/Character.h"

namespace Danmaku
{
class Party
{
public:
  typedef std::array<Character, 4> FrontRow;
  typedef std::vector<Character> CharVec;

  Party();

  static FrontRow& GetFrontRow();
  static CharVec& GetAvailableCharacters();
  static void Reset();
  static void AddExperience(unsigned long amount);
  static int GetAveragePartyLvl();
  static long long GetExperience();
  static void ResetCache();

private:
  void ResetInternal();

  FrontRow _frontRow;
  CharVec _availableCharacters;

  long long _experience;
  int _averagePartyLvl;

  bool _cached;

  static Party* _instance;
};
}
