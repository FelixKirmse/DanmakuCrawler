#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/IDrawableGameState.h"
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "Danmaku/MainMenu.h"
#include "Danmaku/States.h"


namespace Danmaku
{
typedef MenuStates::MenuStates MenuState;

class MainMenu;

class Menu : public BlackDragonEngine::IDrawableGameState,
    public BlackDragonEngine::IUpdateableGameState
{
public:
  typedef std::unique_ptr<MainMenu> MainMenuPtr;

  Menu();

  bool UpdateCondition();
  bool Update();

  bool DrawCondition();
  void Draw(float /*interpolation*/, sf::RenderTarget& renderTarget);

  static void SetState(MenuState state);
  static MenuState GetState();
private:
  MainMenuPtr _mainMenu;
  static MenuState State;
};
}
