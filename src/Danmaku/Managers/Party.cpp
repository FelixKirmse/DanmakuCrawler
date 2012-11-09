#include "Danmaku/Party.h"

namespace Danmaku
{

Party* Party::_instance;

Party::Party()
  : _frontRow(), _availableCharacters(), _experience(0)
{
  _instance = this;
}

Party::FrontRow& Party::GetFrontRow()
{
  return _instance->_frontRow;
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
  for(auto& chara : _instance->_availableCharacters)
    chara.LvlUp();
}

int Party::GetAveragePartyLvl()
{
  if(_instance->_cached)
    return _instance->_averagePartyLvl;

  FrontRow& fr = _instance->_frontRow;
  CharVec& bs = _instance->_availableCharacters;

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

long long Party::GetExperience()
{
  return _instance->_experience;
}

void Party::ResetCache()
{
  _instance->_cached = false;
}

void Party::SwitchChars(size_t availableIndex, size_t frontRowIndex)
{
  Party::FrontRow& frontRow = GetFrontRow();
  Party::CharVec& backSeat = GetAvailableCharacters();
  Character backRowChar = GetAvailableCharacters()[availableIndex];
  Character frontRowChar = GetFrontRow()[frontRowIndex];

  sf::Vector2f charGraphicsPosition = frontRowChar.Graphics().GetPosition();

  frontRow[frontRowIndex] = backRowChar;
  backSeat[availableIndex] = frontRowChar;

  frontRow[frontRowIndex].InitializeCharGraphics();
  backSeat[availableIndex].InitializeCharGraphics();

  frontRow[frontRowIndex].Graphics().Reposition(charGraphicsPosition);

  frontRow[frontRowIndex].Graphics().UpdateSPD(false);
  backSeat[availableIndex].Graphics().UpdateSPD(false);
 }

void Party::ResetInternal()
{
  _experience = 0u;
  _frontRow.fill(Character());
  _availableCharacters.clear();


  // TODO Delete all the test stuff
  _frontRow[0] = Character("Komachi");
  _frontRow[1] = Character("Youmu");
  _frontRow[2] = Character("Aya");
  _frontRow[3] = Character("Minoriko");

  _availableCharacters.push_back(Character("Alice"));
  _availableCharacters.push_back(Character("Chen"));
  _availableCharacters.push_back(Character("Cirno"));
  _availableCharacters.push_back(Character("Eiki"));
  _availableCharacters.push_back(Character("Eirin"));
  _availableCharacters.push_back(Character("Flandre"));
  _availableCharacters.push_back(Character("Iku"));
  _availableCharacters.push_back(Character("Kaguya"));
  _availableCharacters.push_back(Character("Kanako"));
  _availableCharacters.push_back(Character("Keine"));
  _availableCharacters.push_back(Character("Kourin"));
  _availableCharacters.push_back(Character("Maribel"));
  _availableCharacters.push_back(Character("Marisa"));
  _availableCharacters.push_back(Character("Meirin"));
  _availableCharacters.push_back(Character("Mokou"));
  _availableCharacters.push_back(Character("Mystia"));
  _availableCharacters.push_back(Character("Nitori"));
  _availableCharacters.push_back(Character("Patchouli"));
  _availableCharacters.push_back(Character("Ran"));
  _availableCharacters.push_back(Character("Reimu"));
  _availableCharacters.push_back(Character("Remilia"));
  _availableCharacters.push_back(Character("Renko"));
  _availableCharacters.push_back(Character("Rin"));
  _availableCharacters.push_back(Character("Rumia"));
  _availableCharacters.push_back(Character("Sakuya"));
  _availableCharacters.push_back(Character("Sanae"));
  _availableCharacters.push_back(Character("Suika"));
  _availableCharacters.push_back(Character("Suwako"));
  _availableCharacters.push_back(Character("Tenko"));
  _availableCharacters.push_back(Character("Udonge"));
  _availableCharacters.push_back(Character("Utsuho"));
  _availableCharacters.push_back(Character("Wriggle"));
  _availableCharacters.push_back(Character("Yukari"));
  _availableCharacters.push_back(Character("Yuugi"));
  _availableCharacters.push_back(Character("Yuuka"));
  _availableCharacters.push_back(Character("Yuyuko"));

  for(auto& c : _frontRow)
  {
    c.InitializeCharGraphics();
    c.LvlUp(1);
    c.CurrentHP() = c.GetStats().GetTotalBaseStat(HP);
    c.CurrentMP() = c.GetStats().GetTotalBaseStat(MP);
    c.Graphics().UpdateHP();
    c.Graphics().UpdateMP();
  }

  for(auto& c : _availableCharacters)
  {
    c.InitializeCharGraphics();
    c.LvlUp(1);
    c.CurrentHP() = c.GetStats().GetTotalBaseStat(HP);
    c.CurrentMP() = c.GetStats().GetTotalBaseStat(MP);
    c.Graphics().UpdateHP();
    c.Graphics().UpdateMP();

  }

}
}
