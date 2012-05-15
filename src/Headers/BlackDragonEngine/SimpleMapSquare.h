#pragma once

namespace BlackDragonEngine
{
class SimpleMapSquare
{  
public:
  SimpleMapSquare(int tileID) : TileID(tileID), InvalidCell(false){}
  SimpleMapSquare() : TileID(0), InvalidCell(true){}
  int TileID;
  bool InvalidCell;
};
}
