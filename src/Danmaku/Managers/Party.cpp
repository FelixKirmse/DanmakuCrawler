#include "Danmaku/Party.h"

namespace Danmaku
{

Party* Party::_instance;

Party::Party()
  : _frontRow(), _battleBackSeat(), _availableCharacters(), _experience(0)
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

void Party::AddExperience(unsigned long amount)
{
  _instance->_experience += amount;
  for(auto& chara : _instance->_frontRow)
    chara.LvlUp();
  for(auto& chara : _instance->_battleBackSeat)
    chara.LvlUp();
  for(auto& chara : _instance->_availableCharacters)
    chara.LvlUp();
}

int Party::GetAveragePartyLvl()
{
  if(_instance->_cached)
    return _instance->_averagePartyLvl;

  FrontRow& fr = _instance->_frontRow;
  BackSeat& bs = _instance->_battleBackSeat;

  int i(0);
  int lvlSum(0);
  for(auto& chara : fr)
  {
    if(chara.IsDead())
      continue;
    ++i;
    lvlSum += chara.GetLvl();
  }
  for(auto& chara : bs)
  {
    if(chara.IsDead())
      continue;
    ++i;
    lvlSum += chara.GetLvl();
  }

  _instance->_cached = true;
  if(i == 0)
    return 0;
  _instance->_averagePartyLvl = lvlSum / i;

  return _instance->_averagePartyLvl;
}

unsigned long Party::GetExperience()
{
  return _instance->_experience;
}

void Party::ResetCache()
{
  _instance->_cached = false;
}

void Party::ResetInternal()
{
  _frontRow.fill(Character());
  _battleBackSeat.fill(Character());
  _availableCharacters.clear();


  // TODO Delete all the test stuff
  _frontRow[0] = Character("Remilia");
  _frontRow[1] = Character("Youmu");
  _frontRow[2] = Character("Aya");
  _frontRow[3] = Character("Minoriko");

  for(auto& c : _frontRow)
  {
    c.InitializeCharGraphics();
    c.LvlUp(1);
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
