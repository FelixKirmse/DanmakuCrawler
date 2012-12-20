#pragma once
#include <array>
#include <vector>
#include <memory>

namespace Danmaku
{
class Character;

class Party
{
public:
  typedef std::array<Character*, 4> FrontRow;
  typedef std::vector<Character*> CharVec;

  static Party& GetInstance();

  FrontRow& GetFrontRow();
  CharVec& GetAvailableCharacters();
  void Reset();
  void AddExperience(unsigned long amount);
  int GetAveragePartyLvl();
  long long GetExperience();
  void ResetCache();
  void SwitchChars(size_t availableIndex, size_t frontRowIndex);

private:
  Party();
  ~Party();
  FrontRow _frontRow;
  CharVec _availableCharacters;

  long long _experience;
  int _averagePartyLvl;

  bool _cached;
};
}
