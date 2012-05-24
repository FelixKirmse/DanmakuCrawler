#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/IDrawableGameState.h"
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "Danmaku/MainMenu.h"
#include "Danmaku/IngameMenu.h"
#include "Danmaku/States.h"

namespace Danmaku
{
typedef MenuStates::MenuStates MenuState;

class Menu : public BlackDragonEngine::IDrawableGameState,
    public BlackDragonEngine::IUpdateableGameState
{
public:
  Menu();

  bool UpdateCondition();
  bool Update();

  bool DrawCondition();
  void Draw(float /*interpolation*/, sf::RenderTarget& renderTarget);

  static void SetState(MenuState state);
  static MenuState GetState();
private:
  MainMenu _mainMenu;
  IngameMenu _ingameMenu;
  static MenuState State;
};
}
