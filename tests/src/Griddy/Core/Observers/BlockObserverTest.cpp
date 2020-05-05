#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Griddy/Core/Observers/BlockObserver.hpp"
#include "Griddy/Core/Grid.hpp"
#include "Griddy/Core/GDY/Objects/Object.hpp"

namespace griddy {

// TEST(BlockObserverTest, testRender) {

//   std::unordered_map<std::string, BlockDefinition> blockDefinitions;

//   BlockDefinition blockDefinition;
//   blockDefinition.color[0] = 1.0;
//   blockDefinition.color[1] = 0.0;
//   blockDefinition.color[2] = 0.0;
//   blockDefinition.shape = "square";
//   blockDefinition.scale = 0.5;

//   blockDefinitions["object"] = blockDefinition;

//   auto grid = std::shared_ptr<Grid>(new Grid());
//   auto object = std::shared_ptr<Object>(new Object("object", 0, {}));
//   auto blockObserver = std::shared_ptr<BlockObserver>(new BlockObserver(grid, 16, blockDefinitions));

//   grid->init(1,1);
//   grid->initObject(0, {0,0}, object);
  
//   blockObserver->init(1,1);

//   auto resetData = blockObserver->reset();

//   blockObserver->print(std::move(resetData));

//   grid->update();

//   auto updateData = blockObserver->update(0);
  
//   blockObserver->print(std::move(updateData));

// }
}