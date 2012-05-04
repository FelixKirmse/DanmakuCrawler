#pragma once
#include "SFML/System.hpp"

namespace Danmaku
{
class TileCode
{
public:
  enum TileCodes
  {
    Start,
    Event
  };

  TileCode(TileCodes code, sf::String message = "");

  TileCodes Code;
  sf::String Message;
};

bool operator==(TileCode const& lhs, TileCode const& rhs);
bool operator!=(TileCode const& lhs, TileCode const& rhs);

}
