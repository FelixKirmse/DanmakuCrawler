#pragma once
#include <ctime>
#include <string>
#include <boost/random.hpp>
#include <SFML/Graphics.hpp>

namespace Danmaku
{
class EncounterRate
{
public:
  typedef boost::random::uniform_real_distribution<> FloatGenerator;
  typedef boost::random::mt19937 RandomSeed;

  EncounterRate(sf::Font const& font);

  void Step();
  void Draw(sf::RenderTarget& renderTarget);
private:
  sf::Text _rateDisplay;
  RandomSeed _rng;
  FloatGenerator _increaseChance;
  FloatGenerator _roll;
  float _currentChance;
};
}
