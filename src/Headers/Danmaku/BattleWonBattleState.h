#pragma once
#include "Danmaku/IBattleState.h"

namespace Danmaku
{
class BattleWonBattleState : public IBattleState
{
public:
  BattleWonBattleState(CharVec& enemies);

  void Update(Battle& battle);
  void Draw(Battle& battle, sf::RenderTarget& rTarget);

private:
  CharVec& _enemies;
  FrontRow& _frontRow;

  static int const XPPerEnemy;
  static int const XPPerConvincedEnemy;
  static int const XPFromBoss;
  static int const XPFromConvincedBoss;
};
}
