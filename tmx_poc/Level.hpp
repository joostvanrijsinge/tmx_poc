#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Tile.hpp"
#include "TileSet.hpp"
#include <vector>

typedef std::vector<std::vector<Tile*>> tilemap;

struct Level {
    tilemap tiles;
    TileSet* tile_set;
};


#endif // !LEVEL_HPP