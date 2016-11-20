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
#include "RapidXMLAdapter.hpp"

using std::vector;
using std::string;
using std::exception;

class WorldParser
{
public:
    WorldParser();
    ~WorldParser();

    Level* generate_level(std::string file_name); 

private:
    void _read_objects( xml_node<> * map_node, TileMap map );
};


#endif // !WorldParser_HPP