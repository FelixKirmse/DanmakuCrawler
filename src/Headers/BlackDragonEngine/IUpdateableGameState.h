#pragma once
namespace BlackDragonEngine
{
class IUpdateableGameState
{
public:
  virtual ~IUpdateableGameState() {}
  virtual bool UpdateCondition() = 0;
  virtual bool Update() = 0;
};
}
