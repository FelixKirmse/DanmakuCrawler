template<class TMap, class TCell, class TCodes>
void Camera::UpdateWorldRectangle(TileMap<TMap, TCell, TCodes>& tileMap)
{
  _worldRectangle = Rectangle(tileMap.GetMap().LowestX()*tileMap.GetTileWidth(),
                            tileMap.GetMap().LowestY()*tileMap.GetTileHeight(),
                            tileMap.GetTileWidth()*(tileMap.GetMapWidth() + 1),
                            tileMap.GetTileHeight()*(tileMap.GetMapHeight() + 1));
}
