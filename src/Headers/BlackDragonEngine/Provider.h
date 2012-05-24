#pragma once
#include <map>
#include "SFML/System.hpp"

namespace BlackDragonEngine
{
template<class T>
class Provider
{
public:
  static T& Get(sf::String const& name);

private:
  static std::map<sf::String, T> _dataMap;
};

#include "BlackDragonEngine/Inline/Provider.inl"

}
