#include "Danmaku/Party.h"

namespace Danmaku
{

Party* Party::_instance;

Party::Party()
  : _frontRow(), _battleBackSeat(), _availableCharacters()
{
  _instance = this;
}

Party::FrontRow& Party::GetFrontRow()
{
  return _instance->_frontRow;
}

Party::BackSeat& Party::GetBackSeat()
{
  return _instance->_battleBackSeat;
}

Party::CharVec& Party::GetAvailableCharacters()
{
  return _instance->_availableCharacters;
}

void Party::Reset()
{
  _instance->ResetInternal();
}

void Party::ResetInternal()
{
  _frontRow.fill(Character());
  _battleBackSeat.fill(Character());
  _availableCharacters.clear();

  _frontRow[0] = Character("Mokou");

  for(auto& c : _frontRow)
  {
    c.InitializeCharGraphics();
  }

  for(auto& c : _battleBackSeat)
  {
    c.InitializeCharGraphics();
  }

  for(auto& c : _availableCharacters)
  {
    c.InitializeCharGraphics();
  }
}
}
