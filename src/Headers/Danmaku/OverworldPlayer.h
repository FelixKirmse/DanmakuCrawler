#pragma once
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/TileMap.h"
#include "BlackDragonEngine/Map.h"
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Camera.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/TileCode.h"
#include "Danmaku/TileList.h"
#include "Danmaku/MapCell.h"
#include "Danmaku/MapGen.h"
#include "Danmaku/EncounterRate.h"

namespace Danmaku
{
class OverworldPlayer
{
public:
  typedef BlackDragonEngine::TileMap<BlackDragonEngine::Map<MapCell, TileCode>,
  MapCell, TileCode> DanmakuMap;

  OverworldPlayer(sf::Texture& texture);
  void Update();
  void Draw(sf::RenderTarget& renderTarget);

  void SetPlayerAtCell(sf::Vector2i const& cell);

  OverworldPlayer& operator=(OverworldPlayer const& source);

private:
  bool ValidMovement(sf::Vector2i const& desired, MapCell::Direction direction);

  sf::Vector2i _currentTile;
  sf::Vector2f _moveVector;
  sf::Vector2f _position;
  enum
  {
    Idle,
    Moving
  } _moveState;
  sf::Sprite _sprite;
  int _stepsTaken;
  sf::Vector2f const _drawOffset;
  sf::Vector2f const _cameraOffset;
  MapGen _mapGen;
  EncounterRate _encounterRate;
};
}

