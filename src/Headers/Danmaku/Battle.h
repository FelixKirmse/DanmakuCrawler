#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"
#include "Danmaku/Character.h"

namespace Danmaku
{
class Battle : public BlackDragonEngine::IUpdateableGameState,
    public BlackDragonEngine::IDrawableGameState
{
public:
  typedef std::vector<Character> CharVec;

  Battle();
  bool UpdateCondition();
  bool Update();
  bool DrawCondition();
  void Draw(float interpolation, sf::RenderTarget& renderTarget);

private:
  enum BattleStates
  {
    Idle,
    BattleMenu,
    Action,
    Consequences,
    GameOver,
    BattleWon
  } _battleState;

  CharVec _enemies;
  CharVec _playerRow;
  CharVec _playerBattleParty;
};
}
