#pragma once
#include <map>
#include <vector>
#include <SFML/Window.hpp>

namespace BlackDragonEngine
{
using namespace sf;
using namespace std;

typedef Keyboard::Key Key;

class Input
{
public:
  static bool Up(bool strict);
  static bool Down(bool strict);
  static bool Left(bool strict);
  static bool Right(bool strict);
  static bool Jump(bool strict);
  static bool Action(bool strict);
  static bool Cancel(bool strict);
  static bool LeftClick(bool strict);
  static bool RightClick(bool strict);

  static void AddNewAction(String name, vector<Key> keys);
  static bool TriggeredAction(String name, bool strict);

  static void UpdateStates();

  static vector<Key> UpKeys;
  static vector<Key> DownKeys;
  static vector<Key> LeftKeys;
  static vector<Key> RightKeys;
  static vector<Key> JumpKeys;
  static vector<Key> ActionKeys;
  static vector<Key> CancelKeys;

private:  
  static bool CheckKeys(vector<Key> keys);
  static map<String, vector<Key> > CustomActions;

  struct InputState
  {
    bool Up;
    bool Down;
    bool Left;
    bool Right;
    bool Jump;
    bool Action;
    bool Cancel;
    bool LeftClick;
    bool RightClick;
    map<String, bool> CustomAction;
  };

  static InputState LastState;
  static InputState CurrentState;

};
}
