#include "Danmaku/DanmakuGame.h"

namespace Danmaku
{
    DanmakuGame::DanmakuGame()
        : Game("Danmaku", VideoMode(ResolutionWidth, ResolutionHeight))
    {        
    }

    void DanmakuGame::LoadContent() 
    {
        TextureProvider::AddTexture("TitleScreen", "content/textures/titlescreen.png");
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
