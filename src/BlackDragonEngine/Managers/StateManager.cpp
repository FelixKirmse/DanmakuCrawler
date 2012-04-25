#include "BlackDragonEngine/StateManager.h"

namespace BlackDragonEngine
{
StateManager::StateManager()
  : _drawableGameStates(), _updateableGameStates()
{
}

void StateManager::AddUpdateableState(shared_ptr<IUpdateableGameState> const& state)
{
  _updateableGameStates.push_back(state);
}

void StateManager::AddDrawableState(shared_ptr<IDrawableGameState> const& state)
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

void StateManager::Draw(float interpolation, RenderTarget& renderTarget)
{
  for(size_t i = 0; i < _drawableGameStates.size(); ++i)
  {
    if(_drawableGameStates[i]->DrawCondition())
      _drawableGameStates[i]->Draw(interpolation, renderTarget);
  }
}
}
