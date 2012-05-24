#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/GameStateManager.h"
#include "Danmaku/States.h"
#include "Danmaku/TitleScreen.h"

typedef BlackDragonEngine::Provider<sf::Texture> TextureProvider;

namespace Danmaku
{
using namespace BlackDragonEngine;

TitleScreen::TitleScreen()
  : _titleSprite(TextureProvider::Get("TitleScreen"))
{
  _titleSprite.setPosition(0.0f, 0.0f);
}

bool TitleScreen::DrawCondition()
{
  return UpdateCondition();
}

void TitleScreen::Draw(float, sf::RenderTarget& renderTarget)
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
