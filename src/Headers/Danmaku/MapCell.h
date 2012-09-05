#pragma once
namespace Danmaku
{
class MapCell
{
public:
  MapCell();
  MapCell(int tileID);
  MapCell(MapCell const& source);
  MapCell(int tileID, int level);

  enum Direction
  {
    Up,
    Down,
    Left,
    Right
  };

  bool IsTraversible(MapCell const& other, Direction direction) const;

  int TileID;
  bool InvalidCell;

  bool LeftConnector;
  bool RightConnector;
  bool TopConnector;
  bool BottomConnector;

  int EnemyLvl;
};
}
