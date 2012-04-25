#pragma once
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Game.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/TextureProvider.h"

namespace Danmaku
{
    using namespace std;
    using namespace BlackDragonEngine;

    class DanmakuGame : public Game
    {
        private:
            GameStateManager _stateManager; 

        protected:
            void LoadContent();
            void Initialize();
            void Update();
            void Draw(float interpolation, RenderTarget& renderTarget);

        public:
            static int const ResolutionWidth = 320;
            static int const ResolutionHeight = 240;

            DanmakuGame();
            void OnLevelLoad();
    };
}
