#include "Danmaku/CharGraphicsMenuItem.h"
#include "Danmaku/CharGraphics.h"


namespace Danmaku
{
CharGraphicsMenuItem::CharGraphicsMenuItem(CharGraphics& graphics,
                                           sf::String const& name)
  : MenuItem(name), _charGraphics(graphics), _edge(sf::Vector2f(100.f, 100.f))
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
}
