#pragma once
#include <array>
#include "Danmaku/IBattleState.h"

namespace Danmaku
{
class Battle;

class ConsequenceBattleState : public IBattleState
{
public:
  typedef std::array<float, 4> FloatVec;

  ConsequenceBattleState(CharVec& enemies);

  void Update(Battle& battle);
  void Draw(Battle& battle, sf::RenderTarget& rTarget);

private:
  int _frameCounter;
  bool _enemyTurn;
  FrontRow& _frontRow;
  CharVec& _enemies;
  FloatVec _charHPStep;
  FloatVec _charHPShouldHave;

  static int const ConsequenceFrames;
};
}
