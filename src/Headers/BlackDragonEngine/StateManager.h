#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"

namespace BlackDragonEngine
{
class StateManager
{
public:
  typedef std::shared_ptr<IDrawableGameState> DrawablePtr;
  typedef std::shared_ptr<IUpdateableGameState> UpdateablePtr;
  typedef std::vector<DrawablePtr> DrawableList;
  typedef std::vector<UpdateablePtr> UpdateableList;

  virtual ~StateManager() {}
  void AddUpdateableState(UpdateablePtr const& state);
  void AddDrawableState(DrawablePtr const& state);
  void Update();
  void Draw(float interpolation, sf::RenderTarget& renderTarget);

private:
  DrawableList _drawableGameStates;
  UpdateableList _updateableGameStates;
};
}
