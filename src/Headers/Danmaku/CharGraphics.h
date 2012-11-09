#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Danmaku
{
class Character;

class CharGraphics
{  
public:
  CharGraphics();
  CharGraphics(sf::Vector2f offset, sf::String charName, Character* owner);

  void UpdateSPD(bool myTurn);
  void UpdateHP();
  void UpdateMP();
  void SetDamageDone(float damage, bool heal, bool block = false, bool dodge = false);
  void SetBattleSpritePosition(sf::Vector2f pos);

  void DrawBattleSprite(sf::RenderTarget& rTarget);
  void DrawCharSprite(sf::RenderTarget& rTarget);
  void Draw(sf::RenderTarget& rTarget);
  void DrawDamageDone(sf::RenderTarget& rTarget);
  void Reposition(sf::Vector2f newOffset);
  void Reposition(float x, float y);
  void SetDeadSprites();
  void RestoreSprites();

  void ResetDamage();

  sf::Vector2f const& GetPosition();

private:
  Character* _owner;
  sf::Vector2f _offset;

  sf::Sprite _portrait;
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

  sf::Text _enemyName;
  sf::Text _damageDone;

  bool _myTurn;
  bool _tookDamage;


  float _damageSum;
  bool _blocked;
  bool _dodged;
  bool _healed;

  static sf::Color const FullSPDBar;
  static sf::Color const NormalSPDBar;
  static sf::Texture* DeadFrame;
};
}
