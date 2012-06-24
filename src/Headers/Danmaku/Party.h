#pragma once
#include <vector>
#include "Danmaku/Character.h"

namespace Danmaku
{
class Party
{
public:
  typedef std::vector<Character> CharVec;

  static CharVec& GetFrontRow();
  static CharVec& GetBackSeat();
  static CharVec& GetAvailableCharacters();

private:
  static CharVec _frontRow;
  static CharVec _battleBackSeat;
  static CharVec _availableCharacters;
};
}
