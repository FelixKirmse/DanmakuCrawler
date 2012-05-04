#include "Danmaku/DanmakuGame.h"

namespace Danmaku
{
DanmakuGame::DanmakuGame()
  : Game("Danmaku",
         sf::VideoMode(ResolutionWidth, ResolutionHeight),
         sf::Style::Titlebar | sf::Style::Close)
{
}

void DanmakuGame::LoadContent()
{
  TextureProvider::Get("TitleScreen")
      .loadFromFile("content/textures/titlescreen.png");
  FontProvider::Get("Vera").loadFromFile("content/fonts/vera.ttf");



  TextureProvider::Get("TileSheet")
      .loadFromFile("content/textures/tilesheets/maze.png");

  DanmakuMap tileMap(64, 64, 0, TextureProvider::Get("TileSheet"));

  //Initialize this last!
  _stateManager.Initialize();
}

void DanmakuGame::Update()
{
  _stateManager.Update();
}

void DanmakuGame::Draw(float interpolation, sf::RenderTarget& renderTarget)
{
  _stateManager.Draw(interpolation, renderTarget);
}

void DanmakuGame::OnLevelLoad()
{
}

void DanmakuGame::Initialize()
{
  using namespace sf;
  using namespace BlackDragonEngine;

  Input::ActionKeys = { Keyboard::Return, Keyboard::E };
  Input::CancelKeys = { Keyboard::Escape, Keyboard::Back };
  Input::DownKeys = { Keyboard::Down, Keyboard::S };
  Input::UpKeys = { Keyboard::Up, Keyboard::W };
  Input::LeftKeys = { Keyboard::Left, Keyboard::A };
  Input::RightKeys = { Keyboard::Right, Keyboard::D };
  Input::JumpKeys = { Keyboard::Space };
}
}
