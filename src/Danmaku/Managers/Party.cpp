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


  // TODO Delete all the test stuff
  _frontRow[0] = Character("Tenko");
  _frontRow[1] = Character("Komachi");
  _frontRow[2] = Character("Remilia");
  _frontRow[3] = Character("Wriggle");

  for(auto& c : _frontRow)
  {
    c.InitializeCharGraphics();    
    c.LvlUp(100);
    c.CurrentHP() = c.GetStats().GetTotalBaseStat(HP);
    c.CurrentMP() = c.GetStats().GetTotalBaseStat(MP);
    c.Graphics().UpdateHP();
    c.Graphics().UpdateMP();
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
