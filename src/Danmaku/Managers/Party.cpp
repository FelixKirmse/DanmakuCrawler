#include "Danmaku/Party.h"

namespace Danmaku
{

Party* Party::_instance;

Party::Party()
  : _frontRow(), _battleBackSeat(), _availableCharacters()
{
  _instance = this;
}

Party::CharVec& Party::GetFrontRow()
{
  return _instance->_frontRow;
}

Party::CharVec& Party::GetBackSeat()
{
  return _instance->_battleBackSeat;
}

Party::CharVec& Party::GetAvailableCharacters()
{
  return _instance->_availableCharacters;
}
}
