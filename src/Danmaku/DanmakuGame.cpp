#include "Danmaku/DanmakuGame.h"

namespace Danmaku
{
DanmakuGame::DanmakuGame()
  : Game("Danmaku",
        VideoMode(ResolutionWidth, ResolutionHeight),
        Style::Titlebar | Style::Close)
{
}

void DanmakuGame::LoadContent()
{
  Provider<Texture>::Get("TitleScreen")
      .loadFromFile("content/textures/titlescreen.png");
  Provider<Font>::Get("Vera").loadFromFile("content/fonts/vera.ttf");



  Provider<Texture>::Get("TileSheet")
      .loadFromFile("content/textures/tilesheets/maze.png");

  //TileMap<Map<TileCode>, TileCode> tileMap(64, 64, 0,
    //                                       Provider<Texture>::Get("TileSheet"));

  //Initialize this last!
  _stateManager.Initialize();
}

void DanmakuGame::Update()
{
  _stateManager.Update();
}

void DanmakuGame::Draw(float interpolation, RenderTarget& renderTarget)
{
  _stateManager.Draw(interpolation, renderTarget);
}

void DanmakuGame::OnLevelLoad()
{
}

void DanmakuGame::Initialize()
{
  Input::ActionKeys = { Keyboard::Return, Keyboard::E };
  Input::CancelKeys = { Keyboard::Escape, Keyboard::Back };
  Input::DownKeys = { Keyboard::Down, Keyboard::S };
  Input::UpKeys = { Keyboard::Up, Keyboard::W };
  Input::LeftKeys = { Keyboard::Left, Keyboard::A };
  Input::RightKeys = { Keyboard::Right, Keyboard::D };
  Input::JumpKeys = { Keyboard::Space };
}
}
