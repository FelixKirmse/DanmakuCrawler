#pragma once
#include <limits>
#include <vector>
#include <boost/unordered_map.hpp>
#include "BlackDragonEngine/IMap.h"
#include "BlackDragonEngine/Vector2Hash.h"

namespace BlackDragonEngine
{
using namespace sf;
using namespace std;
using namespace boost;


template<class TCodes>
class Map : public IMap<TCodes>
{
public:
  Map();
  unordered_map<Vector2i, vector<TCodes> >& Codes();
  unordered_map<Vector2i, SimpleMapSquare>& MapData();
  int MapWidth();
  int MapHeight();
  int LowestX();
  int HighestX();
  int LowestY();
  int HighestY();
  SimpleMapSquare& operator[](Vector2i const& coords);

private:
  unordered_map<Vector2i, vector<TCodes> > _codes;
  unordered_map<Vector2i, SimpleMapSquare> _mapData;
};

#include "BlackDragonEngine/Inline/Map.inl"

}


