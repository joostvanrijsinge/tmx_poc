#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Tile.hpp"
#include "TileSet.hpp"
#include <vector>

struct Level {
    std::vector<std::vector<Tile*>> tiles;
    TileSet* tile_set;
};


#endif // !LEVEL_HPP