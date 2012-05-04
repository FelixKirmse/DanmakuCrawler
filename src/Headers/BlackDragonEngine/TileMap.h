#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IMap.h"
#include "BlackDragonEngine/Camera.h"

namespace BlackDragonEngine
{
template<class TMap, class TCodes>
class TileMap
{
public:
  typedef sf::Vector2i Coords;
  typedef sf::Vector2f Vector2;
  typedef sf::IntRect Rectangle;
  typedef std::vector<TCodes> CodeList;
  typedef std::vector<Rectangle> RectangleList;
  typedef boost::unordered_map<Coords, SimpleMapSquare> MapData;

  TileMap(int tileWidth, int tileHeight, int tileOffset,
          sf::Texture const& tileSheet);
  TMap& GetMap();

  void Draw(sf::RenderTarget& rendertarget);

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

  void SetEverythingAtCell(SimpleMapSquare const&, CodeList const& codes,
                           Coords const& cell);
  void RemoveEverythingAtCell(Coords const& cell);

  void RemoveMapSquareAtCell(Coords const& cell);
  SimpleMapSquare& GetMapSquareAtCell(Coords const& cell);
  void SetMapSquareAtCell(Coords const& cell, SimpleMapSquare const& square);
  void SetTileAtCell(Coords const& cell, int tileIndex);
  SimpleMapSquare& GetMapSquareAtPixel(Vector2 const& pixelLocation);

  void ClearMap();
  void LoadMap(sf::String location);
  void SaveMap(sf::String location);

  static TileMap<TMap, TCodes>& GetInstance();

private:
  Rectangle& TileSourceRectangle(int tileIndex);

  int const _tileWidth;
  int const _tileHeight;
  int const _tileOffset;
  sf::Texture const& _tileSheet;
  int const _tilesPerRow;
  RectangleList _tileSourceRects;
  TMap _map;
  sf::VertexArray _vMap;

  static TileMap<TMap, TCodes>* _instance;
};

#include "BlackDragonEngine/Inline/TileMap.inl"


}
