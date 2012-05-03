template<class TCodes>
Map<TCodes>::Map()
  :_codes(), _mapData()
{
}

template<class TCodes>
unordered_map<Vector2i, vector<TCodes> >& Map<TCodes>::Codes()
{
  return _codes;
}

template<class TCodes>
unordered_map<Vector2i, SimpleMapSquare>& Map<TCodes>::MapData()
{
  return _mapData;
}

template<class TCodes>
int Map<TCodes>::MapWidth()
{
  return HighestX() - LowestY();
}

template<class TCodes>
int Map<TCodes>::MapHeight()
{
  return HighestY() - LowestY();
}

template<class TCodes>
int Map<TCodes>::LowestX()
{
  int lowestX(numeric_limits<int>::max());
  for(auto iter = _mapData.begin(); iter != _mapData.end(); ++iter)
    if(iter->first.x < lowestX)
      lowestX = iter->first.x;
  return lowestX;
}

template<class TCodes>
int Map<TCodes>::HighestX()
{
  int highestX(numeric_limits<int>::min());
  for(auto iter = _mapData.begin(); iter != _mapData.end(); ++iter)
    if(iter->first.x > highestX)
      highestX = iter->first.x;
  return highestX;
}

template<class TCodes>
int Map<TCodes>::LowestY()
{
  int lowestY(numeric_limits<int>::max());
  for(auto iter = _mapData.begin(); iter != _mapData.end(); ++iter)
    if(iter->first.y < lowestY)
      lowestY = iter->first.y;
  return lowestY;
}

template<class TCodes>
int Map<TCodes>::HighestY()
{
  int highestY(numeric_limits<int>::min());
  for(auto iter = _mapData.begin(); iter != _mapData.end(); ++iter)
    if(iter->first.y > highestY)
      highestY = iter->first.y;
  return highestY;
}

template<class TCodes>
SimpleMapSquare& Map<TCodes>::operator[](Vector2i const& coords)
{
  return _mapData[coords];
}

