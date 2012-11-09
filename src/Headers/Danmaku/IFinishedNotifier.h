#pragma once

namespace Danmaku
{
class IFinishedNotifier
{
public:
  virtual ~IFinishedNotifier(){}

  virtual void WorkFinished() = 0;
  virtual void WorkCancelled() = 0;
};
}
