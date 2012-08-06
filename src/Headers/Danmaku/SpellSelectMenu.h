#pragma once
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <boost/unordered_map.hpp>
#include "BlackDragonEngine/Menu.h"


namespace Danmaku
{
class BattleMenu;
class Character;
class ISpell;

class SpellSelectMenu : public BlackDragonEngine::Menu
{
public:
  SpellSelectMenu(BattleMenu& battleMenu);
  void ResetMenu(Character* currentAttacker);
  void Update();
  void Draw(sf::RenderTarget& renderTarget);
  void SelectMenuItem();

private:
  void AddStandardMenuLabels();

  sf::String const Description;
  sf::String const MP;
  sf::Vector2f const DescriptionOrigin;
  float const OriginY;
  float const SpellOriginX;
  float const MPCostOriginX;
  float const YOffset;

  sf::RectangleShape _backDrop;

  BattleMenu& _battleMenu;
  Character* _currentAttacker;

  boost::unordered::unordered_map<std::string, ISpell*> _nameSpellMap;
};
}
