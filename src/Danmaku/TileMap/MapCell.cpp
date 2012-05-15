#include "Danmaku/MapCell.h"

namespace Danmaku
{
MapCell::MapCell()
  : TileID(0), InvalidCell(true), _leftConnector(false), _rightConnector(false),
    _topConnector(false), _bottomConnector(false)
{
}

MapCell::MapCell(MapCell const& source)
  : TileID(source.TileID), InvalidCell(source.InvalidCell),
    _leftConnector(source._leftConnector),
    _rightConnector(source._rightConnector),
    _topConnector(source._topConnector),
    _bottomConnector(source._bottomConnector)
{
}

MapCell::MapCell(int tileID)
  : TileID(tileID), InvalidCell(false),
    _leftConnector(tileID == TileList::Intersection ||
                   tileID == TileList::SVLeft || tileID == TileList::SH ||
                   tileID == TileList::SHUp || tileID == TileList::SHDown ||
                   tileID == TileList::CLeftDown ||
                   tileID == TileList::CLeftUp),
    _rightConnector(tileID == TileList::Intersection ||
                    tileID == TileList::SVRight || tileID == TileList::SH ||
                    tileID == TileList::SHUp || tileID == TileList::SHDown ||
                    tileID == TileList::CDownRight ||
                    tileID == TileList::CUpRight),
    _topConnector(tileID == TileList::Intersection ||
                  tileID == TileList::SVRight || tileID == TileList::SV ||
                  tileID == TileList::SHUp || tileID == TileList::SVLeft ||
                  tileID == TileList::CLeftUp || tileID == TileList::CUpRight),
    _bottomConnector(tileID == TileList::Intersection ||
                     tileID == TileList::SVRight || tileID == TileList::SV ||
                     tileID == TileList::SVLeft || tileID == TileList::SHDown ||
                     tileID == TileList::CDownRight ||
                     tileID == TileList::CLeftDown)
{
}

bool MapCell::IsConnected(MapCell const& other, Direction direction) const
{
  return (direction == Horizontal) ?
        ((_leftConnector && other._rightConnector) ||
         (_rightConnector && other._leftConnector)) :
        ((_topConnector && other._bottomConnector) ||
         (_bottomConnector && other._topConnector));
}
}
