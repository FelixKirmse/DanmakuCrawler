#include "Danmaku/TitleScreen.h"

namespace Danmaku
{
TitleScreen::TitleScreen()
  : _titleSprite(Provider<Texture>::Get("TitleScreen"))
{
  _titleSprite.setPosition(0.0f, 0.0f);
}

bool TitleScreen::DrawCondition()
{
  return UpdateCondition();
}

void TitleScreen::Draw(float, RenderTarget& renderTarget)
{
  renderTarget.draw(_titleSprite);
}

bool TitleScreen::UpdateCondition()
{
  return GameStateManager::GetState() == GameStates::Titlescreen;
}

bool TitleScreen::Update()
{
  if(Input::Action(false))
    GameStateManager::SetState(GameStates::Menu);

  return false;
}
}
