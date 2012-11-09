#include "Danmaku/CharSwitch.h"
#include "Danmaku/StatOverview.h"
#include <boost/format.hpp>
#include "Danmaku/CharGraphicsMenuItem.h"
#include "Danmaku/Party.h"
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/IFinishedNotifier.h"

namespace Danmaku
{
sf::String const CharSwitch::PressSpaceBarString("Press Space to switch between Stat and Spell View.");
std::string const CharSwitch::PageFormatString("Page %d/%d");
sf::String const CharSwitch::SpellDescription("This Character knows the following Spells.");

int const CharSwitch::XLength(195);
sf::Vector2f const CharSwitch::PortraitOrigin(sf::Vector2f(45.f, 20.f));
int const CharSwitch::YOffSet(110);


CharSwitch& CharSwitch::GetInstance()
{
  static CharSwitch instance;
  return instance;
}

CharSwitch::CharSwitch()
  : _spellSelectMenu(), _statOverview(StatOverview::GetInstance()),
    _showStats(true), _currentPage(1), _changedCharacter(true),
    _backDrop(sf::Vector2f(XLength, 480.f)),
    _switchString(PressSpaceBarString, BlackDragonEngine::Provider<sf::Font>::Get("Vera"), 13),
    _pageString("", BlackDragonEngine::Provider<sf::Font>::Get("Vera"), 13),
    _selectBattleParty(false)
{
  _backDrop.setFillColor(sf::Color::Black);  
  ItemOffset.y = YOffSet;
  _pageString.setColor(sf::Color::White);
  _switchString.setColor(sf::Color::White);
  _pageString.setPosition(70.f, 460.f);
}

void CharSwitch::ResetMenu()
{    
  ChangePage(1);
}

void CharSwitch::Update()
{
  using namespace BlackDragonEngine;
  Menu::Update();
  if(!_selectBattleParty && Input::Left(true) && _currentPage != 1)
    ChangePage(_currentPage - 1);
  if(!_selectBattleParty && Input::Right(true) && _currentPage < GetMaxPage())
    ChangePage(_currentPage + 1);
  if(Input::Jump(true))
    _showStats = !_showStats;
  if(Input::Cancel(true))
  {
    if(_selectedCharacter)
    {
      _selectedCharacter = false;
      ChangePage(1);
    }
    else
    {
      _notifier->WorkCancelled();
    }
  }

  if(_changedCharacter)
  {
    _spellSelectMenu.ResetMenu(GetSelectedCharacter());
    _spellSelectMenu.SetDescription(SpellDescription);
    _statOverview.Update(*GetSelectedCharacter());
    _changedCharacter = false;
  }
}

void CharSwitch::Draw(sf::RenderTarget& renderTarget)
{
  renderTarget.draw(_backDrop);
  renderTarget.draw(_switchString);
  renderTarget.draw(_pageString);
  Menu::Draw(renderTarget);
  if(_showStats)
    _statOverview.Draw(renderTarget);
  else
    _spellSelectMenu.Draw(renderTarget);
}

void CharSwitch::SelectMenuItem()
{
  if(!_selectBattleParty)
  {
    _selectedCharacter = GetSelectedIndex();   
    ShowBattleParty();
    return;
  }

  Party::SwitchChars(_selectedCharacter, GetSelectedIndex());
  _notifier->WorkFinished();
  ChangePage(1);
}

int CharSwitch::GetMaxPage()
{
  return Party::GetAvailableCharacters().size() / 4;
}

void CharSwitch::ChangePage(int newPage)
{
  ClearMenuItems();
  Party::CharVec& characters(Party::GetAvailableCharacters());
  size_t index = (newPage - 1) * 4;
  for(size_t i(index); i < (index) + 4; ++i)
  {
    CharGraphicsMenuItem* newItem = new CharGraphicsMenuItem(characters[i].Graphics(),
                                                             i);
    newItem->SetSelected(false);
    AddMenuItem(newItem);
  }

  SetPositions(PortraitOrigin, false, YOffSet);
  _currentPage = newPage;
  MenuItems.front()->SetSelected(true);
  _changedCharacter = true;
  boost::format pageString(PageFormatString);
  pageString
      % _currentPage
      % GetMaxPage();
  _pageString.setString(pageString.str());
  _selectBattleParty = false;
}

void CharSwitch::ShowBattleParty()
{
  ClearMenuItems();
  Party::FrontRow& characters(Party::GetFrontRow());
  for(size_t i(0); i < 4; ++i)
  {   
    CharGraphicsMenuItem* newItem = new CharGraphicsMenuItem(characters[i].Graphics(),
                                                             i);
    newItem->SetSelected(false);
    AddMenuItem(newItem);
  }
  SetPositions(PortraitOrigin, false, YOffSet);
  _currentPage = 1;
  MenuItems.front()->SetSelected(true);
  _changedCharacter = true;
  _selectBattleParty = true;

  boost::format pageString(PageFormatString);
  pageString
      % 1
      % 1;
  _pageString.setString(pageString.str());
}

Character* CharSwitch::GetSelectedCharacter()
{
  CharGraphicsMenuItem* selectedItem = NULL;
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(MenuItems[i]->IsSelected())
      selectedItem = dynamic_cast<CharGraphicsMenuItem*>(MenuItems[i]);
  }
  return (!_selectBattleParty) ?
            &Party::GetAvailableCharacters()[selectedItem->GetIndex()]
          : &Party::GetFrontRow()[selectedItem->GetIndex()];
}

int CharSwitch::GetSelectedIndex()
{
  CharGraphicsMenuItem* selectedItem = NULL;
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(MenuItems[i]->IsSelected())
      selectedItem = dynamic_cast<CharGraphicsMenuItem*>(MenuItems[i]);
  }
  return selectedItem->GetIndex();
}

int CharSwitch::GetSelectedMenuItemIndex()
{
  for(size_t i = 0; i < MenuItems.size(); ++i)
  {
    if(MenuItems[i]->IsSelected())
      return i;
  }
  return 0;
}

void CharSwitch::NextMenuItem()
{
  BlackDragonEngine::Menu::NextMenuItem();
  _changedCharacter = true;
}

void CharSwitch::PreviousMenuItem()
{
  BlackDragonEngine::Menu::PreviousMenuItem();
  _changedCharacter = true;
}

void CharSwitch::SetNotifier(IFinishedNotifier* notifier)
{
  _notifier = notifier;
}

void CharSwitch::SetPositions(sf::Vector2f position, bool centered, int offset)
{
  for(int i = 0; i < (int)MenuItems.size(); ++i)
  {    
    MenuItems[i]->SetPosition(position + sf::Vector2f(i, (i * offset)));
  }
}

}
