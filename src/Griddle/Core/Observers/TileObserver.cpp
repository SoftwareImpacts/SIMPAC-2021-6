#include "TileObserver.hpp"

#define SPDLOG_HEADER_ONLY
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

namespace griddle {

TileObserver::TileObserver(std::shared_ptr<Grid> grid): Observer(grid) {}

TileObserver::~TileObserver() {}

std::vector<uint32_t> TileObserver::getShape() const {
  return {1, grid_->getWidth(), grid_->getHeight()};
}

std::vector<uint32_t> TileObserver::getStrides() const {
  return {1, 1, 10};
}

std::unique_ptr<uint8_t[]> TileObserver::reset() const {
  return update(0);
};

std::unique_ptr<uint8_t[]> TileObserver::update(int playerId) const {
  int width = grid_->getWidth();
  int height = grid_->getHeight();

  std::unique_ptr<uint8_t[]> observation(new uint8_t[width * height]{});

  for(auto object : grid_->getObjects()) {
    int x = object->getLocation().x;
    int y = object->getLocation().y;
    int idx = width*y + x;

    observation[idx] = object->getObjectId();
  }

  return std::move(observation);
}

void TileObserver::print(std::unique_ptr<uint8_t[]> observation) {
  int width = grid_->getWidth();
  int height = grid_->getHeight();

  std::string printString;

  for (int h = height-1; h >= 0; h--) {
    printString += "[";
    for (int w = 0; w < width; w++) {
      int idx = h * width + w;
      printString += " " + std::to_string(observation[idx]) + " ";
    }
    printString += "]\n";
  }
  spdlog::debug("TileObservation: \n {0}", printString);
}

}  // namespace griddle