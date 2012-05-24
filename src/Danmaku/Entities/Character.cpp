#include "Danmaku/Character.h"

namespace Danmaku
{

Character::Character()
  : Character("Default")
{
}

Character::Character(sf::String name)
  : _name(name), _stats()
{
}


bool Character::UpdateTurnCounter()
{
  _turnCounter += _stats.SPD[0] / 30.f;
  if(_turnCounter >= TimeToAction)
    _turnCounter = 0.f;

  return _turnCounter == 0.f;
}
}

