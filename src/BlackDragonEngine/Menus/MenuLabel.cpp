#include "BlackDragonEngine/Provider.h"
#include "BlackDragonEngine/MenuLabel.h"

namespace BlackDragonEngine
{
MenuLabel::MenuLabel(sf::String const& text, sf::String const& fontName)
  :_text(text, Provider<sf::Font>::Get(fontName), 30)
{
}

void MenuLabel::Draw(sf::RenderTarget& renderTarget)
{
  renderTarget.draw(_text);
}

sf::String const& MenuLabel::GetText()
{
  return _text.getString();
}

sf::Vector2f const& MenuLabel::GetPosition()
{
  return _text.getPosition();
}

void MenuLabel::SetText(sf::String const& text)
{
  _text.setString(text);
}
void MenuLabel::SetPosition(sf::Vector2f const& position)
{
  _text.setPosition(position);
}

void MenuLabel::SetPosition(float x, float y)
{
  SetPosition(sf::Vector2f(x,y));
}

void MenuLabel::SetFontSize(unsigned int newSize)
{
  _text.setCharacterSize(newSize);
}

void MenuLabel::SetColor(sf::Color newColor)
{
  _text.setColor(newColor);
}
}

