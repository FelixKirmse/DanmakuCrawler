#include "Danmaku/CharSwitch.h"
#include "Danmaku/StatOverview.h"
#include <boost/format.hpp>

namespace Danmaku
{
sf::String const CharSwitch::PressSpaceBarString("Press Space to switch between Stat and Spell View.");
std::string const CharSwitch::PageFormatString("Page %d/%d");

int const CharSwitch::XLength(195);
sf::Vector2f const CharSwitch::PortraitOrigin(sf::Vector2f(45.f, 20.f));
int const CharSwitch::YOffSet(110);


CharSwitch::CharSwitch()
  : _spellSelectMenu(), _statOverview(StatOverview::GetInstance()),
    _showStats(true), _currentPage(1), _backDrop(sf::Vector2f(XLength, 480.f)),
    _switchString()
{
  _backDrop.setFillColor(sf::Color::Black);
}

void CharSwitch::ResetMenu()
{
  //TODO
}

void CharSwitch::Update()
{
  //TODO
}

void CharSwitch::Draw(sf::RenderTarget &renderTarget)
{
  //TODO
}

void CharSwitch::SelectMenuItem()
{
  //TODO
}

int CharSwitch::GetMaxPage()
{
  //TODO
}

void CharSwitch::ChangePage(int newPage)
{
  //TODO
}



}
