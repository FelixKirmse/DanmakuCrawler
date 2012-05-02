#pragma once
#include <map>
#include <vector>
#include <SFML/System.hpp>
#include "BlackDragonEngine/SimpleMapSquare.h"


namespace BlackDragonEngine
{
using namespace std;
using namespace sf;

template<class TCodes>
class IMap
{
public:
  virtual ~IMap() {}
  virtual map<Vector2i, vector<TCodes> >& Codes() = 0;
  virtual map<Vector2i, SimpleMapSquare>& MapData() = 0;
  virtual int MapWidth() = 0;
  virtual int MapHeight() = 0;
  virtual int LowestX() = 0;
  virtual int HighestX() = 0;
  virtual int LowestY() = 0;
  virtual int HighestY() = 0;
  virtual SimpleMapSquare& operator[](Vector2i const& coords) = 0;
};

}
