#pragma once
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"
#include "Danmaku/Character.h"
#include "Danmaku/BattleMenu.h"
#include "Danmaku/Party.h"

namespace Danmaku
{
class Battle : public BlackDragonEngine::IUpdateableGameState,
    public BlackDragonEngine::IDrawableGameState
{
  friend class Danmaku::BattleMenu;
public:
  typedef std::vector<Character> CharVec;
  typedef std::vector<sf::Vector2f> VecVec;
  typedef std::array<float, 4> FloatVec;

  Battle();
  bool UpdateCondition();
  bool Update();
  bool DrawCondition();
  void Draw(float interpolation, sf::RenderTarget& renderTarget);

  static void StartBattle(int level, int bossID = 0);

private:
  void IdleUpdate();
  void ConsequenceUpdate();

  void Draw(sf::RenderTarget& renderTarget);
  void ConsequenceDraw(sf::RenderTarget& renderTarget);

  void ArrangeCharFrames(int bossID);

  template<class T>
  void SetInitialSPD(T& vec);

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
  Party::FrontRow& _playerRow;
  Party::BackSeat& _playerBattleParty;
  Character* _currentAttacker;

  TargetInfo _targetInfo;

  size_t _enemyLeftOff;
  size_t _playerLeftOff;
  int _frameCounter;
  bool _enemyTurn;

  Danmaku::BattleMenu _battleMenu;

  sf::Vector2f const FrameContainerStart = sf::Vector2f(200.f, 370.f);
  size_t FrameContainerOffset = 110;

  VecVec _threeLayout;
  VecVec _fourLayout;

  FloatVec _charHPStep;
  FloatVec _charHPShouldHave;

  static Battle* _currentInstance;
};

#include "Danmaku/Inline/Battle.inl"
}
