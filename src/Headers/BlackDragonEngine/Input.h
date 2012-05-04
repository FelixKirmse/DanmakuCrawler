#pragma once
#include <map>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace BlackDragonEngine
{
class Input
{
public:  
  typedef sf::Keyboard::Key Key;
  typedef std::vector<Key> KeyList;
  typedef std::map<sf::String, KeyList> StringKeyMap;
  typedef std::map<sf::String, bool> StringBoolMap;

  static bool Up(bool strict);
  static bool Down(bool strict);
  static bool Left(bool strict);
  static bool Right(bool strict);
  static bool Jump(bool strict);
  static bool Action(bool strict);
  static bool Cancel(bool strict);
  static bool LeftClick(bool strict);
  static bool RightClick(bool strict);

  static void AddNewAction(sf::String name, KeyList keys);
  static bool TriggeredAction(sf::String name, bool strict);

  static sf::Vector2f const& GetMousePosition();
  static bool MouseInsideRectangle(sf::FloatRect const& rect);

  static void UpdateStates();

  static KeyList UpKeys;
  static KeyList DownKeys;
  static KeyList LeftKeys;
  static KeyList RightKeys;
  static KeyList JumpKeys;
  static KeyList ActionKeys;
  static KeyList CancelKeys;

private:  
  static bool CheckKeys(KeyList keys);
  static StringKeyMap CustomActions;

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
    StringBoolMap CustomAction;
    sf::Vector2f MousePosition;
  };

  static InputState LastState;
  static InputState CurrentState;

};
}
