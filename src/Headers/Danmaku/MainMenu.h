#pragma once
#include <SFML/System.hpp>
#include "BlackDragonEngine/Menu.h"

namespace Danmaku
{
class MainMenu : public BlackDragonEngine::Menu
{
public:
  MainMenu();
  void Update();
  void SelectMenuItem();
private:
  sf::String const NewGame;
  sf::String const Resume;
  sf::String const Quit;
};
}
