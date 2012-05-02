template<class TMap, class TCodes>
void Camera::UpdateWorldRectangle(TileMap<TMap, TCodes> const& tileMap)
{
  _worldRectangle = IntRect(tileMap.GetMap().LowestX()*tileMap.GetTileWidth(),
                            tileMap.GetMap().LowestY()*tileMap.GetTileHeight(),
                            tileMap.GetTileWidth*(tileMap.GetMapWidth() + 1),
                            tileMap.GetTileHeight*(tileMap.GetMapHeight() + 1));
}
