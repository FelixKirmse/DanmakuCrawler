#pragma once
#include <SFML/System.hpp>
#include "BlackDragonEngine/Menu.h"

namespace Danmaku
{
class IngameMenu : public BlackDragonEngine::Menu
{
public:
  IngameMenu();
  void Update();
  void SelectMenuItem();
private:
  sf::String const Resume;
  sf::String const BackToMenu;
};
}
