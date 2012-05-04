#include "BlackDragonEngine/StateManager.h"

namespace BlackDragonEngine
{
void StateManager::AddUpdateableState(UpdateablePtr const& state)
{
  _updateableGameStates.push_back(state);
}

void StateManager::AddDrawableState(DrawablePtr const& state)
{
  _drawableGameStates.push_back(state);
}

void StateManager::Update()
{
  for(size_t i = 0; i < _updateableGameStates.size(); ++i)
  {
    if(_updateableGameStates[i]->UpdateCondition())
      if(!_updateableGameStates[i]->Update()) return;
  }
}

void StateManager::Draw(float interpolation, sf::RenderTarget& renderTarget)
{
  for(size_t i = 0; i < _drawableGameStates.size(); ++i)
  {
    if(_drawableGameStates[i]->DrawCondition())
      _drawableGameStates[i]->Draw(interpolation, renderTarget);
  }
}
}
