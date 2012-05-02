#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/Provider.h"

namespace BlackDragonEngine
{
using namespace sf;

class MenuItem
{
public:
    MenuItem(String const& name);
    MenuItem(String const& name, Vector2f const& position);
    MenuItem(String const& name, String const& fontName);
    MenuItem(String const& name, String const& fontName, bool isSelected);
    MenuItem(String const& name, String const& fontName, bool isSelected,
             Color const& selectedColor, Color const& unSelectedColor);
    MenuItem(String const& name, Vector2f const& position, bool isSelected,
             Font const& font);

    virtual void Update();
    virtual void Draw(RenderTarget& renderTarget);

    String const& GetName();
    Vector2f const& GetPosition();
    bool IsSelected();
    Color const& GetSelectedColor();
    Color const& GetUnSelectedColor();
    FloatRect GetLocalRectangle();
    FloatRect GetWorldRectangle();

    void SetName(String const& name);
    void SetPosition(Vector2f const& position);
    void SetSelected(bool selected);
    void SetSelectedColor(Color const& color);
    void SetUnSelectedColor(Color const& color);

private:
    Text _text;
    bool _isSelected;
    Color _selectedColor;
    Color _unSelectedColor;    
};
}
