/*
#include <SFML/Graphics.hpp>
int main(int argc, char** argv)
{
  using namespace sf;
  RenderWindow rWindow(sf::VideoMode(640,480), "Test",
                       Style::Close | Style::Titlebar, ContextSettings());

  for(int i = 0; i < 2; ++i)
  {
    rWindow.clear(Color::Blue);
    rWindow.display();

    RenderTexture rTexture;
    Context context;
    rTexture.create(800,600);
    rTexture.clear(Color::Red);
    rTexture.display();
    rTexture.getTexture().copyToImage().saveToFile("test.png");

    rWindow.clear(Color::Blue);
    rWindow.display();
  }
}
*/



#include "Danmaku/DanmakuGame.h"

int main(int argc, char** argv)
{    
  Danmaku::DanmakuGame game;
  game.Run();
  return 0;
}


