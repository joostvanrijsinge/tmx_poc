#ifndef TILE_HPP
#define TILE_HPP

struct Tile {
    int x;
    int y;
    int texture_id;
    enum tile_type type;
};

enum tile_type {
    NORMAL,
    SPAWN
};

#endif // !TILE_HPP