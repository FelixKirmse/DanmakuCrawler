#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IMap.h"
#include "BlackDragonEngine/Camera.h"

namespace BlackDragonEngine
{
using namespace sf;
using namespace std;

template<class TMap, class TCodes>
class TileMap
{
public:
  TileMap(int tileWidth, int tileHeight, int tileOffset,
          Texture const& tileSheet);
  TMap& GetMap();

  void Draw(RenderTarget& rendertarget);

  int GetTileWidth();
  int GetTileHeight();
  int GetMapWidth();
  int GetMapHeight();

  int GetCellByPixelX(float pixelX);
  int GetCellByPixelY(float pixelY);
  Vector2i GetCellByPixel(Vector2f const& pixelLocation);
  Vector2f GetCellCenter(Vector2i const& cell);
  IntRect CellWorldRectangle(Vector2i const& cell);
  IntRect CellScreenRectangle(Vector2i const& cell);

  vector<TCodes>& GetCellCodes(Vector2i const& cell);
  void SetCellCodes(Vector2i const& cell, vector<TCodes> const& codes);
  void AddCodeToCell(Vector2i const& cell, TCodes const& code);
  void RemoveCodeFromCell(Vector2i const& cell, TCodes const& code);

  void SetEverythingAtCell(SimpleMapSquare const&, vector<TCodes> const& codes,
                           Vector2i const& cell);
  void RemoveEverythingAtCell(Vector2i const& cell);

  void RemoveMapSquareAtCell(Vector2i const& cell);
  SimpleMapSquare& GetMapSquareAtCell(Vector2i const& cell);
  void SetMapSquareAtCell(Vector2i const& cell, SimpleMapSquare const& square);
  void SetTileAtCell(Vector2i const& cell, int tileIndex);
  SimpleMapSquare& GetMapSquareAtPixel(Vector2f const& pixelLocation);

  void ClearMap();
  void LoadMap(String location);
  void SaveMap(String location);

  static TileMap<TMap, TCodes>& GetInstance();

private:
  IntRect& TileSourceRectangle(int tileIndex);

  int const _tileWidth;
  int const _tileHeight;
  int const _tileOffset;
  Texture const& _tileSheet;
  int const _tilesPerRow;
  vector<IntRect> _tileSourceRects;
  TMap _map;
  VertexArray _vMap;

  static TileMap<TMap, TCodes>* _instance;
};

#include "BlackDragonEngine/Inline/TileMap.inl"
}
