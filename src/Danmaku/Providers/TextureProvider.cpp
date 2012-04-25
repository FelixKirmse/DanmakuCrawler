#include "Danmaku/TextureProvider.h"

namespace Danmaku
{
map<String, Texture> TextureProvider::_textures;

void TextureProvider::AddTexture(String const& name, String const& fileName)
{
  _textures.insert(pair<String, Texture>(name, Texture()));
  assert(_textures[name].loadFromFile(fileName));
}

Texture const& TextureProvider::GetTexture(String const& name)
{
  return _textures[name];
}
}
