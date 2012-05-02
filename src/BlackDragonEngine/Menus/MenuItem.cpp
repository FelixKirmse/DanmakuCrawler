#include "BlackDragonEngine/MenuItem.h"

namespace BlackDragonEngine
{
MenuItem::MenuItem(String const& name)
  : MenuItem(name, Vector2f(), false, Provider<Font>::Get("Vera"))
{
}

MenuItem::MenuItem(String const& name, Vector2f const& position)
  : MenuItem(name, position, false, Provider<Font>::Get("Vera"))
{
}

MenuItem::MenuItem(String const& name, String const& fontName)
  : MenuItem(name, Vector2f(), false, Provider<Font>::Get(fontName))
{
}

MenuItem::MenuItem(String const& name, String const& fontName, bool isSelected)
  : MenuItem(name, Vector2f(), isSelected, Provider<Font>::Get(fontName))
{
}

MenuItem::MenuItem(String const& name, String const& fontName, bool isSelected,
                   Color const& selectedColor, Color const& unSelectedColor)
  : MenuItem(name, Vector2f(), isSelected, Provider<Font>::Get(fontName))
{
  _selectedColor = selectedColor;
  _unSelectedColor = unSelectedColor;
}

MenuItem::MenuItem(String const& name, Vector2f const& position,
                   bool isSelected, Font const& font)
  : _text(name, font, 20), _isSelected(isSelected),
    _selectedColor(Color::Red), _unSelectedColor(Color::White)
{
  _text.setPosition(position);
}

void MenuItem::Update()
{
  _text.setColor((_isSelected) ? _selectedColor : _unSelectedColor);
}

void MenuItem::Draw(RenderTarget& renderTarget)
{
  renderTarget.draw(_text);
}

String const& MenuItem::GetName()
{
  return _text.getString();
}

Vector2f const& MenuItem::GetPosition()
{
  return _text.getPosition();
}

bool MenuItem::IsSelected()
{
  return _isSelected;
}

Color const& MenuItem::GetSelectedColor()
{
  return _selectedColor;
}

Color const& MenuItem::GetUnSelectedColor()
{
  return _unSelectedColor;
}

void MenuItem::SetName(String const& name)
{
  _text.setString(name);
}

void MenuItem::SetPosition(Vector2f const& position)
{
  _text.setPosition(Vector2f(static_cast<int>(position.x),
                             static_cast<int>(position.y)));
}

void MenuItem::SetSelected(bool selected)
{
  _isSelected = selected;
}

void MenuItem::SetSelectedColor(Color const& color)
{
  _selectedColor = color;
}

void MenuItem::SetUnSelectedColor(Color const& color)
{
  _unSelectedColor = color;
}

FloatRect MenuItem::GetLocalRectangle()
{
  return _text.getLocalBounds();
}

FloatRect MenuItem::GetWorldRectangle()
{
    return _text.getGlobalBounds();
}

}

