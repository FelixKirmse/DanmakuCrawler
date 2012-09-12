#pragma once
#include <SFML/Graphics.hpp>
#include "Danmaku/Stats.h"

namespace Danmaku
{
class Character;

class StatOverview
{
public:
  static StatOverview& GetInstance();

  void Update(Character &chara);
  void Draw(sf::RenderTarget& rTarget);
private:
  StatOverview();
  StatOverview(StatOverview const&);
  void operator=(StatOverview const&);

  int Stat(BaseStat stat);
  int Stat(EleMastery stat);
  int Stat(DebuffResistance stat);
  int Str(BaseStat stat);
  int Str(EleMastery stat);
  int Str(DebuffResistance stat);


  sf::RectangleShape _backdrop;
  sf::Text _baseStatText;
  sf::Text _masteryText;
  sf::Text _resiText;
  sf::Text _bonusText;
  sf::Text _baseStatValues;
  sf::Text _masteryValues;
  sf::Text _resiValues;
  sf::Text _bonusValues;

  sf::Text _nameLabel;
  sf::Text _levelLabel;
  sf::Text _statsLabel;
  sf::Text _bonusLabel;
  sf::Text _masteriesLabel;
  sf::Text _resistanceLabel;
  sf::Text _evaTypeLabel;
  sf::Text _afflictedByLabel;
  sf::Text _dodgeLabel;
  sf::Text _blockLabel;
  sf::Text _nothingLabel;
  sf::Text _psnLabel;
  sf::Text _silLabel;

  //sf::Color const BuffColor;
  //sf::Color const DebuffColor;
  sf::Color const PsnColor;
  sf::Color const SilColor;
  sf::Color const NothingColor;
  sf::Color const NotAppliedColor;

  int const LabelX;
  int const ValueX;
  int const SecondRowX;
  int const SecondRowValueX;
  int const BaseY;
  int const MasteryResiY;


  std::string const FormatStringBaseValues;
  std::string const FormatStringBaseBoni;
  std::string const FormatStringMasteriesValues;
  std::string const FormatStringResiValues;
  sf::String const NameLabel;
  sf::String const LevelLabel;

  bool _dodge;

  Stats* _statCache;
};
}
