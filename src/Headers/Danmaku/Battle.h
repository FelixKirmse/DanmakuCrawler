#pragma once
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"
#include "Danmaku/Character.h"
#include "Danmaku/BattleMenu.h"
#include "Danmaku/Party.h"
#include <boost/random.hpp>
#include <boost/unordered_map.hpp>
#include "Danmaku/IdleBattleState.h"
#include "Danmaku/ActionBattleState.h"
#include "Danmaku/ConsequenceBattleState.h"
#include "Danmaku/GameOverBattleState.h"
#include "Danmaku/BattleWonBattleState.h"

namespace Danmaku
{
class Battle : public BlackDragonEngine::IUpdateableGameState,
    public BlackDragonEngine::IDrawableGameState
{  
public:
  typedef std::vector<Character*> CharVec;
  typedef std::vector<sf::Vector2f> VecVec;
  typedef std::array<float, 4> FloatVec;
  typedef boost::random::mt19937 RandomSeed;

  Battle();

  bool UpdateCondition();
  bool Update();
  bool DrawCondition();
  void Draw(float interpolation, sf::RenderTarget& renderTarget);

  void SetTargetInfo(TargetInfo targetInfo);
  TargetInfo& GetTargetInfo();

  CharVec& GetEnemies();
  Party::FrontRow& GetFrontRow();

  void SetCurrentAttacker(Character* chara);
  Character* GetCurrentAttacker();

  bool IsEnemyTurn();
  void IsEnemyTurn(bool turn);

  bool IsBossFight();

  void SetIdle();
  void ShowBattleMenu();
  void PerformAction();
  void ShowConsequences();
  void GameOver();
  void BattleWon();

  static void StartBattle(int level, int bossID = 0);
  static size_t MaxEnemyID;
  static bool TargetIsEnemy();
  static bool AttackerIsEnemy();
  static Battle* GetInstance();

private:    
  void ArrangeCharFrames(int bossID);

  void GenerateEnemies(int level, int bossID);
  void SetupBossBattle(int level, int bossID);

  unsigned long long GetAvgSPD();

  template<class T>
  void SetInitialSPD(T& vec);

  CharVec _enemies;
  Party& _party;
  Party::FrontRow& _playerRow;
  Character* _currentAttacker;

  TargetInfo _targetInfo;

  bool _enemyTurn;

  IdleBattleState _idleState;
  BattleMenu _battleMenu;
  ActionBattleState _actionState;
  ConsequenceBattleState _consequenceState;
  GameOverBattleState _gameOverState;
  BattleWonBattleState _battleWonState;

  IBattleState* _battleState;


  VecVec _threeLayout;
  VecVec _fourLayout;

  RandomSeed _rng; 

  IBattleState* _queuedState;
  bool _stateChanged;

  bool _isBossfight;

  sf::RectangleShape _castDisplay;
  sf::Text _castText;


  static sf::Vector2f const FrameContainerStart;
  static int const FrameContainerOffset;

  static float const EnemyHPMod;
  static float const EnemyBaseMod;

  static Battle* _currentInstance;
};

#include "Danmaku/Inline/Battle.inl"
}
