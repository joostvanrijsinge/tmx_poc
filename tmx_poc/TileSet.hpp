#ifndef TILESET_HPP
#define TILESET_HPP
#include <string>

using std::string;

struct TileSet {
    string texture_name;
    string texture_source;
    size_t tile_width;
    size_t tile_height;

};


#endif // !TILESET_HPP