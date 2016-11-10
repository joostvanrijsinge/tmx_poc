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
    TileSet* _read_tile_set( xml_node<> * map_node );
    vector<vector<int>> _read_int_map( xml_node<> * map_node );
    TileMap _read_map( xml_node<> * map_node, vector<vector<int>> int_map );
    void _read_objects( xml_node<> * map_node, TileMap map );
};


#endif // !WorldParser_HPP