#include "Danmaku/CharGraphicsMenuItem.h"

#include <string>


namespace Danmaku
{
CharGraphicsMenuItem::CharGraphicsMenuItem(CharGraphics graphics, int id)
  : MenuItem(std::to_string(id)), _charGraphics(graphics),
    _edge(sf::Vector2f(100.f, 100.f)),
    _index(id)
{
  _edge.setOutlineThickness(2.f);
  SetSelectedColor(sf::Color::Red);
  SetUnSelectedColor(sf::Color::Black); 
}

void CharGraphicsMenuItem::Update()
{
  _edge.setOutlineColor(IsSelected() ? GetSelectedColor() : GetUnSelectedColor());
}

void CharGraphicsMenuItem::Draw(sf::RenderTarget& renderTarget)
{
  renderTarget.draw(_edge);
  _charGraphics.Draw(renderTarget);
}

void CharGraphicsMenuItem::SetPosition(sf::Vector2f const& position)
{
  _charGraphics.Reposition(position);
  _edge.setPosition(position);
}

int CharGraphicsMenuItem::GetIndex()
{
  return _index;
}

sf::Vector2f const& CharGraphicsMenuItem::GetPosition()
{
  return _edge.getPosition();
}

sf::FloatRect CharGraphicsMenuItem::GetLocalRectangle()
{
  return _edge.getLocalBounds();
}
}
