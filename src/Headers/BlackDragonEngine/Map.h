#pragma once
#include <limits>
#include <vector>
#include <boost/unordered_map.hpp>
#include "BlackDragonEngine/IMap.h"
#include "BlackDragonEngine/Vector2Hash.h"

namespace BlackDragonEngine
{
template<class TCodes>
class Map : public IMap<TCodes>
{
public:  
  typedef boost::unordered_map<sf::Vector2i, std::vector<TCodes> > CodeMap;
  typedef boost::unordered_map<sf::Vector2i, SimpleMapSquare> TileMap;

  Map();
  CodeMap& Codes();
  TileMap& MapData();
  int MapWidth();
  int MapHeight();
  int LowestX();
  int HighestX();
  int LowestY();
  int HighestY();
  SimpleMapSquare& operator[](sf::Vector2i const& coords);

private:
  CodeMap _codes;
  TileMap _mapData;
};

#include "BlackDragonEngine/Inline/Map.inl"
}


