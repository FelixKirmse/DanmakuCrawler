template<class TMap, class TCell, class TCodes>
TileMap<TMap, TCell, TCodes>::TileMap(int tileWidth, int tileHeight, int tileOffset,
                               int tileStepX, int tileStepY, int oddRowXOffset,
                               sf::Texture const& tileSheet,
                               sf::Vector2i resolution)
  :_tileWidth(tileWidth), _tileHeight(tileHeight), _tileOffset(tileOffset),
    _tileStepX(tileStepX), _tileStepY(tileStepY),
    _oddRowXOffset(oddRowXOffset),
    _tileSheet(tileSheet),
    _tilesPerRow(tileSheet.getSize().x/(tileWidth + tileOffset)),
    _vMap(sf::Quads, (resolution.x/tileWidth + 10) *
          (resolution.y/tileHeight + 10) * 4)
{
  if(_instance != 0)
    throw "An instance of this class was already created elsewhere, use GetInstance to get it!";

  size_t tileCount = (_tilesPerRow*_tileSheet.getSize().y)/
      (_tileHeight + _tileOffset);

  for(size_t i = 0; i < tileCount; ++i)
  {
    _tileSourceRects.push_back(Rectangle((i%_tilesPerRow)*(_tileWidth + _tileOffset),
                                         (i/_tilesPerRow)*(_tileHeight + _tileOffset),
                                         _tileWidth, _tileHeight));
    _instance = this;
  }
}

