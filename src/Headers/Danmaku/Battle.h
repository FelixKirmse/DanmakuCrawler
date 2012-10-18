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

namespace Danmaku
{
class Battle : public BlackDragonEngine::IUpdateableGameState,
    public BlackDragonEngine::IDrawableGameState
{  
public:
  typedef std::vector<Character> CharVec;
  typedef std::vector<sf::Vector2f> VecVec;
  typedef std::array<float, 4> FloatVec;
  typedef boost::random::mt19937 RandomSeed;

  enum BattleState
  {
    Idle,
    BattleMenu,
    Action,
    Consequences,
    GameOver,
    BattleWon
  };

  Battle();
  bool UpdateCondition();
  bool Update();
  bool DrawCondition();
  void Draw(float interpolation, sf::RenderTarget& renderTarget);
  void SetTargetInfo(TargetInfo targetInfo);
  void SetBattleState(BattleState battleState);
  CharVec& GetEnemies();
  Party::FrontRow& GetFrontRow();

  static void StartBattle(int level, int bossID = 0);
  static size_t MaxEnemyID;
  static bool TargetIsEnemy();
  static bool AttackerIsEnemy();
  static Battle* GetInstance();

private:  
  void IdleUpdate();
  void ConsequenceUpdate();
  void ActionUpdate();

  void Draw(sf::RenderTarget& renderTarget);
  void ConsequenceDraw(sf::RenderTarget& renderTarget);
  void ActionDraw(sf::RenderTarget& rTarget);

  void ArrangeCharFrames(int bossID);

  void GenerateEnemies(int level, int bossID);
  void SetupBossBattle(int level, int bossID);

  void EndBattle();

  unsigned long long GetAvgSPD();

  template<class T>
  void SetInitialSPD(T& vec);

  BattleState _battleState;  

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

  sf::Vector2f const FrameContainerStart = sf::Vector2f(200.f, 380.f);
  size_t FrameContainerOffset = 110;

  VecVec _threeLayout;
  VecVec _fourLayout;

  FloatVec _charHPStep;
  FloatVec _charHPShouldHave;

  RandomSeed _rng; 

  BattleState _queuedState;
  bool _changeState;

  bool _isBossfight;

  sf::RectangleShape _castDisplay;
  sf::Text _castText;

  static int const ConsequenceFrames;
  static float const EnemyHPMod;
  static float const EnemyBaseMod;
  static int const XPPerEnemy;
  static int const XPPerConvincedEnemy;
  static int const XPFromBoss;
  static int const XPFromConvincedBoss;
  static std::string const CastTextFormatString;
  static std::string const Allies;
  static std::string const Enemies;
  static std::string const Decaying;
  static std::string const Self;

  static Battle* _currentInstance;  
};

#include "Danmaku/Inline/Battle.inl"
}
