#include <ctime>
#include <string>
#include "Danmaku/EncounterRate.h"
#include "Danmaku/Battle.h"

namespace Danmaku
{
EncounterRate::EncounterRate(sf::Font const& font)
  : _rateDisplay(), _rng(time(0)), _increaseChance(.5f, 3.f),
    _roll(0.f, 100.f), _currentChance(0.f)
{
  _rateDisplay.setFont(font);
  _rateDisplay.setCharacterSize(12);
  _rateDisplay.setPosition(sf::Vector2f(10.f, 460.f));
  _rateDisplay.setString("EncounterRate: " +
                         std::to_string(_currentChance) + "%");
  _rateDisplay.setColor(sf::Color::Red);
}

void EncounterRate::SetChance(int newChance)
{
  _currentChance = newChance;
  _rateDisplay.setString("EncounterRate: " +
                         std::to_string(_currentChance) + "%");
}

void EncounterRate::Step()
{  
  if(_roll(_rng) < (_currentChance - 50.f))
  {
    _currentChance = 0.f;
    _rateDisplay.setString("EncounterRate: " +
                           std::to_string(_currentChance) + "%");
    // TODO actual level logic
    Battle::StartBattle(1);
    return;
  }
  _currentChance += _increaseChance(_rng);
  _rateDisplay.setString("EncounterRate: " +
                         std::to_string(_currentChance) + "%");
}

void EncounterRate::Draw(sf::RenderTarget& renderTarget)
{
  renderTarget.draw(_rateDisplay);
}
}
