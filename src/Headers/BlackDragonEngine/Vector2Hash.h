#pragma once
#include <SFML/System.hpp>

namespace sf
{
template<class T>
size_t hash_value(sf::Vector2<T> const& vec)
{
  return vec.x ^ vec.y;
}
}
