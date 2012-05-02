
template<class T>
map<String, T> Provider<T>::_dataMap;

template<class T>
T& Provider<T>::Get(String const& name)
{
  return _dataMap[name];
}


