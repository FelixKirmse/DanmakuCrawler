#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"

namespace BlackDragonEngine
{
typedef std::shared_ptr<IDrawableGameState> DrawablePtr;
typedef std::shared_ptr<IUpdateableGameState> UpdateablePtr;
using std::vector;

class StateManager
{
private:
  vector<DrawablePtr> _drawableGameStates;
  vector<UpdateablePtr> _updateableGameStates;

protected:
  StateManager();

public:
  virtual ~StateManager() {}
  void AddUpdateableState(UpdateablePtr const& state);
  void AddDrawableState(DrawablePtr const& state);
  void Update();
  void Draw(float interpolation, RenderTarget& renderTarget);
};
}
