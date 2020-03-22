#pragma once
#include "../Object.hpp"

namespace griddy {

class Action;

class PushableWall : public Object {
 public:
  ObjectType getObjectType() const override;

  std::string getDescription() const override;

  bool onActionPerformed(std::shared_ptr<Object> sourceObject, std::shared_ptr<Action> action) override;

  PushableWall();
  ~PushableWall() override;

 private:
  int value;

  static const ObjectType type;
};
}  // namespace griddy