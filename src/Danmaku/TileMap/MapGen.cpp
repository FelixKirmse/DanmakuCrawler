#include "Danmaku/MapGen.h"

namespace Danmaku
{
MapGen::MapGen(DanmakuMap& tileMap)
  : _tileMap(tileMap), _mapData(tileMap.GetMap().MapData()), _rng(time(0)),
    _selectTileType(0,99), _possibleDirections()
{
  using namespace sf;
  using namespace TileList;
  tileMap.ClearMap();
  _straightTiles = { SV, SH };
  _cornerTiles = { CDownRight, CLeftDown, CLeftUp, CUpRight };
  _branchTiles = { Intersection, SVLeft, SVRight, SHUp, SHDown };
  _mapData[Vector2i(0,0)] = MapCell(Intersection);
  //GenerateStep(Vector2i(0,0));
  GenerateInitialMap(Vector2i(0,0), 0, 10);
}

bool MapGen::CellAvailable(sf::Vector2i const& cell)
{
  return !_mapData.count(cell);
}

void MapGen::GenerateStep(sf::Vector2i const& current)
{
  using namespace sf;
  using namespace TileList;

  if(CellAvailable(current))
    return;

  _possibleDirections.clear();  
  MapCell& currentCell = _mapData[current];

  if(currentCell.TopConnector && CellAvailable(Vector2i(current.x,
                                                        current.y - 1)))
    _possibleDirections.push_back(MapCell::Up);
  if(currentCell.BottomConnector && CellAvailable(Vector2i(current.x,
                                                           current.y + 1)))
    _possibleDirections.push_back(MapCell::Down);
  if(currentCell.LeftConnector && CellAvailable(Vector2i(current.x - 1,
                                                         current.y)))
    _possibleDirections.push_back(MapCell::Left);
  if(currentCell.RightConnector && CellAvailable(Vector2i(current.x + 1,
                                                          current.y)))
    _possibleDirections.push_back(MapCell::Right);
  if(_possibleDirections.size() == 0)
    return;
  for(size_t i = 0; i < _possibleDirections.size(); ++i)
  {
    MapCell newCell;
    MapCell::Direction direction(_possibleDirections[i]);
    int tileType = _selectTileType(_rng);
    /* 50% Chance for Straight Tiles
     * 25% Chance for Corner Tiles
     * 25% Chance for Branching Tiles
     */
    std::vector<TileList::TileList> possibleTiles =
        (tileType < 50) ? _straightTiles :
                          (tileType < 75) ? _cornerTiles : _branchTiles ;
    IntGenerator selectTile(0, possibleTiles.size() - 1);
    do
    {
      int tile;
      tile = possibleTiles[selectTile(_rng)];
      newCell = MapCell(tile);
    }
    while(!currentCell.IsTraversible(newCell, direction));
    Vector2i newTile(current);
    newTile.x += (direction == MapCell::Left) ? -1 :
                                                (direction == MapCell::Right) ?
                                                  1 : 0;
    newTile.y += (direction == MapCell::Up) ? -1 :
                                              (direction == MapCell::Down) ?
                                                1 : 0;
    _mapData[newTile] = newCell;
  }
  BlackDragonEngine::Camera::UpdateWorldRectangle(_tileMap);
}

void MapGen::GenerateInitialMap(sf::Vector2i const& current,
                                int recursionSteps, int maxSteps)
{
  using namespace sf;
  if(recursionSteps == maxSteps)
    return;
  GenerateStep(current);
  GenerateInitialMap(Vector2i(current.x + 1, current.y), recursionSteps + 1,
                     maxSteps);
  GenerateInitialMap(Vector2i(current.x - 1, current.y), recursionSteps + 1,
                     maxSteps);
  GenerateInitialMap(Vector2i(current.x, current.y + 1), recursionSteps + 1,
                     maxSteps);
  GenerateInitialMap(Vector2i(current.x, current.y - 1), recursionSteps + 1,
                     maxSteps);
}

MapGen& MapGen::operator=(MapGen const& source)
{
  _rng = source._rng;
  _selectTileType = source._selectTileType;
  _possibleDirections = source._possibleDirections;
  _straightTiles = source._straightTiles;
  _cornerTiles = source._cornerTiles;
  _branchTiles = source._branchTiles;
  return *this;
}
}
