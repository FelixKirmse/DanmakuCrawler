#include "BlackDragonEngine/MenuLabel.h"

namespace BlackDragonEngine
{
MenuLabel::MenuLabel(String const& text, String const& fontName)
  :_text(text, Provider<Font>::Get(fontName), 30)
{
}

void MenuLabel::Draw(RenderTarget& renderTarget)
{
  renderTarget.draw(_text);
}

String const& MenuLabel::GetText()
{
  return _text.getString();
}

Vector2f const& MenuLabel::GetPosition()
{
  return _text.getPosition();
}

void MenuLabel::SetText(String const& text)
{
  _text.setString(text);
}
void MenuLabel::SetPosition(Vector2f const& position)
{
  _text.setPosition(position);
}
}

