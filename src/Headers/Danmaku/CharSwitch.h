#pragma once
#include "Danmaku/SpellSelectMenu.h"
#include "BlackDragonEngine/Menu.h"

namespace Danmaku
{
class StatOverview;

class CharSwitch : public BlackDragonEngine::Menu
{
public:
  CharSwitch();

  void ResetMenu();
  void Update();
  void Draw(sf::RenderTarget& renderTarget);
  void SelectMenuItem();

private:
  int GetMaxPage();
  void ChangePage(int newPage);

  SpellSelectMenu _spellSelectMenu;
  StatOverview& _statOverview;

  bool  _showStats;
  int _currentPage;

  sf::RectangleShape _backDrop;
  sf::Text _switchString;

  static sf::String const PressSpaceBarString;
  static std::string const PageFormatString;

  static int const XLength;
  static sf::Vector2f const PortraitOrigin;
  static int const YOffSet;
};
}
