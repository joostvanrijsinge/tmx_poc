#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Tile.hpp"
#include "TileSet.hpp"
#include <vector>

using std::vector;

typedef vector<vector<Tile*>> TileMap;

struct Level {
    TileMap tiles;
    TileSet* tile_set;
};


#endif // !LEVEL_HPP