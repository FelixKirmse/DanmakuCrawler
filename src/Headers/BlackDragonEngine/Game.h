#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace BlackDragonEngine
{
class Game
{
public:
  Game(sf::String const& title = "Game",
      sf::VideoMode windowSize = sf::VideoMode(800,600),
      sf::Uint32 style = sf::Style::Default,
      sf::ContextSettings const& settings = sf::ContextSettings());

  virtual ~Game() {}
  void Run(int ups = 30);
  void Quit();

  static sf::Vector2f GetScreenCenter();
  static void Exit();

protected:
  virtual void LoadContent();
  virtual void Update();
  virtual void Draw(float interpolation, sf::RenderTarget& renderTarget);
  virtual void Initialize();
  virtual void UnloadContent();

private:
  int GetTicks();
  void HandleEvents();


  sf::RenderWindow _graphics;
  bool _gameRunning;  
  bool _hasFocus;

  static Game* _currentInstance; //For lazy static access
};
}
