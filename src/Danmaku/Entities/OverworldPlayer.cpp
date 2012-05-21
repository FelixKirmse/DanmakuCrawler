#include "Danmaku/OverworldPlayer.h"

namespace Danmaku
{
OverworldPlayer::OverworldPlayer(sf::Texture& texture)
  : _currentTile(0,0), _moveVector(0,0), _position(0,0), _moveState(Idle),
    _sprite(texture), _stepsTaken(0), _drawOffset(texture.getSize().x/2.f,
                                                  texture.getSize().y/2.f),
    _cameraOffset(BlackDragonEngine::Camera::GetViewPortWidth() / 2.f,
                  BlackDragonEngine::Camera::GetViewPortHeight() / 2.f),
    _mapGen(DanmakuMap::GetInstance()),
    _encounterRate(BlackDragonEngine::Provider<sf::Font>::Get("Vera"))
{
  SetPlayerAtCell(sf::Vector2i(0,0));
}

void OverworldPlayer::Update()
{
  using namespace BlackDragonEngine;
  sf::Vector2i targetTile(_currentTile);
  switch(_moveState)
  {
  case Idle:
    if(Input::Up() && ValidMovement(sf::Vector2i(targetTile.x,
                                                 targetTile.y - 1),
                                    MapCell::Up))
      targetTile.y -= 1;
    else if(Input::Down() && ValidMovement(sf::Vector2i(targetTile.x,
                                                        targetTile.y + 1),
                                           MapCell::Down))
      targetTile.y += 1;
    else if(Input::Left() && ValidMovement(sf::Vector2i(targetTile.x - 1,
                                                        targetTile.y),
                                           MapCell::Left))
      targetTile.x -= 1;
    else if(Input::Right() && ValidMovement(sf::Vector2i(targetTile.x + 1,
                                                         targetTile.y),
                                            MapCell::Right))
      targetTile.x += 1;
    if(targetTile != _currentTile)
    {
      _moveVector = (DanmakuMap::GetInstance()
                     .GetCellCenter(targetTile) - _position) / 5.f;
      _moveState = Moving;
      _currentTile = targetTile;      
    }
    break;
  case Moving:
    _position += _moveVector;
    ++_stepsTaken;
    _sprite.setPosition(_position - _drawOffset);
    Camera::ForcePosition(_position - _cameraOffset);
    if(_stepsTaken == 5)
    {
      _moveState = Idle;
      _stepsTaken = 0;
      _mapGen.GenerateStep(targetTile);
      _encounterRate.Step();
      Update(); //For smooth movement
    }
    break;
  }
}

bool OverworldPlayer::ValidMovement(sf::Vector2i const& desired,
                                    MapCell::Direction direction)
{
  DanmakuMap& tileMap = DanmakuMap::GetInstance();
  MapCell& currentCell = tileMap.GetMapSquareAtCell(_currentTile);
  MapCell& desiredCell = tileMap.GetMapSquareAtCell(desired);
  if(desiredCell.InvalidCell)
  {
    tileMap.GetMap().MapData().erase(desired);
    return false;
  }

  return currentCell.IsTraversible(desiredCell, direction);
}

void OverworldPlayer::Draw(sf::RenderTarget& renderTarget)
{
  using namespace BlackDragonEngine;
  sf::Vector2f position = _sprite.getPosition();
  _sprite.setPosition(Camera::WorldToScreen(position));
  renderTarget.draw(_sprite);
  _sprite.setPosition(position);
  _encounterRate.Draw(renderTarget);
}

void OverworldPlayer::SetPlayerAtCell(sf::Vector2i const& cell)
{
  _position = DanmakuMap::GetInstance().GetCellCenter(cell);
  _sprite.setPosition(_position - _drawOffset);
  BlackDragonEngine::Camera::ForcePosition(_position - _cameraOffset);
}

OverworldPlayer& OverworldPlayer::operator=(OverworldPlayer const& source)
{
  _currentTile = source._currentTile;
  _moveVector = source._moveVector;
  _position = source._position;
  _moveState = source._moveState;
  _sprite = source._sprite;
  _stepsTaken = source._stepsTaken;
  _mapGen = source._mapGen;
  _encounterRate = source._encounterRate;
  return *this;
}

}
