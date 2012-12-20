template<class T>
void Battle::SetInitialSPD(T& vec)
{
  for(size_t i = 0; i < vec.size(); ++i)
  {
    vec[i]->TurnCounter() = vec[i]->GetStats().BaseStats[SPD][0];
    vec[i]->Graphics().UpdateSPD(false);
  }
}
