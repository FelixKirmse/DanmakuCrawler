template<class TMap, class TCodes>
TileMap<TMap, TCodes>::TileMap(int tileWidth, int tileHeight, int tileOffset,
                               Texture const& tileSheet)
  :_tileWidth(tileWidth), _tileHeight(tileHeight), _tileOffset(tileOffset),
    _tileSheet(tileSheet),
    _tilesPerRow(tileSheet.getSize().x/(tileWidth + tileOffset)),
    _vMap(Quads)
{
  if(_instance != 0)
    throw "An instance of this class was already created elsewhere, use GetInstance to get it!";

  size_t tileCount = (_tilesPerRow*_tileSheet.getSize().y)/
      (_tileHeight + _tileOffset);

  for(size_t i = 0; i < tileCount; ++i)
  {
    _tileSourceRects[i] = IntRect((i%_tilesPerRow)*(_tileWidth + _tileOffset),
                                  (i/_tilesPerRow)*(_tileHeight + _tileOffset),
                                  _tileWidth, _tileHeight);
    _instance = this;
  }
}

template<class TMap, class TCodes>
TMap& TileMap<TMap, TCodes>::GetMap()
{
  return _map;
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::Draw(RenderTarget& renderTarget)
{
  Vector2f cameraPos = Camera::GetPosition();
  int startX = GetCellByPixelX((int) cameraPos.x) - 1;
  int endX = GetCellByPixelX((int) cameraPos.x + Camera::GetViewPortWidth());

  int startY = GetCellByPixelY((int) cameraPos.y) - 1;
  int endY = GetCellByPixelY((int) cameraPos.y + Camera::GetViewPortHeight());

  vector<Vector2i, SimpleMapSquare> const& mapData = _map.MapData();
  _vMap.clear();
  for(auto it = mapData.begin(); it != mapData.end(); ++it)
  {
    int i = 0;
    Vector2i const cell = it->first;
    if(cell.x < startX || cell.x > endX || cell.y < startY || cell.y > endY)
      continue;
    int const tileID = _map[cell].TileID;
    IntRect const sourceRect = TileSourceRectangle(tileID);

    _vMap[i + 0].position = Vector2f((cell.x + 0) * _tileWidth,
                                     (cell.y + 0) * _tileHeight);
    _vMap[i + 1].position = Vector2f((cell.x + 0) * _tileWidth,
                                     (cell.y + 1) * _tileHeight);
    _vMap[i + 2].position = Vector2f((cell.x + 1) * _tileWidth,
                                     (cell.y + 1) * _tileHeight);
    _vMap[i + 3].position = Vector2f((cell.x + 1) * _tileWidth,
                                     (cell.y + 0) * _tileHeight);

    _vMap[i + 0].texCoords = Vector2i(sourceRect.left,
                                      sourceRect.top);
    _vMap[i + 1].texCoords = Vector2i(sourceRect.left,
                                      sourceRect.top + sourceRect.height);
    _vMap[i + 2].texCoords = Vector2i(sourceRect.left + sourceRect.width,
                                      sourceRect.top + sourceRect.height);
    _vMap[i + 3].texCoords = Vector2i(sourceRect.left + sourceRect.width,
                                      sourceRect.top);
    i = i + 4;
  }

  renderTarget.draw(_vMap, _tileSheet);
}

template<class TMap, class TCodes>
int TileMap<TMap, TCodes>::GetTileWidth()
{
  return _tileWidth;
}

template<class TMap, class TCodes>
int TileMap<TMap, TCodes>::GetTileHeight()
{
  return _tileHeight;
}

template<class TMap, class TCodes>
int TileMap<TMap, TCodes>::GetMapWidth()
{
  return _map.MapWidth();
}

template<class TMap, class TCodes>
int TileMap<TMap, TCodes>::GetMapHeight()
{
  return _map.MapHeight();
}

template<class TMap, class TCodes>
int TileMap<TMap, TCodes>::GetCellByPixelX(float pixelX)
{
  float cell = pixelX/_tileWidth;
  return (cell < 0 && cell < (int)cell) ? (int)cell - 1 : (int)cell;
}

template<class TMap, class TCodes>
int TileMap<TMap, TCodes>::GetCellByPixelY(float pixelY)
{
  float cell = pixelY/_tileHeight;
  return (cell < 0 && cell < (int)cell) ? (int)cell - 1 : (int)cell;
}

template<class TMap, class TCodes>
Vector2i TileMap<TMap, TCodes>::GetCellByPixel(Vector2f const& pixelLocation)
{
  return Vector2i(GetCellByPixelX(pixelLocation.x),
                  GetCellByPixelY(pixelLocation.y));
}

template<class TMap, class TCodes>
Vector2f TileMap<TMap, TCodes>::GetCellCenter(Vector2i const& cell)
{
  return Vector2f((cell.x*_tileWidth) + (_tileWidth/2.0f),
                  (cell.y*_tileHeight) + (_tileHeight/2.0f));
}

template<class TMap, class TCodes>
IntRect TileMap<TMap, TCodes>::CellWorldRectangle(Vector2i const& cell)
{
  return IntRect(cell.x*_tileWidth, cell.y*_tileHeight, _tileWidth, _tileHeight);
}

template<class TMap, class TCodes>
IntRect TileMap<TMap, TCodes>::CellScreenRectangle(Vector2i const& cell)
{
  return Camera::WorldToScreen(CellWorldRectangle(cell));
}

template<class TMap, class TCodes>
vector<TCodes>& TileMap<TMap, TCodes>::GetCellCodes(Vector2i const& cell)
{
  return _map.Codes()[cell];
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::SetCellCodes(Vector2i const& cell,
                                         vector<TCodes> const& codes)
{
  _map.Codes()[cell] = codes;
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::AddCodeToCell(Vector2i const& cell,
                                          TCodes const& code)
{
  _map.Codes()[cell].push_back(code);
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::RemoveCodeFromCell(Vector2i const& cell,
                                               TCodes const& code)
{
  vector<TCodes>& codes = _map.Codes()[cell];
  for(size_t i = 0;i < codes.size(); ++i)
    if(codes[i] == code)
      codes.erase(i--);
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::SetEverythingAtCell(SimpleMapSquare const& square,
                                                vector<TCodes> const& codes,
                                                Vector2i const& cell)
{
  _map[cell] = square;
  _map.Codes()[cell] = codes;
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::RemoveEverythingAtCell(Vector2i const& cell)
{
  _map.Codes().erase(cell);
  _map.MapData().erase(cell);
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::RemoveMapSquareAtCell(Vector2i const& cell)
{
  _map.MapData().erase(cell);
}

template<class TMap, class TCodes>
SimpleMapSquare& TileMap<TMap, TCodes>::GetMapSquareAtCell(Vector2i const& cell)
{
  return _map[cell];
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::SetMapSquareAtCell(Vector2i const& cell,
                                               SimpleMapSquare const& square)
{
  _map[cell] = square;
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::SetTileAtCell(Vector2i const& cell, size_t tileIndex)
{
  _map[cell].TileID = tileIndex;
}

template<class TMap, class TCodes>
SimpleMapSquare& TileMap<TMap, TCodes>::GetMapSquareAtPixel(
    Vector2f const& pixelLocation)
{
  return GetMapSquareAtCell(GetCellByPixelX(pixelLocation.x),
                            GetCellByPixelY(pixelLocation.y));
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::ClearMap()
{
  _map = TMap();
}

template<class TMap, class TCodes>
TileMap<TMap, TCodes>& TileMap<TMap, TCodes>::GetInstance()
{
  if(_instance == 0)
    throw "There's no instance available, make sure you call the public constructor once!";
  return *_instance;
}

template<class TMap, class TCodes>
IntRect& TileMap<TMap, TCodes>::TileSourceRectangle(size_t tileIndex)
{
  return _tileSourceRects[tileIndex];
}

template<class TMap, class TCodes>
TileMap<TMap, TCodes>* TileMap<TMap, TCodes>::_instance = 0;

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::LoadMap(String location)
{
  //TODO Load Code
  _vMap = VertexArray(Quads, _map.MapData().size() * 4);
}

template<class TMap, class TCodes>
void TileMap<TMap, TCodes>::SaveMap(String location)
{
}
