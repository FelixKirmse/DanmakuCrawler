#pragma once
#include "SFML/System.hpp"

namespace Danmaku
{
using namespace sf;
class TileCode
{
public:
  TileCode(TileCodes code, String message = "");

  enum TileCodes
  {
    Start,
    Event
  };

  TileCodes Code;
  String Message;
};

bool operator==(TileCode const& lhs, TileCode const& rhs);
bool operator!=(TileCode const& lhs, TileCode const& rhs);

}
