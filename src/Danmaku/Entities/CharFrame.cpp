#include "Danmaku/CharFrame.h"
#include <string>
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Character.h"


namespace Danmaku
{
typedef BlackDragonEngine::Provider<sf::Font> FontProvider;
typedef BlackDragonEngine::Provider<sf::Texture> TextureProvider;
using namespace std;

CharFrame::CharFrame()
{
}

CharFrame::CharFrame(sf::Vector2f offset, sf::String charName, Character* owner)
  : _owner(owner), _offset(0.f, 0.f), _frame(sf::Vector2f(100.f,100.f)),
    _spdBackgrnd(sf::Vector2f(50.f,8.f)), _spdBar(sf::Vector2f(50.f,8.f)),
    _hpBackgrnd(sf::Vector2f(90.f,10.f)), _hpBar(sf::Vector2f(90.f,10.f)),
    _mpBackgrnd(sf::Vector2f(90.f,10.f)), _mpBar(sf::Vector2f(90.f,10.f)),
    _hp("HP", FontProvider::Get("Vera"), 8u),
    _mp("MP", FontProvider::Get("Vera"), 8u),
    _hpValue(to_string((int)owner->_currentHP) + " / "
             + to_string((int)owner->GetStats().GetTotalHP()),
             FontProvider::Get("Vera"), 8u),
    _mpValue(to_string((int)owner->_currentMP) + " / "
             + to_string((int)owner->GetStats().GetTotalMP()),
             FontProvider::Get("Vera"), 8u)
{
  using namespace sf;
  _frame.setTexture(&TextureProvider::Get(charName));
  _frame.setOutlineColor(Color::Black);
  _frame.setOutlineThickness(1.f);

  _spdBackgrnd.setFillColor(Color(207u, 207u, 207u));
  _spdBackgrnd.setOutlineColor(Color(190u, 190u, 190u));
  _spdBackgrnd.setOutlineThickness(1.f);

  _spdBar.setFillColor(Color(255u, 119u, 0u));
  _spdBar.setOutlineColor(Color(255u, 96u, 0u));
  _spdBar.setOutlineThickness(1.f);

  _hpBackgrnd.setFillColor(Color(207u, 207u, 207u));
  _hpBackgrnd.setOutlineColor(Color(190u, 190u, 190u));
  _hpBackgrnd.setOutlineThickness(1.f);

  _hpBar.setFillColor(Color(181u, 212u, 149u));
  _hpBar.setOutlineColor(Color(148u, 177u, 117u));
  _hpBar.setOutlineThickness(1.f);

  _mpBackgrnd.setFillColor(Color(207u, 207u, 207u));
  _mpBackgrnd.setOutlineColor(Color(190u, 190u, 190u));
  _mpBackgrnd.setOutlineThickness(1.f);

  _mpBar.setFillColor(Color(0u, 148u, 255u));
  _mpBar.setOutlineColor(Color(0u, 90u, 255u));
  _mpBar.setOutlineThickness(1.f);

  _frame.setPosition(0.f, 0.f);

  _spdBar.setPosition(44.f, 61.f);
  _spdBackgrnd.setPosition(44.f, 61.f);

  _hpBar.setPosition(4.f, 73.f);
  _hpBackgrnd.setPosition(4.f, 73.f);

  _mpBar.setPosition(4.f, 87.f);
  _mpBackgrnd.setPosition(4.f, 87.f);

  _hp.setPosition(78.f, 73.f);
  _mp.setPosition(78.f, 87.f);

  _hpValue.setPosition(7.f, 73.f);
  _mpValue.setPosition(7.f, 87.f);

  _hp.setColor(Color::Black);
  _hpValue.setColor(Color::Black);
  _mp.setColor(Color::Black);
  _mpValue.setColor(Color::Black);

  Reposition(offset);
}

void CharFrame::Reposition(sf::Vector2f newOffset)
{
  // Revert to base position, then move to new one.
  _frame.move(-_offset + newOffset);
  _spdBar.move(-_offset + newOffset);
  _spdBackgrnd.move(-_offset + newOffset);
  _hpBar.move(-_offset + newOffset);
  _hpBackgrnd.move(-_offset + newOffset);
  _mpBar.move(-_offset + newOffset);
  _mpBackgrnd.move(-_offset + newOffset);
  _hp.move(-_offset + newOffset);
  _mp.move(-_offset + newOffset);
  _hpValue.move(-_offset + newOffset);
  _mpValue.move(-_offset + newOffset);

  _offset = newOffset;
}

void CharFrame::UpdateHP()
{
  int currentHP = (int)_owner->_currentHP;
  int maxHP = (int)_owner->GetStats().GetTotalHP();

  _hpValue.setString(to_string(currentHP) + " / " + to_string(maxHP));

  float scaleFactor = (float)currentHP/maxHP;
  sf::Vector2f size(_hpBackgrnd.getSize().x * scaleFactor, _hpBar.getSize().y);
  _hpBar.setSize(size);

}

void CharFrame::UpdateMP()
{
  int currentMP = (int)_owner->_currentMP;
  int maxMP = (int)_owner->GetStats().GetTotalMP();

  _mpValue.setString(to_string(currentMP) + " / " + to_string(maxMP));

  float scaleFactor = (float)currentMP/maxMP;
  sf::Vector2f size(_mpBackgrnd.getSize().x * scaleFactor, _mpBar.getSize().y);
  _mpBar.setSize(size);
}

void CharFrame::Draw(sf::RenderTarget& rTarget)
{
  rTarget.draw(_frame);
  rTarget.draw(_spdBackgrnd);
  rTarget.draw(_spdBar);
  rTarget.draw(_hpBackgrnd);
  rTarget.draw(_hpBar);
  rTarget.draw(_mpBackgrnd);
  rTarget.draw(_mpBar);
  rTarget.draw(_hp);
  rTarget.draw(_mp);
  rTarget.draw(_hpValue);
  rTarget.draw(_mpValue);
}

void CharFrame::UpdateSPD()
{
  float scaleFactor = (float)_owner->_turnCounter/_owner->TimeToAction;
  if(scaleFactor == 0.f)
    scaleFactor = 1.f;
  sf::Vector2f size(_spdBackgrnd.getSize().x * scaleFactor, _spdBar.getSize().y);
  _spdBar.setSize(size);
}

}
