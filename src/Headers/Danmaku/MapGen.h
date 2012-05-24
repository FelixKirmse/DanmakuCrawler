#pragma once
#include <vector>
#include <boost/random.hpp>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/TileMap.h"
#include "BlackDragonEngine/Map.h"
#include "Danmaku/MapCell.h"
#include "Danmaku/TileCode.h"
#include "Danmaku/TileList.h"

namespace Danmaku
{
class MapGen
{
public:
  typedef BlackDragonEngine::TileMap<BlackDragonEngine::Map<MapCell, TileCode>,
  MapCell, TileCode> DanmakuMap;
  typedef boost::unordered::unordered_map<sf::Vector2i, MapCell> MapData;
  typedef boost::random::uniform_int_distribution<> IntGenerator;
  typedef boost::random::mt19937 RandomSeed;
  typedef std::vector<TileList::TileList> TileVec;

  MapGen(DanmakuMap& tileMap);
  void GenerateStep(sf::Vector2i const& currentTile);
  void GenerateInitialMap(sf::Vector2i const& current, int recursionSteps = 0,
                          int maxSteps = 10);

  MapGen& operator=(MapGen const&);
private:
  bool CellAvailable(sf::Vector2i const& cell);

  DanmakuMap& _tileMap;
  MapData& _mapData;
  RandomSeed _rng;
  IntGenerator _selectTileType;
  std::vector<MapCell::Direction> _possibleDirections;
  TileVec _straightTiles;
  TileVec _cornerTiles;
  TileVec _branchTiles;
};
}
