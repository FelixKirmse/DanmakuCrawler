#pragma once
#include "Danmaku/IBattleState.h"


namespace Danmaku
{
class Character;

class IdleBattleState : public IBattleState
{
public:
  IdleBattleState(CharVec& enemies);

  void Update(Battle& battle);
  void Draw(Battle& battle, sf::RenderTarget& rTarget);

private:
  int _playerLeftOff;
  int _enemyLeftOff;
  FrontRow& _frontRow;
  CharVec& _enemies;
};
}
