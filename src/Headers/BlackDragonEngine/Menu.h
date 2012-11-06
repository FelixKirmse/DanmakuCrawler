#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "BlackDragonEngine/Game.h"

namespace BlackDragonEngine
{
class MenuItem;
class MenuLabel;

class Menu
{
public:
  typedef std::vector<MenuItem*> MenuItemList;
  typedef std::vector<MenuLabel*> MenuLabelList;

  Menu();
  virtual ~Menu();

  virtual void Update();
  virtual void Draw(sf::RenderTarget& renderTarget);
  virtual void NextMenuItem();
  virtual void PreviousMenuItem();
  virtual void ResolveMouseSelection();
  virtual void ResetMenu();

  virtual void SelectMenuItem() = 0;

  void AddMenuItem(MenuItem* item);
  void AddMenuLabel(MenuLabel* label);
  void ClearMenuItems();
  void ClearLabels();

protected:
  sf::String const& SelectedItem();
  void SetPositions(sf::Vector2f position = Game::GetScreenCenter(),
                    bool centered = true, int offset = -2);
  void SetLabelPositions(sf::Vector2f position = Game::GetScreenCenter(),
                         bool centered = true, int offset = -2,
                         bool originBottomRight = false);

  sf::String const FontName;
  MenuItemList MenuItems;
  MenuLabelList MenuLabels;
  bool EnableMouseSelection;
  sf::Vector2f ItemOffset;
};
}
