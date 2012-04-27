#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/IDrawableGameState.h"
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "Danmaku/MainMenu.h"
#include "Danmaku/States.h"
#include "Danmaku/GameStateManager.h"


namespace Danmaku
{
using BlackDragonEngine::IDrawableGameState;
using BlackDragonEngine::IUpdateableGameState;
using namespace sf;
typedef MenuStates::MenuStates MenuState;

class Menu : public IDrawableGameState, public IUpdateableGameState
{
public:
  Menu();

  bool UpdateCondition();
  bool Update();

  bool DrawCondition();
  void Draw(float /*interpolation*/, RenderTarget& renderTarget);

  static void SetState(MenuState state);
private:
  MainMenu _mainMenu;
  static MenuState State;
};
}
