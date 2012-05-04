#include "BlackDragonEngine/Input.h"

namespace BlackDragonEngine
{
bool Input::Up(bool strict)
{
  return (strict) ? !LastState.Up && CurrentState.Up : CurrentState.Up;
}

bool Input::Down(bool strict)
{
  return (strict) ? !LastState.Down && CurrentState.Down : CurrentState.Down;
}

bool Input::Left(bool strict)
{
  return (strict) ? !LastState.Left && CurrentState.Left : CurrentState.Left;
}

bool Input::Right(bool strict)
{
  return (strict) ? !LastState.Right && CurrentState.Right : CurrentState.Right;
}

bool Input::Jump(bool strict)
{
  return (strict) ? !LastState.Jump && CurrentState.Jump : CurrentState.Jump;
}

bool Input::Action(bool strict)
{
  return (strict) ? !LastState.Action && CurrentState.Action : CurrentState.Action;
}

bool Input::Cancel(bool strict)
{
  return (strict) ? !LastState.Cancel && CurrentState.Cancel : CurrentState.Cancel;
}

bool Input::LeftClick(bool strict)
{
  return (strict) ? !LastState.LeftClick && CurrentState.LeftClick : CurrentState.LeftClick;
}

bool Input::RightClick(bool strict)
{
  return (strict) ? !LastState.RightClick && CurrentState.RightClick : CurrentState.RightClick;
}


void Input::AddNewAction(sf::String name, KeyList keys)
{
  CustomActions[name] = keys;
}

bool Input::TriggeredAction(sf::String name, bool strict)
{
  return (strict) ? !LastState.CustomAction[name] && CurrentState.CustomAction[name] : CurrentState.CustomAction[name];
}

sf::Vector2f const& Input::GetMousePosition()
{
  return CurrentState.MousePosition;
}

bool Input::MouseInsideRectangle(sf::FloatRect const& rect)
{
  return rect.contains(CurrentState.MousePosition);
}

Input::KeyList Input::UpKeys;
Input::KeyList Input::DownKeys;
Input::KeyList Input::LeftKeys;
Input::KeyList Input::RightKeys;
Input::KeyList Input::JumpKeys;
Input::KeyList Input::ActionKeys;
Input::KeyList Input::CancelKeys;

Input::InputState Input::LastState = {0};
Input::InputState Input::CurrentState = {0};

void Input::UpdateStates()
{
  LastState = CurrentState;

  CurrentState.Action = CheckKeys(ActionKeys);
  CurrentState.Cancel = CheckKeys(CancelKeys);
  CurrentState.Down = CheckKeys(DownKeys);
  CurrentState.Jump = CheckKeys(JumpKeys);
  CurrentState.Left = CheckKeys(LeftKeys);
  CurrentState.Right = CheckKeys(RightKeys);
  CurrentState.Up = CheckKeys(UpKeys);
  CurrentState.LeftClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
  CurrentState.RightClick = sf::Mouse::isButtonPressed(sf::Mouse::Right);
  sf::Vector2i pos = sf::Mouse::getPosition();
  CurrentState.MousePosition = sf::Vector2f(pos.x, pos.y);

  for(auto i = CustomActions.begin(); i != CustomActions.end(); ++i)
  {
    sf::String actionName = i->first;
    KeyList actionKeys = i->second;
    CurrentState.CustomAction[actionName] = CheckKeys(actionKeys);
  }
}

bool Input::CheckKeys(KeyList keys)
{
  for(size_t i = 0; i < keys.size(); ++i)
  {
    if(sf::Keyboard::isKeyPressed(keys[i]))
      return true;
  }
  return false;
}

Input::StringKeyMap Input::CustomActions;

}
