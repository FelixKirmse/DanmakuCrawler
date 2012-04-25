#pragma once
#include <memory>
#include <map>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include <cassert>

namespace Danmaku
{
    using namespace std;
    using namespace sf;

    class TextureProvider
    {
        public:
            static void AddTexture(String const& name, String const& fileName);
            static Texture const& GetTexture(String const& name);

        private:
            static map<String, Texture> _textures;
    };
}
