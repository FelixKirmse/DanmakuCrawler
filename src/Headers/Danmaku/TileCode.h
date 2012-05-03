#pragma once
#include "SFML/System.hpp"

namespace Danmaku
{
using namespace sf;
class TileCode
{
public:
  enum TileCodes
  {
    Start,
    Event
  };

  TileCode(TileCodes code, String message = "");

  TileCodes Code;
  String Message;
};

bool operator==(TileCode const& lhs, TileCode const& rhs);
bool operator!=(TileCode const& lhs, TileCode const& rhs);

}
