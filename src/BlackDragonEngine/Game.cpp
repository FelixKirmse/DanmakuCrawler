#include "BlackDragonEngine/Game.h"

namespace BlackDragonEngine
{
Game::Game(sf::String const& title, sf::VideoMode windowSize,
           sf::Uint32 style, sf::ContextSettings const& settings)
  : _graphics(windowSize, title, style, settings), _gameRunning(false)
{
  _currentInstance = this;
}

int Game::GetTicks()
{
  timeb tb;
  ftime(&tb);
  return tb.millitm + (tb.time & 0xfffff) * 1000;
}

void Game::Run(int ups)
{
  int const ticksPerSecond = ups;
  int const skipTicks = 1000 / ticksPerSecond;
  int const maxFrameSkip = 5;

  int nextGameTick = GetTicks();
  _gameRunning = true;

  Initialize();
  LoadContent();

  while(_gameRunning)
  {
    HandleEvents();

    for(int loops = 0; GetTicks() > nextGameTick && loops < maxFrameSkip; ++loops)
    {
      Input::UpdateStates();
      Update();
      nextGameTick += skipTicks;
    }

    _graphics.clear();
    float interpolation = float(GetTicks() + skipTicks - nextGameTick)
        - float(skipTicks);
    Draw(interpolation, _graphics);
    _graphics.display();
  }

  UnloadContent();
}

void Game::HandleEvents()
{
  sf::Event event;
  while(_graphics.pollEvent(event))
  {
    if(event.type == sf::Event::Closed)
      Quit();
  }
}

void Game::Quit()
{
  _gameRunning = false;
  _graphics.close();
}

void Game::LoadContent() {}
void Game::Update() {}
void Game::Draw(float interpolation, sf::RenderTarget& renderTarget) {}
void Game::Initialize() {}
void Game::UnloadContent() {}

Game* Game::_currentInstance;

sf::Vector2f Game::GetScreenCenter()
{
  sf::Vector2u size = _currentInstance->_graphics.getSize();
  return sf::Vector2f(size.x/2.0f, size.y/2.0f);
}

void Game::Exit()
{
  _currentInstance->Quit();
}
}
