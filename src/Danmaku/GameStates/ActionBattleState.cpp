#include "Danmaku/ActionBattleState.h"
#include "Danmaku/Battle.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Spells/ISpell.h"

namespace Danmaku
{
std::string const ActionBattleState::CastTextFormatString = "%s uses %s on %s!";
std::string const ActionBattleState::Allies("all allies");
std::string const ActionBattleState::Enemies("all enemies");
std::string const ActionBattleState::Decaying("%s's allies");
std::string const ActionBattleState::Self("self");

ActionBattleState::ActionBattleState()
  : _castText(), _castDisplay(sf::Vector2f(640.f, 25.f))
{
  _castDisplay.setFillColor(sf::Color::Black);
  _castText.setCharacterSize(13u);
  _castText.setColor(sf::Color::White);
  _castText.setFont(BlackDragonEngine::Provider<sf::Font>::Get("Vera"));
}

void ActionBattleState::Update(Battle& battle)
{
  ++_frameCounter;
  if(_frameCounter == 90)
  {
    _frameCounter = 0;
    battle.ShowConsequences();
    return;
  }
  if(_frameCounter == 1)
  {
    using namespace boost;
    std::string targetString;
    TargetInfo& targetInfo = battle.GetTargetInfo();

    switch(targetInfo.Spell->GetTargetType())
    {
    case TargetInfo::Allies:
      targetString = Allies;
      break;

    case TargetInfo::Enemies:
      targetString = Enemies;
      break;

    case TargetInfo::Self:
      targetString = Self;
      break;

    case TargetInfo::Single:
      targetString = targetInfo.Target->GetDisplayName().toAnsiString();
      break;

    case TargetInfo::Decaying:
      format decayString(Decaying);
      decayString
          % targetInfo.Target->GetDisplayName().toAnsiString();
      targetString = decayString.str();
      break;
    }


    format formatString(CastTextFormatString);
    formatString
        % battle.GetCurrentAttacker()->GetDisplayName().toAnsiString()
        % targetInfo.Spell->GetName().toAnsiString()
        % targetString;

    _castText.setString(formatString.str());
    _castText.setPosition(sf::Vector2f(
                            (int)(320.f - _castText.getLocalBounds().width * .5f),
                            5.f));
  }
}

void ActionBattleState::Draw(Battle& battle, sf::RenderTarget& rTarget)
{
  rTarget.draw(_castDisplay);
  rTarget.draw(_castText);
}
}
