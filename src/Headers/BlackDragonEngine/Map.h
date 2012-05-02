#pragma once
#include <limits>
#include <vector>
#include <map>
#include "BlackDragonEngine/IMap.h"

namespace BlackDragonEngine
{
using namespace sf;
using namespace std;

template<class TCodes>
class Map : public IMap<TCodes>
{
public:
  Map();
  map<Vector2i, vector<TCodes> >& Codes();
  map<Vector2i, SimpleMapSquare>& MapData();
  int MapWidth();
  int MapHeight();
  int LowestX();
  int HighestY();
  int LowestY();
  int HighestY();
  SimpleMapSquare& operator[](Vector2i const& coords);

private:
  map<Vector2i, vector<TCodes> > _codes;
  map<Vector2i, SimpleMapSquare> _mapData;
};

#include "BlackDragonEngine/Inline/Map.inl"

}


