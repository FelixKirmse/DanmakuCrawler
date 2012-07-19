#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "BlackDragonEngine/Game.h"
#include "BlackDragonEngine/MenuItem.h"
#include "BlackDragonEngine/MenuLabel.h"

namespace BlackDragonEngine
{
class Menu
{
public:
  typedef std::vector<MenuItem> MenuItemList;
  typedef std::vector<MenuLabel> MenuLabelList;

  Menu();

  virtual void Update();
  virtual void Draw(sf::RenderTarget& renderTarget);
  virtual void NextMenuItem();
  virtual void PreviousMenuItem();
  virtual void ResolveMouseSelection();
  virtual void ResetMenu();

  virtual void SelectMenuItem() = 0;

protected:
  sf::String const& SelectedItem();
  void SetPositions(sf::Vector2f positionCenter = Game::GetScreenCenter(),
                    bool centered = true);

  sf::String const FontName;
  MenuItemList MenuItems;
  MenuLabelList MenuLabels;
  bool EnableMouseSelection;
  sf::Vector2f ItemOffset;
};
}
