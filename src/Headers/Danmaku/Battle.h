#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"
#include "Danmaku/Character.h"
#include "Danmaku/BattleMenu.h"

namespace Danmaku
{
class Battle : public BlackDragonEngine::IUpdateableGameState,
    public BlackDragonEngine::IDrawableGameState
{
  friend class Danmaku::BattleMenu;
public:
  typedef std::vector<Character> CharVec;
  typedef std::vector<sf::Vector2f> VecVec;

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
  void SetInitialSPD(CharVec& vec);

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
  CharVec& _playerRow;
  CharVec& _playerBattleParty;
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

  static Battle* _currentInstance;
};
}
