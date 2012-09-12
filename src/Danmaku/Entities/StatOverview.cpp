#include "Danmaku/StatOverview.h"
#include "Danmaku/Character.h"
#include "BlackDragonEngine/Provider.h"
#include <string>
#include <boost/format.hpp>


namespace Danmaku
{
using namespace BlackDragonEngine;
int const FONTSIZE(11);
sf::Font const& FONT(Provider<sf::Font>::Get("Vera"));
std::string const formatStringBase =
    "HP:\n"
    "MP:\n"
    "AD:\n"
    "MD:\n"
    "DEF:\n"
    "MR:\n"
    "EVA:\n"
    "SPD:\n"
    "CHA:\n";

std::string const formatStringBaseValues =
    "%d/%d\n"
    "%d/%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n";

std::string const formatStringBaseBoni =
    "%d%%\n"
    "%d%%\n"
    "%d%%\n"
    "%d%%\n"
    "%d%%\n"
    "%d%%\n"
    "%d%%\n"
    "%d%%\n"
    "%d%%\n";

std::string const formatStringMasteries =
    "FIR:\n"
    "WAT:\n"
    "ICE:\n"
    "ARC:\n"
    "WND:\n"
    "HOL:\n"
    "DRK:\n"
    "GRN:\n"
    "LGT:\n";

std::string const formatStringMasteriesValues =
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n";
std::string const formatStringResi =
    "DOT:\n"
    "PAR:\n"
    "SIL:\n"
    "DTH:\n";

std::string const formatStringResiValues =
    "%d\n"
    "%d\n"
    "%d\n"
    "%d\n";



StatOverview& StatOverview::GetInstance()
{
  static StatOverview instance;
  return instance;
}

StatOverview::StatOverview()
  : _backdrop(sf::Vector2f(390 + 75, 355)),
    _baseStatText(formatStringBase, FONT, FONTSIZE),
    _masteryText(formatStringMasteries, FONT, FONTSIZE),
    _resiText(formatStringResi, FONT, FONTSIZE), _bonusText("", FONT, FONTSIZE),
    _baseStatValues("", FONT, FONTSIZE), _masteryValues("", FONT, FONTSIZE),
    _resiValues("", FONT, FONTSIZE), _bonusValues("", FONT, FONTSIZE),
    _nameLabel("Name:", FONT, FONTSIZE),
    _levelLabel("Level :", FONT, FONTSIZE),
    _statsLabel("Stats:", FONT, FONTSIZE),
    _bonusLabel("Strength:", FONT, FONTSIZE),
    _masteriesLabel("Elemental Masteries:", FONT, FONTSIZE),
    _resistanceLabel("Status Resistances:", FONT, FONTSIZE),
    _evaTypeLabel("Type of EVA:", FONT, FONTSIZE),
    _afflictedByLabel("Currently afflicted by:", FONT, FONTSIZE),
    _dodgeLabel("Dodge", FONT, FONTSIZE), _blockLabel("Block", FONT, FONTSIZE),
    _nothingLabel("Nothing", FONT, FONTSIZE), _psnLabel("DOT", FONT, FONTSIZE),
    _silLabel("SIL", FONT, FONTSIZE),
    PsnColor(243u, 69u, 255u), SilColor(28u, 58u, 255u),
    NothingColor(sf::Color::White), NotAppliedColor(128u, 128u, 128u),
    LabelX(260 + 75), ValueX(300 + 75), SecondRowX(435 + 75), SecondRowValueX(470 + 75),
    BaseY(55), MasteryResiY(195),
    FormatStringBaseValues(formatStringBaseValues),
    FormatStringBaseBoni(formatStringBaseBoni),
    FormatStringMasteriesValues(formatStringMasteriesValues),
    FormatStringResiValues(formatStringResiValues),
    NameLabel("Name: "), LevelLabel("Level: "), _dodge(true), _statCache(0)
{
  _backdrop.setPosition(240 + 75, 15);
  _backdrop.setFillColor(sf::Color::Black);
  _baseStatText.setPosition(LabelX, BaseY);
  _masteryText.setPosition(LabelX, MasteryResiY);
  _resiText.setPosition(SecondRowX, MasteryResiY);
  _bonusText.setPosition(LabelX, BaseY);
  _baseStatValues.setPosition(ValueX, BaseY);
  _masteryValues.setPosition(ValueX, MasteryResiY);
  _resiValues.setPosition(SecondRowValueX, MasteryResiY);
  _bonusValues.setPosition(SecondRowX, BaseY);
  _nameLabel.setPosition(LabelX, 20);
  _levelLabel.setPosition(425 + 75, 20);
  _statsLabel.setPosition(250 + 75, 40);
  _bonusLabel.setPosition(425 + 75, 40);
  _masteriesLabel.setPosition(250 + 75, 180);
  _resistanceLabel.setPosition(425 + 75, 180);
  _evaTypeLabel.setPosition(425 + 75, 260);
  _afflictedByLabel.setPosition(250 + 75, 325);
  _dodgeLabel.setPosition(SecondRowX, 280);
  _blockLabel.setPosition(SecondRowX, 280);
  _nothingLabel.setPosition(395 + 75, 325);
  _psnLabel.setPosition(450 + 75, 325);
  _silLabel.setPosition(485 + 75, 325);

  _nothingLabel.setColor(NothingColor);
  _psnLabel.setColor(NotAppliedColor);
  _silLabel.setColor(NotAppliedColor);
}

void StatOverview::Update(Character& chara)
{
  using namespace boost;
  Stats& stats = chara.GetStats();
  _statCache = &stats;
  _nameLabel.setString(NameLabel + chara.GetDisplayName());
  _levelLabel.setString(LevelLabel + std::to_string(chara.GetLvl()));
  format baseStatValues(FormatStringBaseValues);
  baseStatValues
      % (int)chara.CurrentHP()
      % Stat(HP)
      % (int)chara.CurrentMP()
      % Stat(MP)
      % Stat(AD)
      % Stat(MD)
      % Stat(DEF)
      % Stat(MR)
      % Stat(EVA)
      % Stat(SPD)
      % Stat(CHA);
  _baseStatValues.setString(baseStatValues.str());

  format baseStatBoni(FormatStringBaseBoni);
  baseStatBoni
      % (int)((chara.CurrentHP() / Stat(HP)) * 100)
      % (int)((chara.CurrentMP() / Stat(MP)) * 100)
      % Str(AD)
      % Str(MD)
      % Str(DEF)
      % Str(MR)
      % Str(EVA)
      % Str(SPD)
      % Str(CHA);
  _bonusValues.setString(baseStatBoni.str());

  format masteryValues(FormatStringMasteriesValues);
  masteryValues
      % Stat(FIR)
      % Stat(WAT)
      % Stat(ICE)
      % Stat(ARC)
      % Stat(WND)
      % Stat(HOL)
      % Stat(DRK)
      % Stat(GRN)
      % Stat(LGT);
  _masteryValues.setString(masteryValues.str());

  format resiValues(FormatStringResiValues);
  resiValues
      % Stat(PSN)
      % Stat(PAR)
      % Stat(SIL)
      % Stat(DTH);
  _resiValues.setString(resiValues.str());

  _dodge = stats.EVAType == Stats::Dodge;

  bool silenced(chara.IsSilenced());
  bool poisoned(chara.IsPoisoned());

  _psnLabel.setColor(poisoned ? PsnColor : NotAppliedColor);
  _silLabel.setColor(silenced ? SilColor : NotAppliedColor);
  _nothingLabel.setColor(poisoned || silenced ? NotAppliedColor : NothingColor);
}

void StatOverview::Draw(sf::RenderTarget& rTarget)
{
  rTarget.draw(_backdrop);
  rTarget.draw(_baseStatText);
  rTarget.draw(_masteryText);
  rTarget.draw(_resiText);
  rTarget.draw(_bonusText);
  rTarget.draw(_baseStatValues);
  rTarget.draw(_masteryValues);
  rTarget.draw(_resiValues);
  rTarget.draw(_bonusValues);

  rTarget.draw(_nameLabel);
  rTarget.draw(_levelLabel);
  rTarget.draw(_statsLabel);
  rTarget.draw(_bonusLabel);
  rTarget.draw(_masteriesLabel);
  rTarget.draw(_resistanceLabel);
  rTarget.draw(_evaTypeLabel);
  rTarget.draw(_afflictedByLabel);
  if(_dodge)
    rTarget.draw(_dodgeLabel);
  else
    rTarget.draw(_blockLabel);
  rTarget.draw(_nothingLabel);
  rTarget.draw(_psnLabel);
  rTarget.draw(_silLabel);
}

int StatOverview::Stat(BaseStat stat)
{
  return _statCache->GetTotalBaseStat(stat);
}

int StatOverview::Stat(EleMastery stat)
{
  return _statCache->GetTotalMastery(stat);
}

int StatOverview::Stat(DebuffResistance stat)
{
  return _statCache->GetTotalResistance(stat);
}

int StatOverview::Str(BaseStat stat)
{
  return _statCache->BaseStats[stat][4] * 100;
}

int StatOverview::Str(EleMastery stat)
{
  return _statCache->Masteries[stat][4] * 100;
}

int StatOverview::Str(DebuffResistance stat)
{
  return _statCache->Resistances[stat][4] * 100;
}

}
