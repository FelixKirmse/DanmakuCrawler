#pragma once
#include <sys/timeb.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/Input.h"

namespace BlackDragonEngine
{
    using namespace std;
    using namespace sf;

    class Game
    {
        public:
            Game(String title = "Game", VideoMode windowSize = VideoMode(800,600));
            virtual ~Game() {}
            void Run(int ups = 30);
            void Quit();
            
        protected:
            virtual void LoadContent();
            virtual void Update();
            virtual void Draw(float interpolation, RenderTarget& renderTarget);
            virtual void Initialize();
            virtual void UnloadContent();


        private:
            int GetTicks();
            void HandleEvents();

            RenderWindow _graphics;
            bool _gameRunning;
    };
}
