#include "Danmaku/CharGraphics.h"
#include <string>
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/Character.h"
#include "Danmaku/Stats.h"


namespace Danmaku
{
typedef BlackDragonEngine::Provider<sf::Font> FontProvider;
typedef BlackDragonEngine::Provider<sf::Texture> TextureProvider;
using namespace std;

CharGraphics::CharGraphics()
{
}

sf::Color const CharGraphics::FullSPDBar(255u, 0u, 0u);
sf::Color const CharGraphics::NormalSPDBar(255u, 119u, 0u);
sf::Texture* CharGraphics::DeadFrame = NULL;

CharGraphics::CharGraphics(sf::Vector2f offset, sf::String charName,
                           Character* owner)
  : _owner(owner), _offset(0.f, 0.f),
    _portrait(TextureProvider::Get(charName + "Portrait")),
    _spdBackgrnd(sf::Vector2f(70.f,6.f)), _spdBar(sf::Vector2f(70.f,6.f)),
    _hpBackgrnd(sf::Vector2f(90.f,10.f)), _hpBar(sf::Vector2f(90.f,10.f)),
    _mpBackgrnd(sf::Vector2f(90.f,10.f)), _mpBar(sf::Vector2f(90.f,10.f)),
    _hp("HP", FontProvider::Get("Vera"), 8u),
    _mp("MP", FontProvider::Get("Vera"), 8u),
    _hpValue(to_string((int)owner->CurrentHP()) + " / "
             + to_string((int)owner->GetStats().GetTotalBaseStat(HP)),
             FontProvider::Get("Vera"), 8u),
    _mpValue(to_string((int)owner->CurrentMP()) + " / "
             + to_string((int)owner->GetStats().GetTotalBaseStat(MP)),
             FontProvider::Get("Vera"), 8u),
    _charSprite(TextureProvider::Get(charName + "CharSprite")),
    _battleSprite(TextureProvider::Get(charName + "BattleSprite")),
    _enemySpdBar(sf::Vector2f(70.f,6.f)),
    _enemySpdBackgrnd(sf::Vector2f(70.f,6.f)),
    _enemyName(owner->GetDisplayName(), FontProvider::Get("Vera"), 12u),
    _damageDone("0", FontProvider::Get("Vera"), 10u),
    _myTurn(false)
{
  using namespace sf;
  if(DeadFrame == NULL)
    DeadFrame = &TextureProvider::Get("DeadPortrait");

  _charSprite.setPosition(0.f, 0.f);
  /*_battleSprite.setOrigin(_battleSprite.getLocalBounds().width,
                          _battleSprite.getLocalBounds().height);
*/
  _portrait.setTexture(TextureProvider::Get(charName + "Portrait"));
  _portrait.setPosition(sf::Vector2f(100.f,100.f));

  _spdBackgrnd.setFillColor(Color(207u, 207u, 207u));
  _spdBackgrnd.setOutlineColor(Color(190u, 190u, 190u));
  _spdBackgrnd.setOutlineThickness(1.f);

  _spdBar.setFillColor(Color(255u, 119u, 0u));
  _spdBar.setOutlineColor(Color(255u, 96u, 0u));
  _spdBar.setOutlineThickness(1.f);

  _enemySpdBackgrnd.setFillColor(Color(207u, 207u, 207u));
  _enemySpdBackgrnd.setOutlineColor(Color(190u, 190u, 190u));
  _enemySpdBackgrnd.setOutlineThickness(1.f);

  _enemySpdBar.setFillColor(Color(255u, 119u, 0u));
  _enemySpdBar.setOutlineColor(Color(255u, 96u, 0u));
  _enemySpdBar.setOutlineThickness(1.f);

  _hpBackgrnd.setFillColor(Color(207u, 207u, 207u));
  _hpBackgrnd.setOutlineColor(Color(190u, 190u, 190u));
  _hpBackgrnd.setOutlineThickness(1.f);

  //_hpBar.setFillColor(Color(181u, 212u, 149u));
  _hpBar.setFillColor(Color(0u, 255u, 0u));
  _hpBar.setOutlineColor(Color(148u, 177u, 117u));
  _hpBar.setOutlineThickness(1.f);

  _mpBackgrnd.setFillColor(Color(207u, 207u, 207u));
  _mpBackgrnd.setOutlineColor(Color(190u, 190u, 190u));
  _mpBackgrnd.setOutlineThickness(1.f);

  _mpBar.setFillColor(Color(0u, 148u, 255u));
  _mpBar.setOutlineColor(Color(0u, 90u, 255u));
  _mpBar.setOutlineThickness(1.f);

  _portrait.setPosition(0.f, 0.f);

  _spdBar.setPosition(24.f, 61.f);
  _spdBackgrnd.setPosition(24.f, 61.f);

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

void CharGraphics::Reposition(float x, float y)
{
  Reposition(sf::Vector2f(x,y));
}

void CharGraphics::SetDeadSprites()
{
  _portrait.setTexture(*DeadFrame);
  _battleSprite.setTexture(*DeadFrame);
}

void CharGraphics::Reposition(sf::Vector2f newOffset)
{
  // Revert to base position, then move to new one.
  _portrait.move(-_offset + newOffset);
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

void CharGraphics::UpdateHP()
{
  int currentHP = (int)_owner->CurrentHP();
  int maxHP = (int)_owner->GetStats().GetTotalBaseStat(HP);

  _hpValue.setString(to_string(currentHP) + " / " + to_string(maxHP));

  float scaleFactor = (float)currentHP/maxHP;
  sf::Vector2f size(_hpBackgrnd.getSize().x * scaleFactor, _hpBar.getSize().y);
  _hpBar.setSize(size);

  // Smooth going from green to red
  sf::Color hpColor = _hpBar.getFillColor();
  unsigned int red = (scaleFactor > .5f) ? 255u - (scaleFactor * 2 * 255u) :
                                           255u;
  unsigned int green = (scaleFactor < .5f) ? 255u * scaleFactor * 2 : 255u;
  if(scaleFactor == .5f)
  {
    red = 255u;
    green = 255u;
  }
  hpColor.r = red;
  hpColor.g = green;
  _hpBar.setFillColor(hpColor);  
}

void CharGraphics::UpdateMP()
{
  int currentMP = _owner->CurrentMP();
  int maxMP = _owner->GetStats().GetTotalBaseStat(MP);

  _mpValue.setString(to_string(currentMP) + " / " + to_string(maxMP));

  float scaleFactor = (float)currentMP/maxMP;
  sf::Vector2f size(_mpBackgrnd.getSize().x * scaleFactor, _mpBar.getSize().y);
  _mpBar.setSize(size);
}

void CharGraphics::SetDamageDone(int damage)
{
  _damageDone.setColor(damage <= 0 ? sf::Color::Red : sf::Color::Green);
  _damageDone.setString(std::to_string(damage < 0 ? -damage : damage));
  sf::Vector2f dmgPos = _enemySpdBar.getPosition();
  dmgPos.y -= 14.f;
  dmgPos.x = (int)dmgPos.x;
  dmgPos.y = (int)dmgPos.y;
  _damageDone.setPosition(dmgPos);
}

void CharGraphics::DrawCharSprite(sf::RenderTarget& rTarget)
{
  if(_myTurn && !_owner->IsDead())
    rTarget.draw(_charSprite);
}

void CharGraphics::Draw(sf::RenderTarget& rTarget)
{    
  rTarget.draw(_portrait);

  if(_owner->IsDead())
    return;

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

void CharGraphics::DrawDamageDone(sf::RenderTarget& rTarget)
{
  if(!_owner->IsDead())
    rTarget.draw(_damageDone);
}

void CharGraphics::UpdateSPD(bool myTurn)
{
  float scaleFactor = (float)_owner->TurnCounter()/_owner->TimeToAction;
  if(myTurn)
    scaleFactor = 1.f;

  _myTurn = myTurn;
  sf::Vector2f size(_spdBackgrnd.getSize().x * scaleFactor, _spdBar.getSize().y);
  _spdBar.setSize(size);
  _spdBar.setFillColor((_myTurn) ? FullSPDBar : NormalSPDBar);

  _enemySpdBar.setSize(size);
  _enemySpdBar.setFillColor((_myTurn) ? FullSPDBar : NormalSPDBar);
}

void CharGraphics::SetBattleSpritePosition(sf::Vector2f pos)
{
  pos.x -= _battleSprite.getLocalBounds().width;
  pos.y -= _battleSprite.getLocalBounds().height;
  _battleSprite.setPosition(pos);
  float posx = pos.x +_battleSprite.getLocalBounds().width
      - _battleSprite.getLocalBounds().width / 2.f
      - _enemySpdBackgrnd.getSize().x / 2.f;
  _enemySpdBackgrnd.setPosition(posx, pos.y
                                + _battleSprite.getLocalBounds().height+ 5.f);
  _enemySpdBar.setPosition(_enemySpdBackgrnd.getPosition());
  _enemyName.setPosition(_enemySpdBar.getPosition());

  sf::Vector2f namePos = _enemyName.getPosition();
  namePos.y += 7.f;
  namePos.x += _enemySpdBar.getLocalBounds().width / 2.f;
  namePos.x -= _enemyName.getLocalBounds().width / 2.f;
  namePos.x = (int)namePos.x;
  namePos.y = (int)namePos.y;
  _enemyName.setPosition(namePos);
}

void CharGraphics::DrawBattleSprite(sf::RenderTarget& rTarget)
{
  if(_owner->IsDead())
    return;

  rTarget.draw(_battleSprite);
  rTarget.draw(_enemySpdBackgrnd);
  rTarget.draw(_enemySpdBar);
  rTarget.draw(_enemyName);
}

}
