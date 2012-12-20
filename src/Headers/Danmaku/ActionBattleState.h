#pragma once
#include "Danmaku/IBattleState.h"
#include <SFML/Graphics.hpp>

namespace Danmaku
{
class ActionBattleState : public IBattleState
{
public:
  ActionBattleState();

  void Update(Battle& battle);
  void Draw(Battle& battle, sf::RenderTarget& rTarget);

private:
  int _frameCounter;
  sf::Text _castText;
  sf::RectangleShape _castDisplay;

  static std::string const CastTextFormatString;
  static std::string const Allies;
  static std::string const Enemies;
  static std::string const Decaying;
  static std::string const Self;
};
}
