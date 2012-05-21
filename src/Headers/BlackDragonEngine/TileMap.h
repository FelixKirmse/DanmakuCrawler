#pragma once
#include <stdexcept>
#include <vector>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IMap.h"
#include "BlackDragonEngine/Camera.h"


namespace BlackDragonEngine
{
template<class TMap, class TCell, class TCodes>
class TileMap
{
public:
  typedef sf::Vector2i Coords;
  typedef sf::Vector2f Vector2;
  typedef sf::IntRect Rectangle;
  typedef std::vector<TCodes> CodeList;
  typedef std::vector<Rectangle> RectangleList;
  typedef boost::unordered::unordered_map<Coords, TCell> MapData;

  TileMap(int tileWidth, int tileHeight, int tileOffset, int tileStepX,
          int tileStepY, int oddRowXOffset,
          sf::Texture const& tileSheet, sf::Vector2i resolution);
  TMap& GetMap();

  void Draw(sf::RenderTarget& rendertarget);
  void SaveToFile(sf::String const& path);

  int GetTileWidth();
  int GetTileHeight();
  int GetMapWidth();
  int GetMapHeight();

  int GetCellByPixelX(float pixelX);
  int GetCellByPixelY(float pixelY);
  Coords GetCellByPixel(Vector2 const& pixelLocation);
  Vector2 GetCellCenter(Coords const& cell);
  Rectangle CellWorldRectangle(Coords const& cell);
  Rectangle CellScreenRectangle(Coords const& cell);

  CodeList& GetCellCodes(Coords const& cell);
  void SetCellCodes(Coords const& cell, CodeList const& codes);
  void AddCodeToCell(Coords const& cell, TCodes const& code);
  void RemoveCodeFromCell(Coords const& cell, TCodes const& code);

  void SetEverythingAtCell(TCell const&, CodeList const& codes,
                           Coords const& cell);
  void RemoveEverythingAtCell(Coords const& cell);

  void RemoveMapSquareAtCell(Coords const& cell);
  TCell& GetMapSquareAtCell(Coords const& cell);
  void SetMapSquareAtCell(Coords const& cell, TCell const& square);
  void SetTileAtCell(Coords const& cell, int tileIndex);
  TCell& GetMapSquareAtPixel(Vector2 const& pixelLocation);

  void ClearMap();
  void LoadMap(sf::String location);
  void SaveMap(sf::String location);

  static TileMap<TMap, TCell, TCodes>& GetInstance();

private:
  Rectangle& TileSourceRectangle(int tileIndex);

  int const _tileWidth;
  int const _tileHeight;
  int const _tileOffset;
  int const _tileStepX;
  int const _tileStepY;
  int const _oddRowXOffset;

  sf::Texture const& _tileSheet;
  int const _tilesPerRow;
  RectangleList _tileSourceRects;
  TMap _map;
  sf::VertexArray _vMap;

  static TileMap<TMap, TCell, TCodes>* _instance;
};

#include "BlackDragonEngine/Inline/TileMap.inl"

template<class TMap, class TCell, class TCodes>
void TileMap<TMap, TCell, TCodes>::SaveToFile(sf::String const& path)
{ /*
  using namespace sf;
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
  */
}
}
