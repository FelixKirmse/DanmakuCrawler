#pragma once

namespace Danmaku
{
namespace TileList
{
// S = Straight, V = Vertical, H = Horizontal, C = Corner
enum TileList
{
  Intersection = 0,
  SVLeft = 1,
  SVRight = 2,
  SV = 3,
  SH = 4,
  SHUp = 5,
  SHDown = 6,
  CDownRight = 8,
  CLeftDown = 9,
  CLeftUp = 10,
  CUpRight = 11
};
}
}
