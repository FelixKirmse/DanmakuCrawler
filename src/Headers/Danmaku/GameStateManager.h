#pragma once
#include "BlackDragonEngine/StateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/TitleScreen.h"

namespace Danmaku
{
    using namespace BlackDragonEngine;

    class GameStateManager : public StateManager
    {
        private:
            static States _state;
            static bool _playerDead;
            static bool _fastDead;

        public:
            GameStateManager();
            void Initialize();
            static States GetState();
            static void SetState(States state);
            static bool GetPlayerDead();
            static void SetPlayerDead(bool dead);
            static bool GetFastDead();
    };
}
