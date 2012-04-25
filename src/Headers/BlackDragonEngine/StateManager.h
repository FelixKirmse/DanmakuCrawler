#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "BlackDragonEngine/IUpdateableGameState.h"
#include "BlackDragonEngine/IDrawableGameState.h"

namespace BlackDragonEngine
{
    using namespace std;

    class StateManager
    {
        private:
            vector<shared_ptr<IDrawableGameState>> _drawableGameStates;
            vector<shared_ptr<IUpdateableGameState>> _updateableGameStates;

        protected:
            StateManager();

        public:
            virtual ~StateManager() {}
            void AddUpdateableState(shared_ptr<IUpdateableGameState> const& state);
            void AddDrawableState(shared_ptr<IDrawableGameState> const& state);
            void Update();
            void Draw(float interpolation, RenderTarget& renderTarget);
    };
}