template<class TMap, class TCell, class TCodes>
TMap& TileMap<TMap, TCell, TCodes>::GetMap()
{
  return _map;
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::Draw(sf::RenderTarget& renderTarget)
{
  Vector2 cameraPos = Camera::GetPosition();
  int startX = GetCellByPixelX((int) cameraPos.x) - 5;
  int endX = GetCellByPixelX((int) cameraPos.x + Camera::GetViewPortWidth()) + 5;

  int startY = GetCellByPixelY((int) cameraPos.y) - 5;
  int endY = GetCellByPixelY((int) cameraPos.y + Camera::GetViewPortHeight()) + 5;

  MapData const& mapData = _map.MapData();
  for(size_t i = 0; i < _vMap.getVertexCount(); ++i)
    _vMap[i] = sf::Vertex();
  int i = 0;
  for(auto it = mapData.begin(); it != mapData.end(); ++it)
  {
    Coords const cell = it->first;
    if(cell.x < startX || cell.x > endX || cell.y < startY || cell.y > endY)
      continue;
    int const tileID = _map[cell].TileID;
    Rectangle const sourceRect = TileSourceRectangle(tileID);
    Rectangle const screenRect = CellScreenRectangle(cell);

    _vMap[i + 0].position = Vector2(screenRect.left,
                                    screenRect.top);
    _vMap[i + 1].position = Vector2(screenRect.left,
                                    screenRect.top + screenRect.height);
    _vMap[i + 2].position = Vector2(screenRect.left + screenRect.width,
                                    screenRect.top + screenRect.height);
    _vMap[i + 3].position = Vector2(screenRect.left + screenRect.width,
                                    screenRect.top);

    _vMap[i + 0].texCoords = Vector2(sourceRect.left,
                                     sourceRect.top);
    _vMap[i + 1].texCoords = Vector2(sourceRect.left,
                                     sourceRect.top + sourceRect.height);
    _vMap[i + 2].texCoords = Vector2(sourceRect.left + sourceRect.width,
                                     sourceRect.top + sourceRect.height);
    _vMap[i + 3].texCoords = Vector2(sourceRect.left + sourceRect.width,
                                     sourceRect.top);
    i = i + 4;
  }

  renderTarget.draw(_vMap, &_tileSheet);
}

template<class TMap, class TCell, class TCodes>
int TileMap<TMap, TCell, TCodes>::GetTileWidth()
{
  return _tileWidth;
}

template<class TMap, class TCell, class TCodes>
int TileMap<TMap, TCell, TCodes>::GetTileHeight()
{
  return _tileHeight;
}

template<class TMap, class TCell, class TCodes>
int TileMap<TMap, TCell, TCodes>::GetMapWidth()
{
  return _map.MapWidth();
}

template<class TMap, class TCell, class TCodes>
int TileMap<TMap, TCell, TCodes>::GetMapHeight()
{
  return _map.MapHeight();
}

template<class TMap, class TCell, class TCodes>
int TileMap<TMap, TCell, TCodes>::GetCellByPixelX(float pixelX)
{
  float cell = pixelX/_tileWidth;
  return (cell < 0 && cell < (int)cell) ? (int)cell - 1 : (int)cell;
}

template<class TMap, class TCell, class TCodes>
int TileMap<TMap, TCell, TCodes>::GetCellByPixelY(float pixelY)
{
  float cell = pixelY/_tileHeight;
  return (cell < 0 && cell < (int)cell) ? (int)cell - 1 : (int)cell;
}

template<class TMap, class TCell, class TCodes>
sf::Vector2i TileMap<TMap, TCell, TCodes>::GetCellByPixel(Vector2 const& pixelLocation)
{
  return Coords(GetCellByPixelX(pixelLocation.x),
                GetCellByPixelY(pixelLocation.y));
}

template<class TMap, class TCell, class TCodes>
sf::Vector2f TileMap<TMap, TCell, TCodes>::GetCellCenter(Coords const& cell)
{
  return Vector2((cell.x*_tileWidth) + (_tileWidth/2.0f),
                 (cell.y*_tileHeight) + (_tileHeight/2.0f));
}

template<class TMap, class TCell, class TCodes>
sf::IntRect TileMap<TMap, TCell, TCodes>::CellWorldRectangle(Coords const& cell)
{
  int const rowOffset = (cell.y % 2 == 1) ? _oddRowXOffset : 0;
  return Rectangle((cell.x*_tileStepX) + rowOffset, cell.y*_tileStepY,
                   _tileWidth, _tileHeight);
}

template<class TMap, class TCell, class TCodes>
sf::IntRect TileMap<TMap, TCell, TCodes>::CellScreenRectangle(Coords const& cell)
{
  return Camera::WorldToScreen(CellWorldRectangle(cell));
}

template<class TMap, class TCell, class TCodes>
std::vector<TCodes>& TileMap<TMap, TCell, TCodes>::GetCellCodes(Coords const& cell)
{
  return _map.Codes()[cell];
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::SetCellCodes(Coords const& cell,
                                         CodeList const& codes)
{
  _map.Codes()[cell] = codes;
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::AddCodeToCell(Coords const& cell,
                                          TCodes const& code)
{
  _map.Codes()[cell].push_back(code);
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::RemoveCodeFromCell(Coords const& cell,
                                               TCodes const& code)
{
  CodeList& codes = _map.Codes()[cell];
  for(size_t i = 0;i < codes.size(); ++i)
    if(codes[i] == code)
      codes.erase(i--);
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::SetEverythingAtCell(TCell const& square,
                                                CodeList const& codes,
                                                Coords const& cell)
{
  _map[cell] = square;
  _map.Codes()[cell] = codes;
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::RemoveEverythingAtCell(Coords const& cell)
{
  _map.Codes().erase(cell);
  _map.MapData().erase(cell);
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::RemoveMapSquareAtCell(Coords const& cell)
{
  _map.MapData().erase(cell);
}

template<class TMap, class TCell, class TCodes>
TCell& TileMap<TMap, TCell, TCodes>::GetMapSquareAtCell(Coords const& cell)
{
  return _map[cell];
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::SetMapSquareAtCell(Coords const& cell,
                                               TCell const& square)
{
  _map[cell] = square;
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::SetTileAtCell(Coords const& cell, int tileIndex)
{
  _map[cell].TileID = tileIndex;
}

template<class TMap, class TCell, class TCodes>
TCell& TileMap<TMap, TCell, TCodes>::GetMapSquareAtPixel(
    Vector2 const& pixelLocation)
{
  return GetMapSquareAtCell(GetCellByPixelX(pixelLocation.x),
                            GetCellByPixelY(pixelLocation.y));
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::ClearMap()
{
  _map = TMap();
}

template<class TMap, class TCell, class TCodes>
TileMap<TMap, TCell, TCodes>& TileMap<TMap, TCell, TCodes>::GetInstance()
{
  if(_instance == 0)
    throw "There's no instance available, make sure you call the public constructor once!";
  return *_instance;
}

template<class TMap, class TCell, class TCodes>
sf::IntRect& TileMap<TMap, TCell, TCodes>::TileSourceRectangle(int tileIndex)
{
  return _tileSourceRects[tileIndex];
}

template<class TMap, class TCell, class TCodes>
TileMap<TMap, TCell, TCodes>* TileMap<TMap, TCell, TCodes>::_instance = 0;

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::LoadMap(sf::String location)
{
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::SaveMap(sf::String location)
{
}

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::SaveToFile(sf::String const& path)
{  using namespace sf;
  RenderTexture texture;
  Context context;
  int mapWidth(GetMapWidth());
  int mapHeight(GetMapHeight());

  texture.create(mapWidth * _tileWidth, mapHeight * _tileHeight);
  texture.clear(Color::Black);
  sf::VertexArray vMap(Quads, mapWidth * mapHeight * 4);
  for(int i = 0; i < mapWidth * mapHeight * 4; ++i)
    vMap[i] = Vertex();
  MapData const& mapData = _map.MapData();
  int i = 0;
  for(auto it = mapData.begin(); it != mapData.end(); ++it)
  {
    Coords const cell = it->first;
    int const tileID = _map[cell].TileID;
    Rectangle const sourceRect = TileSourceRectangle(tileID);
    Rectangle const worldRect = CellWorldRectangle(cell);
    vMap[i + 0].position = Vector2(worldRect.left,
                                    worldRect.top);
    vMap[i + 1].position = Vector2(worldRect.left,
                                    worldRect.top + worldRect.height);
    vMap[i + 2].position = Vector2(worldRect.left + worldRect.width,
                                    worldRect.top + worldRect.height);
    vMap[i + 3].position = Vector2(worldRect.left + worldRect.width,
                                    worldRect.top);

    vMap[i + 0].texCoords = Vector2(sourceRect.left,
                                     sourceRect.top);
    vMap[i + 1].texCoords = Vector2(sourceRect.left,
                                     sourceRect.top + sourceRect.height);
    vMap[i + 2].texCoords = Vector2(sourceRect.left + sourceRect.width,
                                     sourceRect.top + sourceRect.height);
    vMap[i + 3].texCoords = Vector2(sourceRect.left + sourceRect.width,
                                     sourceRect.top);
    i = i + 4;
  }
  texture.draw(vMap, &_tileSheet);
  texture.display();
  texture.getTexture().copyToImage().saveToFile(path);
}
