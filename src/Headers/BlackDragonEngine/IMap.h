#pragma once
#include <vector>
#include <SFML/System.hpp>
#include "BlackDragonEngine/SimpleMapSquare.h"
#include "BlackDragonEngine/Vector2Hash.h"
#include <boost/unordered_map.hpp>


namespace BlackDragonEngine
{
using namespace std;
using namespace sf;
using namespace boost;

template<class TCodes>
class IMap
{
public:
  virtual ~IMap() {}
  virtual unordered_map<Vector2i, vector<TCodes> >& Codes() = 0;
  virtual unordered_map<Vector2i, SimpleMapSquare>& MapData() = 0;
  virtual int MapWidth() = 0;
  virtual int MapHeight() = 0;
  virtual int LowestX() = 0;
  virtual int HighestX() = 0;
  virtual int LowestY() = 0;
  virtual int HighestY() = 0;
  virtual SimpleMapSquare& operator[](Vector2i const& coords) = 0;
};

}
