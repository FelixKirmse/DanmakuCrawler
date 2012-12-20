#pragma once
#include "Danmaku/IBattleState.h"

namespace Danmaku
{
class GameOverBattleState : public IBattleState
{
public:
  void Update(Battle& battle);
  void Draw(Battle& battle, sf::RenderTarget& rTarget);
};
}
