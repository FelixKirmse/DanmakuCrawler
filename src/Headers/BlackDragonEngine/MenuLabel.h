#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace BlackDragonEngine
{
class MenuLabel
{
public:
  MenuLabel(sf::String const& text, sf::String const& fontName);
  void Draw(sf::RenderTarget& renderTarget);

  sf::String const& GetText();
  sf::Vector2f const& GetPosition();

  void SetText(sf::String const& text);
  void SetPosition(sf::Vector2f const& position);
  void SetPosition(float x, float y);
  void SetFontSize(unsigned int newSize);
  void SetColor(sf::Color newColor);

private:
  sf::Text _text;
};
}
