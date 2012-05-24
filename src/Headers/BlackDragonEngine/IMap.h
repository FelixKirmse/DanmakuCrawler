#pragma once
#include <vector>
#include <boost/unordered_map.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/Vector2Hash.h"

namespace BlackDragonEngine
{
template<class TCell, class TCodes>
class IMap
{
public:
  typedef boost::unordered::unordered_map<sf::Vector2i, std::vector<TCodes> >
  VecCodeMap;
  typedef boost::unordered::unordered_map<sf::Vector2i, TCell> VecSquareMap;

  virtual ~IMap() {}
  virtual VecCodeMap& Codes() = 0;
  virtual VecSquareMap& MapData() = 0;
  virtual int MapWidth() = 0;
  virtual int MapHeight() = 0;
  virtual int LowestX() = 0;
  virtual int HighestX() = 0;
  virtual int LowestY() = 0;
  virtual int HighestY() = 0;
  virtual TCell& operator[](sf::Vector2i const& coords) = 0;
};
}
