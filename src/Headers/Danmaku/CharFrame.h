#pragma once
#include <SFML/Graphics.hpp>

namespace Danmaku
{
class Character;

class CharFrame
{
  friend class Battle; // Delete this
public:
  CharFrame();
  CharFrame(sf::Vector2f offset, sf::String charName, Character* owner);

  void UpdateSPD();
  void UpdateHP();
  void UpdateMP();

  void Draw(sf::RenderTarget& rTarget);
  void Reposition(sf::Vector2f newOffset);

private:
  Character* _owner;
  sf::Vector2f _offset;

  sf::RectangleShape _frame;
  sf::RectangleShape _spdBackgrnd;
  sf::RectangleShape _spdBar;
  sf::RectangleShape _hpBackgrnd;
  sf::RectangleShape _hpBar;
  sf::RectangleShape _mpBackgrnd;
  sf::RectangleShape _mpBar;
  sf::Text _hp;
  sf::Text _mp;
  sf::Text _hpValue;
  sf::Text _mpValue;
};
}
