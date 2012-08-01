#include "BlackDragonEngine/Provider.h"
#include "BlackDragonEngine/MenuItem.h"

namespace BlackDragonEngine
{
MenuItem::MenuItem(sf::String const& name)
  : MenuItem(name, sf::Vector2f(), false, Provider<sf::Font>::Get("Vera"))
{
}

MenuItem::MenuItem(sf::String const& name, sf::Vector2f const& position)
  : MenuItem(name, position, false, Provider<sf::Font>::Get("Vera"))
{
}

MenuItem::MenuItem(sf::String const& name, sf::String const& fontName)
  : MenuItem(name, sf::Vector2f(), false, Provider<sf::Font>::Get(fontName))
{
}

MenuItem::MenuItem(sf::String const& name, sf::String const& fontName,
                   bool isSelected)
  : MenuItem(name, sf::Vector2f(), isSelected,
             Provider<sf::Font>::Get(fontName))
{
}

MenuItem::MenuItem(sf::String const& name,sf::String const& fontName,
                   bool isSelected, sf::Color const& selectedColor,
                   sf::Color const& unSelectedColor)
  : MenuItem(name, sf::Vector2f(), isSelected,
             Provider<sf::Font>::Get(fontName))
{
  _selectedColor = selectedColor;
  _unSelectedColor = unSelectedColor;
}

MenuItem::MenuItem(sf::String const& name, sf::Vector2f const& position,
                   bool isSelected, sf::Font const& font)
  : _text(name, font, 20), _isSelected(isSelected),
    _selectedColor(sf::Color::Red), _unSelectedColor(sf::Color::White)
{
  _text.setPosition(position);
}

void MenuItem::Update()
{
  _text.setColor((_isSelected) ? _selectedColor : _unSelectedColor);
}

void MenuItem::Draw(sf::RenderTarget& renderTarget)
{
  renderTarget.draw(_text);
}

sf::String const& MenuItem::GetName()
{
  return _text.getString();
}

sf::Vector2f const& MenuItem::GetPosition()
{
  return _text.getPosition();
}

bool MenuItem::IsSelected()
{
  return _isSelected;
}

sf::Color const& MenuItem::GetSelectedColor()
{
  return _selectedColor;
}

sf::Color const& MenuItem::GetUnSelectedColor()
{
  return _unSelectedColor;
}

void MenuItem::SetName(sf::String const& name)
{
  _text.setString(name);
}

void MenuItem::SetPosition(sf::Vector2f const& position)
{
  _text.setPosition(sf::Vector2f(static_cast<int>(position.x),
                                 static_cast<int>(position.y)));
}

void MenuItem::SetPosition(float x, float y)
{
  SetPosition(sf::Vector2f(x,y));
}

void MenuItem::SetSelected(bool selected)
{
  _isSelected = selected;
}

void MenuItem::SetSelectedColor(sf::Color const& color)
{
  _selectedColor = color;
}

void MenuItem::SetUnSelectedColor(sf::Color const& color)
{
  _unSelectedColor = color;
}

void MenuItem::SetFontSize(unsigned int newSize)
{
  _text.setCharacterSize(newSize);
}

sf::FloatRect MenuItem::GetLocalRectangle()
{
  return _text.getLocalBounds();
}

sf::FloatRect MenuItem::GetWorldRectangle()
{
    return _text.getGlobalBounds();
}

}

