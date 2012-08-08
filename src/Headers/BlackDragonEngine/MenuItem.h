#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace BlackDragonEngine
{


class MenuItem
{
public:
    MenuItem(sf::String const& name);
    MenuItem(sf::String const& name, sf::Vector2f const& position);
    MenuItem(sf::String const& name, sf::String const& fontName);
    MenuItem(sf::String const& name, sf::String const& fontName,
             bool isSelected);
    MenuItem(sf::String const& name, sf::String const& fontName, bool isSelected,
             sf::Color const& selectedColor, sf::Color const& unSelectedColor);
    MenuItem(sf::String const& name, sf::Vector2f const& position,
             bool isSelected, sf::Font const& font);

    virtual void Update();
    virtual void Draw(sf::RenderTarget& renderTarget);

    sf::String const& GetName();
    sf::Vector2f const& GetPosition();
    bool IsSelected();
    sf::Color const& GetSelectedColor();
    sf::Color const& GetUnSelectedColor();
    sf::Color const& GetUnselectableColor();
    sf::FloatRect GetLocalRectangle();
    sf::FloatRect GetWorldRectangle();
    bool IsSelectable();

    void SetName(sf::String const& name);
    void SetPosition(sf::Vector2f const& position);
    void SetPosition(float x, float y);
    void SetSelected(bool selected);
    void SetSelectedColor(sf::Color const& color);
    void SetUnSelectedColor(sf::Color const& color);
    void SetFontSize(unsigned int newSize);
    void SetSelectable(bool selectable);
    void SetUnselectableColor(sf::Color const& newColor);

private:
    sf::Text _text;
    bool _isSelected;
    sf::Color _selectedColor;
    sf::Color _unSelectedColor;
    bool _selectable;
    sf::Color _unselectableColor;
};
}
