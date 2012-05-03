#include "Danmaku/TileCode.h"

namespace Danmaku
{
TileCode::TileCode(TileCodes code, String message)
  : Code(code), Message(message)
{
}

bool operator==(TileCode const& lhs, TileCode const& rhs)
{
  return lhs.Code == rhs.Code;
}

bool operator!=(TileCode const& lhs, TileCode const& rhs)
{
  return !operator==(lhs, rhs);
}
}
