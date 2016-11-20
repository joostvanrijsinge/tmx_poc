#ifndef TILESET_HPP
#define TILESET_HPP
#include <string>

using std::string;

struct TileSet {
    string texture_source;
    size_t image_width;
    size_t image_height;
    size_t tile_size;
};


#endif // !TILESET_HPP