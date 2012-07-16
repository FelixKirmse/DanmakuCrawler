#pragma once
#include <SFML/Graphics.hpp>

namespace Danmaku
{
class Character;

class CharGraphics
{
  friend class Battle; // Delete this
public:
  CharGraphics();
  CharGraphics(sf::Vector2f offset, sf::String charName, Character* owner);

  void UpdateSPD();
  void UpdateHP();
  void UpdateMP();
  void SetBattleSpritePosition(sf::Vector2f const& pos);

  void DrawBattleSprite(sf::RenderTarget& rTarget);
  void DrawCharSprite(sf::RenderTarget& rTarget);
  void Draw(sf::RenderTarget& rTarget);
  void Reposition(sf::Vector2f newOffset);
  void Reposition(float x, float y);

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

  sf::Sprite _charSprite;
  sf::Sprite _battleSprite;

  sf::RectangleShape _enemySpdBar;
  sf::RectangleShape _enemySpdBackgrnd;

  bool _myTurn;

  static sf::Color const FullSPDBar;
  static sf::Color const NormalSPDBar;
};
}
