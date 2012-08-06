#pragma once
#include <string>
#include <boost/unordered_map.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/Menu.h"


namespace Danmaku
{
class Battle;
class BattleMenu;
class Character;

class TargetSelectMenu : public BlackDragonEngine::Menu
{
public:
  TargetSelectMenu(Battle& battle, BattleMenu& battleMenu);
  void SelectMenuItem();
  void ResetMenu();
  void Update();

private:
  enum Direction
  {
    Left,
    Right
  };

  void SelectMenuItemHorizontal(Direction direction);

  sf::String const Enemies;
  sf::String const Party;

  Battle& _battle;
  BattleMenu& _battleMenu;
  boost::unordered::unordered_map<std::string, Character*> _nameCharMap;
};
}
