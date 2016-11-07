#ifndef WorldParser_HPP
#define WorldParser_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "TileSet.hpp"
#include "Level.hpp"
#include "Tile.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

class WorldParser
{
public:
    WorldParser();
    ~WorldParser();

    Level* generate_level(std::string file_name); 

private:
    TileSet* _read_tile_set();
    std::vector<std::vector<Tile*>> _read_map();
    void _read_objects();

    TileSet* _tile_set;
    std::vector<std::vector<Tile*>> _map;
    rapidxml::xml_node<> * _map_node;
    rapidxml::xml_document<> _doc;
    std::string _file_name;
    
};


#endif // !WorldParser_HPP