#include "Danmaku/TileList.h"
#include "Danmaku/MapCell.h"
#include "Danmaku/Party.h"

namespace Danmaku
{
MapCell::MapCell()
  : TileID(0), InvalidCell(true), LeftConnector(false), RightConnector(false),
    TopConnector(false), BottomConnector(false), EnemyLvl(0)
{
}

MapCell::MapCell(MapCell const& source)
  : TileID(source.TileID), InvalidCell(source.InvalidCell),
    LeftConnector(source.LeftConnector),
    RightConnector(source.RightConnector),
    TopConnector(source.TopConnector),
    BottomConnector(source.BottomConnector),
    EnemyLvl(source.EnemyLvl)
{
}

MapCell::MapCell(int tileID, int level)
  : MapCell(tileID)
{
  EnemyLvl = level;
}

MapCell::MapCell(int tileID)
  : TileID(tileID), InvalidCell(false),
    LeftConnector(tileID == TileList::Intersection ||
                   tileID == TileList::SVLeft || tileID == TileList::SH ||
                   tileID == TileList::SHUp || tileID == TileList::SHDown ||
                   tileID == TileList::CLeftDown ||
                   tileID == TileList::CLeftUp),
    RightConnector(tileID == TileList::Intersection ||
                    tileID == TileList::SVRight || tileID == TileList::SH ||
                    tileID == TileList::SHUp || tileID == TileList::SHDown ||
                    tileID == TileList::CDownRight ||
                    tileID == TileList::CUpRight),
    TopConnector(tileID == TileList::Intersection ||
                  tileID == TileList::SVRight || tileID == TileList::SV ||
                  tileID == TileList::SHUp || tileID == TileList::SVLeft ||
                  tileID == TileList::CLeftUp || tileID == TileList::CUpRight),
    BottomConnector(tileID == TileList::Intersection ||
                     tileID == TileList::SVRight || tileID == TileList::SV ||
                     tileID == TileList::SVLeft || tileID == TileList::SHDown ||
                     tileID == TileList::CDownRight ||
                     tileID == TileList::CLeftDown),
    EnemyLvl(Party::GetInstance().GetAveragePartyLvl())
{
}

bool MapCell::IsTraversible(MapCell const& other, Direction direction) const
{
  return (direction == Up) ?
        TopConnector && other.BottomConnector :
        (direction == Down) ?
          BottomConnector && other.TopConnector :
          (direction == Left) ?
            LeftConnector && other.RightConnector :
            (direction == Right) ?
              RightConnector && other.LeftConnector :
              false;
}
}
