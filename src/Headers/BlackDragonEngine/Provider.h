#pragma once
#include <map>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

namespace BlackDragonEngine
{
using namespace std;
using namespace sf;

template<class T>
class Provider
{
public:
  static T& Get(String const& name);

private:
  static map<String, T> _dataMap;
};

template<class T>
map<String, T> Provider<T>::_dataMap;

template<class T>
T& Provider<T>::Get(String const& name)
{
  return _dataMap[name];
}

}
