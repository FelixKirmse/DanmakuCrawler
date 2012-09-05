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
  typedef std::array<Character, 12> BackSeat;
  typedef std::vector<Character> CharVec;

  Party();

  static FrontRow& GetFrontRow();
  static BackSeat& GetBackSeat();
  static CharVec& GetAvailableCharacters();
  static void Reset();
  static void AddExperience(unsigned long amount);
  static int GetAveragePartyLvl();
  static unsigned long GetExperience();
  static void ResetCache();

private:
  void ResetInternal();

  FrontRow _frontRow;
  BackSeat _battleBackSeat;
  CharVec _availableCharacters;

  unsigned long long _experience;
  int _averagePartyLvl;

  bool _cached;

  static Party* _instance;
};
}
