#include <boost/filesystem.hpp>
#include "BlackDragonEngine/Input.h"
#include "BlackDragonEngine/Camera.h"
#include "BlackDragonEngine/Provider.h"
#include "Danmaku/DanmakuGame.h"
#include "Danmaku/Battle.h"

#include <fstream>
#include "Danmaku/SerializeUnorderedMap.h"
#include <boost/serialization/array.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

typedef BlackDragonEngine::Provider<sf::Texture> TextureProvider;
typedef BlackDragonEngine::Provider<sf::Font> FontProvider;

namespace Danmaku
{
DanmakuGame::DanmakuGame()
  : Game("Danmaku",
         sf::VideoMode(ResolutionWidth, ResolutionHeight),
         sf::Style::Titlebar | sf::Style::Close),
    _party()
{
}

void DanmakuGame::LoadContent()
{
  TextureProvider::Get("TitleScreen")
      .loadFromFile("content/textures/titlescreen.png");
  FontProvider::Get("Vera").loadFromFile("content/fonts/vera.ttf");



  TextureProvider::Get("TileSheet")
      .loadFromFile("content/textures/tilesheets/maze.png");

  TextureProvider::Get("OverworldPlayer")
      .loadFromFile("content/textures/entities/overworldplayer.png");

  LoadTexturesFromDir("content/textures/charportraits", "Portrait");
  LoadTexturesFromDir("content/textures/charsprites", "CharSprite");
  LoadTexturesFromDir("content/textures/battlesprites", "BattleSprite");

  int const tileWidth = 64;
  int const tileHeight = 64;
  int const tileOffset = 0;
  int const tileStepX = tileWidth;
  int const tileStepY = tileHeight;
  int const oddRowXOffset = 0;

  _tileMap = MapPtr(new DanmakuMap(tileWidth, tileHeight, tileOffset, tileStepX,
                                   tileStepY, oddRowXOffset,
                                   TextureProvider::Get("TileSheet"),
                                   sf::Vector2i(ResolutionWidth,
                                                ResolutionHeight)));

  BlackDragonEngine::Camera::SetViewPortWidth(ResolutionWidth);
  BlackDragonEngine::Camera::SetViewPortHeight(ResolutionHeight);

  std::ifstream ifs("content/etc/BaseStats.xml");
  boost::archive::xml_iarchive ia(ifs);
  ia >> BOOST_SERIALIZATION_NVP(Stats::_baseStats);

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
  Input::CancelKeys = { Keyboard::Escape, Keyboard::BackSpace };
  Input::DownKeys = { Keyboard::Down, Keyboard::S };
  Input::UpKeys = { Keyboard::Up, Keyboard::W };
  Input::LeftKeys = { Keyboard::Left, Keyboard::A };
  Input::RightKeys = { Keyboard::Right, Keyboard::D };
  Input::JumpKeys = { Keyboard::Space };
}

void DanmakuGame::LoadTexturesFromDir(sf::String const& dir,
                                      sf::String const& suffix)
{
  using namespace boost::filesystem;
  path texturePath(dir);
  directory_iterator end_iter;
  int eCount = -1;
  for(directory_iterator i(texturePath); i != end_iter; ++i)
  {
    if(is_directory(i->path()))
      continue;
    if(sf::String(i->path().stem().native()).find("Enemy") != sf::String::InvalidPos )
      ++eCount;
    TextureProvider::Get(i->path().stem().native() + suffix)
        .loadFromFile(i->path().native());
  }
  Battle::MaxEnemyID = eCount;
}

}
