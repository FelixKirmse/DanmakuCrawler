#pragma once
#include "BlackDragonEngine/SimpleMapSquare.h"
#include "Danmaku/TileList.h"

namespace Danmaku
{
class MapCell
{
public:
  MapCell();
  MapCell(int tileID);
  MapCell(MapCell const& source);

  enum Direction
  {
    Horizontal,
    Vertical
  };

  bool IsConnected(MapCell const& other, Direction direction) const;

  int TileID;
  bool InvalidCell;

private:
  bool _leftConnector;
  bool _rightConnector;
  bool _topConnector;
  bool _bottomConnector;
};
}
