template<class Archive>
void Stats::serialize(Archive& ar, unsigned int const version)
{
  ar & BOOST_SERIALIZATION_NVP(BaseStats);
  ar & BOOST_SERIALIZATION_NVP(Masteries);
  ar & BOOST_SERIALIZATION_NVP(Resistances);
}
