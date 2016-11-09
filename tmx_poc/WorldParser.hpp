#ifndef WorldParser_HPP
#define WorldParser_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include "TileSet.hpp"
#include "Level.hpp"
#include "Tile.hpp"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

using std::vector;
using std::string;
using rapidxml::xml_node;
using rapidxml::xml_document;
using std::exception;

class WorldParser
{
public:
    WorldParser();
    ~WorldParser();

    Level* generate_level(std::string file_name); 

private:
    TileSet* _read_tile_set();
    TileMap _read_map();
    void _read_objects();

    TileSet* _tile_set;
    TileMap _map;
    xml_node<> * _map_node;
    xml_document<> _doc;
    string _file_name;
    
};


#endif // !WorldParser_HPP