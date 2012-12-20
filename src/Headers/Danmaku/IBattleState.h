#pragma once
#include <vector>
#include <array>

namespace sf{class RenderTarget;}
namespace Danmaku
{
class Battle;
class Character;

class IBattleState
{
public:
  typedef std::vector<Character*> CharVec;
  typedef std::array<Character*, 4> FrontRow;

  virtual ~IBattleState() {}
  virtual void Update(Battle& battle) = 0;
  virtual void Draw(Battle& battle, sf::RenderTarget& rTarget) = 0;
};
}
