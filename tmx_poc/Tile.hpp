#ifndef TILE_HPP
#define TILE_HPP

enum TileType {
    NORMAL,
    SPAWN
};

struct Tile {
    int texture_id;
    TileType type;
};


#endif // !TILE_HPP