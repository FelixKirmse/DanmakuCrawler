#pragma once
#include "SFML/System.hpp"
#include "Danmaku/Stats.h"

namespace Danmaku
{
class Character
{
public:
  Character();
  Character(sf::String name);

  bool UpdateTurnCounter();
private:
  sf::String _name;
  Stats _stats;
  int _turnCounter;

  int const TimeToAction = 3000;
};
}
