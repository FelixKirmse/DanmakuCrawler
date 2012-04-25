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


void Input::AddNewAction(String name, vector<Key> keys)
{
  CustomActions[name] = keys;
}

bool Input::TriggeredAction(String name, bool strict)
{
  return (strict) ? !LastState.CustomAction[name] && CurrentState.CustomAction[name] : CurrentState.CustomAction[name];
}

vector<Key> Input::UpKeys;
vector<Key> Input::DownKeys;
vector<Key> Input::LeftKeys;
vector<Key> Input::RightKeys;
vector<Key> Input::JumpKeys;
vector<Key> Input::ActionKeys;
vector<Key> Input::CancelKeys;

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
  CurrentState.LeftClick = Mouse::isButtonPressed(Mouse::Left);
  CurrentState.RightClick = Mouse::isButtonPressed(Mouse::Right);

  for(auto mapIterator = CustomActions.begin(); mapIterator != CustomActions.end(); ++mapIterator)
  {
    String actionName = mapIterator->first;
    vector<Key> actionKeys = mapIterator->second;
    CurrentState.CustomAction[actionName] = CheckKeys(actionKeys);
  }
}

bool Input::CheckKeys(vector<Key> keys)
{
  for(size_t i = 0; i < keys.size(); ++i)
  {
    if(Keyboard::isKeyPressed(keys[i]))
      return true;
  }
  return false;
}

map<String, vector<Key> > Input::CustomActions;

}
