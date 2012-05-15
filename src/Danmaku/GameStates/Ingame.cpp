#include "Danmaku/Ingame.h"

namespace Danmaku
{
Ingame::Ingame()
  : _tileMap(DanmakuMap::GetInstance()),
             _player(BlackDragonEngine::Provider<sf::Texture>::Get("OverworldPlayer"))
{
  typedef boost::unordered_map<sf::Vector2i, MapCell> TileMap;

  TileMap& mapData = _tileMap.GetMap().MapData();
  mapData[sf::Vector2i(0,0)] = MapCell(TileList::CDownRight);
  mapData[sf::Vector2i(1,0)] = MapCell(TileList::SH);
  mapData[sf::Vector2i(2,0)] = MapCell(TileList::SH);
  mapData[sf::Vector2i(3,0)] = MapCell(TileList::CLeftDown);
  mapData[sf::Vector2i(3,1)] = MapCell(TileList::SV);
  mapData[sf::Vector2i(3,2)] = MapCell(TileList::SV);
  mapData[sf::Vector2i(3,3)] = MapCell(TileList::CLeftUp);
  mapData[sf::Vector2i(0,1)] = MapCell(TileList::SV);
  mapData[sf::Vector2i(0,2)] = MapCell(TileList::SV);
  mapData[sf::Vector2i(0,3)] = MapCell(TileList::CUpRight);
  mapData[sf::Vector2i(1,3)] = MapCell(TileList::SH);
  mapData[sf::Vector2i(2,3)] = MapCell(TileList::SH);
  _tileMap.LoadMap("");
  BlackDragonEngine::Camera::UpdateWorldRectangle(_tileMap);
  _player.SetPlayerAtCell(sf::Vector2i(0,0));
}

bool Ingame::UpdateCondition()
{
  return GameStateManager::GetState() == GameStates::Ingame;
}

bool Ingame::Update()
{
  using namespace BlackDragonEngine;
  _player.Update();
  return false;
}

bool Ingame::DrawCondition()
{
  GameStates::States state(GameStateManager::GetState());
  return state == GameStates::Ingame;
}

void Ingame::Draw(float interpolation, sf::RenderTarget& renderTarget)
{
  _tileMap.Draw(renderTarget);
  _player.Draw(renderTarget);
}
}
