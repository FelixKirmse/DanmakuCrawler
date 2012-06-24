#include "Danmaku/Party.h"

namespace Danmaku
{
Party::CharVec Party::_frontRow;
Party::CharVec Party::_battleBackSeat;
Party::CharVec Party::_availableCharacters;

Party::CharVec& Party::GetFrontRow()
{
  return _frontRow;
}

Party::CharVec& Party::GetBackSeat()
{
  return _battleBackSeat;
}

Party::CharVec& Party::GetAvailableCharacters()
{
  return _availableCharacters;
}
}
