#include <sys/timeb.h>
#include <string>
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Game.h"

namespace BlackDragonEngine
{
Game::Game(sf::String const& title, sf::VideoMode windowSize,
           sf::Uint32 style, sf::ContextSettings const& settings)
  : _graphics(windowSize, title, style, settings), _gameRunning(false),
    _hasFocus(true)
{
  _currentInstance = this;
  _graphics.setVerticalSyncEnabled(false);
  _graphics.setFramerateLimit(9000000);
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

  int drawCounter = 0;
  int updateCounter = 0;
  sf::Clock clock;
  /*sf::Text fpsText;
  fpsText.setFont(sf::Font::getDefaultFont());
  fpsText.setColor(sf::Color::Red);
  fpsText.setCharacterSize(30);
  fpsText.setPosition(sf::Vector2f(10,0));
  */
  while(_gameRunning)
  {
    HandleEvents();

    for(int loops = 0; GetTicks() > nextGameTick && loops < maxFrameSkip; ++loops)
    {
      if(_hasFocus)
        Input::UpdateStates();
      Update();
      nextGameTick += skipTicks;
      ++updateCounter;
    }

    _graphics.clear(sf::Color::Black);
    float interpolation = float(GetTicks() + skipTicks - nextGameTick)
        - float(skipTicks);
    Draw(interpolation, _graphics);
    //_graphics.draw(fpsText);
    if(clock.getElapsedTime().asMilliseconds() > 1000)
    {
      /*fpsText.setString("UpdateRate: " + std::to_string(updateCounter)
                        + "\nDrawRate: " + std::to_string(drawCounter));*/
      drawCounter = 0;
      updateCounter = 0;
      clock.restart();
    }
    _graphics.display();
    ++drawCounter;
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
    if(event.type == sf::Event::LostFocus)
      _hasFocus = false;
    if(event.type == sf::Event::GainedFocus)
      _hasFocus = true;
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
