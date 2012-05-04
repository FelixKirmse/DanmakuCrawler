
template<class T>
std::map<sf::String, T> Provider<T>::_dataMap;

template<class T>
T& Provider<T>::Get(sf::String const& name)
{
  return _dataMap[name];
}


