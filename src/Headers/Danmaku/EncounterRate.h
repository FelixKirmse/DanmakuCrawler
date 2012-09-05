#pragma once
#include <boost/random.hpp>
#include <SFML/Graphics.hpp>
#include "Danmaku/MapCell.h"

namespace Danmaku
{
class EncounterRate
{
public:
  typedef boost::random::uniform_real_distribution<> FloatGenerator;
  typedef boost::random::mt19937 RandomSeed;

  EncounterRate(sf::Font const& font);

  void SetChance(int newChance);
  void Step(MapCell& targetCell);
  void Draw(sf::RenderTarget& renderTarget);
private:
  sf::Text _rateDisplay;
  RandomSeed _rng;
  FloatGenerator _increaseChance;
  FloatGenerator _roll;
  float _currentChance;
};
}
