#ifndef TILE_HPP
#define TILE_HPP

enum tile_type {
    NORMAL,
    SPAWN
};

struct Tile {
    int texture_id;
    tile_type type;
};


#endif // !TILE_HPP