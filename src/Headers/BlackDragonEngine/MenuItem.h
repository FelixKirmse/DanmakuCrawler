#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace BlackDragonEngine
{


class MenuItem
{
public:
  MenuItem();
  MenuItem(sf::String const& name);
  MenuItem(sf::String const& name, sf::Vector2f const& position);
  MenuItem(sf::String const& name, sf::String const& fontName);
  MenuItem(sf::String const& name, sf::String const& fontName,
           bool isSelected);
  MenuItem(sf::String const& name, sf::String const& fontName, bool isSelected,
           sf::Color const& selectedColor, sf::Color const& unSelectedColor);
  MenuItem(sf::String const& name, sf::Vector2f const& position,
           bool isSelected, sf::Font const& font);

  virtual ~MenuItem(){}

  virtual void Update();
  virtual void Draw(sf::RenderTarget& renderTarget);

  virtual sf::String const& GetName();
  virtual sf::Vector2f const& GetPosition();
  virtual bool IsSelected();
  virtual sf::Color const& GetSelectedColor();
  virtual sf::Color const& GetUnSelectedColor();
  virtual sf::Color const& GetUnselectableColor();
  virtual sf::FloatRect GetLocalRectangle();
  virtual sf::FloatRect GetWorldRectangle();
  virtual bool IsSelectable();

  virtual void SetName(sf::String const& name);
  virtual void SetPosition(sf::Vector2f const& position);
  virtual void SetPosition(float x, float y);
  virtual void SetSelected(bool selected);
  virtual void SetSelectedColor(sf::Color const& color);
  virtual void SetUnSelectedColor(sf::Color const& color);
  virtual void SetFontSize(unsigned int newSize);
  virtual void SetSelectable(bool selectable);
  virtual void SetUnselectableColor(sf::Color const& newColor);

private:
  sf::Text _text;
  bool _isSelected;
  sf::Color _selectedColor;
  sf::Color _unSelectedColor;
  bool _selectable;
  sf::Color _unselectableColor;
};
}
