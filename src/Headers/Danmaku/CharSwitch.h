#pragma once
#include "Danmaku/SpellSelectMenu.h"
#include "BlackDragonEngine/Menu.h"

namespace Danmaku
{
class StatOverview;
class IFinishedNotifier;

class CharSwitch : public BlackDragonEngine::Menu
{
public:
  static CharSwitch& GetInstance();

  void ResetMenu();
  void Update();
  void Draw(sf::RenderTarget& renderTarget);
  void SelectMenuItem();
  void NextMenuItem();
  void PreviousMenuItem();

  void SetNotifier(IFinishedNotifier* notifier);

protected:
  void SetPositions(sf::Vector2f position,
                    bool centered = true, int offset = -2);
private:
  CharSwitch();

  int GetMaxPage();
  void ChangePage(int newPage);
  void ShowBattleParty();

  Character* GetSelectedCharacter();
  int GetSelectedIndex();
  int GetSelectedMenuItemIndex();

  SpellSelectMenu _spellSelectMenu;
  StatOverview& _statOverview;

  bool  _showStats;
  int _currentPage;
  bool _changedCharacter;

  size_t _selectedCharacter;

  sf::RectangleShape _backDrop;
  sf::Text _switchString;
  sf::Text _pageString;

  IFinishedNotifier* _notifier;

  bool _selectBattleParty;

  static sf::String const PressSpaceBarString;
  static std::string const PageFormatString;
  static sf::String const SpellDescription;

  static int const XLength;
  static sf::Vector2f const PortraitOrigin;
  static int const YOffSet;
};
}
