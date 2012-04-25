#pragma once
#include <SFML/Graphics.hpp>

namespace BlackDragonEngine
{
    using namespace sf;

    class IDrawableGameState
    {
        public:
            virtual ~IDrawableGameState() {}
            virtual bool DrawCondition() = 0;
            virtual void Draw(float interpolation, RenderTarget& renderTarget) = 0;
    };
}
