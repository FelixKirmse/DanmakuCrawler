#pragma once
#include <sys/timeb.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "BlackDragonEngine/Input.h"

namespace BlackDragonEngine
{
using namespace std;
using namespace sf;

class Game
{
public:
  Game(String const& title = "Game",
      VideoMode windowSize = VideoMode(800,600),
      Uint32 style = Style::Default,
      ContextSettings const& settings = ContextSettings());

  virtual ~Game() {}
  void Run(int ups = 30);
  void Quit();

  static Vector2f GetScreenCenter();
  static void Exit();

protected:
  virtual void LoadContent();
  virtual void Update();
  virtual void Draw(float interpolation, RenderTarget& renderTarget);
  virtual void Initialize();
  virtual void UnloadContent();


private:
  int GetTicks();
  void HandleEvents();

  RenderWindow _graphics;
  bool _gameRunning;

  static Game* _currentInstance;
};
}
