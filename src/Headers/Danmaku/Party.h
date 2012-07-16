#pragma once
#include <vector>
#include "Danmaku/Character.h"

namespace Danmaku
{
class Party
{
public:
  typedef std::vector<Character> CharVec;

  Party();

  static CharVec& GetFrontRow();
  static CharVec& GetBackSeat();
  static CharVec& GetAvailableCharacters();

private:
  CharVec _frontRow;
  CharVec _battleBackSeat;
  CharVec _availableCharacters;

  static Party* _instance;
};
}
