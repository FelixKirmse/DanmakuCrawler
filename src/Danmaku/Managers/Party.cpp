#include "Danmaku/Party.h"
#include "Danmaku/Character.h"

namespace Danmaku
{
Party::Party()
  : _frontRow(), _availableCharacters(), _experience(0)
{
}

Party::~Party()
{
  for(auto* chara : _frontRow)
    delete chara;
  for(auto* chara : _availableCharacters)
    delete chara;
}

Party& Party::GetInstance()
{
  static Party instance;
  return instance;
}

Party::FrontRow& Party::GetFrontRow()
{
  return _frontRow;
}

Party::CharVec& Party::GetAvailableCharacters()
{
  return _availableCharacters;
}

void Party::Reset()
{
  _experience = 0u;
  for(auto* chara : _frontRow)
    delete chara;

  for(auto* chara : _availableCharacters)
    delete chara;


  // TODO Delete all the test stuff
  _frontRow[0] = new Character("Komachi");
  _frontRow[1] = new Character("Youmu");
  _frontRow[2] = new Character("Kaguya");
  _frontRow[3] = new Character("Minoriko");

  _availableCharacters.push_back(new Character("Alice"));
  _availableCharacters.push_back(new Character("Chen"));
  _availableCharacters.push_back(new Character("Cirno"));
  _availableCharacters.push_back(new Character("Eiki"));
  _availableCharacters.push_back(new Character("Eirin"));
  _availableCharacters.push_back(new Character("Flandre"));
  _availableCharacters.push_back(new Character("Iku"));
  _availableCharacters.push_back(new Character("Aya"));
  _availableCharacters.push_back(new Character("Kanako"));
  _availableCharacters.push_back(new Character("Keine"));
  _availableCharacters.push_back(new Character("Kourin"));
  _availableCharacters.push_back(new Character("Maribel"));
  _availableCharacters.push_back(new Character("Marisa"));
  _availableCharacters.push_back(new Character("Meirin"));
  _availableCharacters.push_back(new Character("Mokou"));
  _availableCharacters.push_back(new Character("Mystia"));
  _availableCharacters.push_back(new Character("Nitori"));
  _availableCharacters.push_back(new Character("Patchouli"));
  _availableCharacters.push_back(new Character("Ran"));
  _availableCharacters.push_back(new Character("Reimu"));
  _availableCharacters.push_back(new Character("Remilia"));
  _availableCharacters.push_back(new Character("Renko"));
  _availableCharacters.push_back(new Character("Rin"));
  _availableCharacters.push_back(new Character("Rumia"));
  _availableCharacters.push_back(new Character("Sakuya"));
  _availableCharacters.push_back(new Character("Sanae"));
  _availableCharacters.push_back(new Character("Suika"));
  _availableCharacters.push_back(new Character("Suwako"));
  _availableCharacters.push_back(new Character("Tenko"));
  _availableCharacters.push_back(new Character("Udonge"));
  _availableCharacters.push_back(new Character("Utsuho"));
  _availableCharacters.push_back(new Character("Wriggle"));
  _availableCharacters.push_back(new Character("Yukari"));
  _availableCharacters.push_back(new Character("Yuugi"));
  _availableCharacters.push_back(new Character("Yuuka"));
  _availableCharacters.push_back(new Character("Yuyuko"));

  for(auto* c : _frontRow)
  {   
    c->LvlUp(1);
    c->CurrentHP() = c->GetStats().GetTotalBaseStat(HP);
    c->CurrentMP() = c->GetStats().GetTotalBaseStat(MP);
    c->Graphics().UpdateHP();
    c->Graphics().UpdateMP();
  }

  for(auto* c : _availableCharacters)
  {  
    c->LvlUp(1);
    c->CurrentHP() = c->GetStats().GetTotalBaseStat(HP);
    c->CurrentMP() = c->GetStats().GetTotalBaseStat(MP);
    c->Graphics().UpdateHP();
    c->Graphics().UpdateMP();

  }
}

void Party::AddExperience(unsigned long amount)
{
  _experience += amount;
  for(auto* chara : _frontRow)
    chara->LvlUp();
  for(auto* chara : _availableCharacters)
    chara->LvlUp();
}

int Party::GetAveragePartyLvl()
{
  if(_cached)
    return _averagePartyLvl;

  FrontRow& fr = _frontRow;
  CharVec& bs = _availableCharacters;

  int i(0);
  int lvlSum(0);
  for(auto* chara : fr)
  {
    if(chara == 0 || chara->IsDead())
      continue;
    ++i;
    lvlSum += chara->GetLvl();
  }
  for(auto* chara : bs)
  {
    if(chara->IsDead())
      continue;
    ++i;
    lvlSum += chara->GetLvl();
  }

  _cached = true;
  if(i == 0)
    return 0;
  _averagePartyLvl = lvlSum / i;

  return _averagePartyLvl;
}

long long Party::GetExperience()
{
  return _experience;
}

void Party::ResetCache()
{
  _cached = false;
}

void Party::SwitchChars(size_t availableIndex, size_t frontRowIndex)
{  
  Character* backRowChar = _availableCharacters[availableIndex];
  Character* frontRowChar = _frontRow[frontRowIndex];

  sf::Vector2f charGraphicsPosition = frontRowChar->Graphics().GetPosition();

  _frontRow[frontRowIndex] = backRowChar;
  _availableCharacters[availableIndex] = frontRowChar;

  _frontRow[frontRowIndex]->Graphics().Reposition(charGraphicsPosition);

  _frontRow[frontRowIndex]->Graphics().UpdateSPD(false);
  _availableCharacters[availableIndex]->Graphics().UpdateSPD(false);
 }
}
