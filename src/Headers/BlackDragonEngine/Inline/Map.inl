template<class TCell, class TCodes>
Map<TCell, TCodes>::Map()
  :_codes(), _mapData()
{
}

template<class TCell, class TCodes>
boost::unordered::unordered_map<sf::Vector2i, std::vector<TCodes> >&
Map<TCell, TCodes>::Codes()
{
  return _codes;
}

template<class TCell, class TCodes>
boost::unordered::unordered_map<sf::Vector2i, TCell>&
Map<TCell, TCodes>::MapData()
{
  return _mapData;
}

template<class TCell, class TCodes>
int Map<TCell, TCodes>::MapWidth()
{
  return HighestX() - LowestY();
}

template<class TCell, class TCodes>
int Map<TCell, TCodes>::MapHeight()
{
  return HighestY() - LowestY();
}

template<class TCell, class TCodes>
int Map<TCell, TCodes>::LowestX()
{
  int lowestX(std::numeric_limits<int>::max());
  for(auto iter = _mapData.begin(); iter != _mapData.end(); ++iter)
    if(iter->first.x < lowestX)
      lowestX = iter->first.x;
  return lowestX;
}

template<class TCell, class TCodes>
int Map<TCell, TCodes>::HighestX()
{
  int highestX(std::numeric_limits<int>::min());
  for(auto iter = _mapData.begin(); iter != _mapData.end(); ++iter)
    if(iter->first.x > highestX)
      highestX = iter->first.x;
  return highestX;
}

template<class TCell, class TCodes>
int Map<TCell, TCodes>::LowestY()
{
  int lowestY(std::numeric_limits<int>::max());
  for(auto iter = _mapData.begin(); iter != _mapData.end(); ++iter)
    if(iter->first.y < lowestY)
      lowestY = iter->first.y;
  return lowestY;
}

template<class TCell, class TCodes>
int Map<TCell, TCodes>::HighestY()
{
  int highestY(std::numeric_limits<int>::min());
  for(auto iter = _mapData.begin(); iter != _mapData.end(); ++iter)
    if(iter->first.y > highestY)
      highestY = iter->first.y;
  return highestY;
}

template<class TCell, class TCodes>
TCell& Map<TCell, TCodes>::operator[](sf::Vector2i const& coords)
{
  return _mapData[coords];
}
