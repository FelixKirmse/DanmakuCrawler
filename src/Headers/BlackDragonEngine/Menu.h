#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "BlackDragonEngine/MenuItem.h"
#include "BlackDragonEngine/MenuLabel.h"
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Game.h"

namespace BlackDragonEngine
{
using namespace sf;

class Menu
{
public:
  Menu();

  virtual void Update();
  virtual void Draw(RenderTarget& renderTarget);
  virtual void NextMenuItem();
  virtual void PreviousMenuItem();
  virtual void ResolveMouseSelection();

  virtual void SelectMenuItem() = 0;

protected:
  String const& SelectedItem();
  void SetPositions();

  String const FontName;
  vector<MenuItem> MenuItems;
  vector<MenuLabel> MenuLabels;
  bool EnableMouseSelection;
  Vector2f ItemOffset;
};
}
