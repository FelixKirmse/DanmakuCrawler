#pragma once
#include <vector>
#include <boost/unordered_map.hpp>
#include "BlackDragonEngine/IMap.h"
#include "BlackDragonEngine/Vector2Hash.h"

namespace BlackDragonEngine
{
template<class TCell, class TCodes>
class Map : public IMap<TCell, TCodes>
{
public:  
  typedef boost::unordered::unordered_map<sf::Vector2i, std::vector<TCodes> >
  CodeMap;
  typedef boost::unordered::unordered_map<sf::Vector2i, TCell> TileMap;

  Map();
  CodeMap& Codes();
  TileMap& MapData();
  int MapWidth();
  int MapHeight();
  int LowestX();
  int HighestX();
  int LowestY();
  int HighestY();
  TCell& operator[](sf::Vector2i const& coords);

private:
  CodeMap _codes;
  TileMap _mapData;
};

#include "BlackDragonEngine/Inline/Map.inl"
}


