#include "WorldParser.hpp"



WorldParser::WorldParser()
{
}


WorldParser::~WorldParser()
{
}

/// \brief Generates a level from the source .tmx file
/// 
/// This function generates a Level object which has:
/// * 2D vector of Tiles
/// * TileSet struct
/// 
/// \param file_name location of the file to be used
/// \return returns a Level*

Level* WorldParser::generate_level( std::string file_name )
{
    _file_name = file_name;

    std::ifstream the_File( _file_name );
    std::vector<char> buffer( ( std::istreambuf_iterator<char>( the_File ) ), std::istreambuf_iterator<char>() );
    buffer.push_back( '\0' );
    _doc.parse<0>( &buffer[0] );

    _map_node = _doc.first_node( "map" );


    _tile_set = _read_tile_set();
    _map = _read_map();
    _read_objects();

    Level* generated_level = new Level;
    generated_level->tile_set = _tile_set;
    generated_level->tiles = _map;

    return generated_level;
}

/// \brief returns a TileSet
///
/// returns a TileSet from the file that includes:
/// * texture_name
/// * tile_width
/// * tile_height
/// * texture_source
///
/// \return returns a TileSet*
TileSet* WorldParser::_read_tile_set()
{
    TileSet* re_tile_set = new TileSet();

    rapidxml::xml_node<> * tileset_node = _map_node->first_node( "tileset" );
    rapidxml::xml_node<> * image_node = tileset_node->first_node( "image" );

    re_tile_set->texture_name = tileset_node->first_attribute("name")->value();
    re_tile_set->tile_width = std::atoi( tileset_node->first_attribute( "tilewidth" )->value() );
    re_tile_set->tile_height = std::atoi( tileset_node->first_attribute( "tileheight" )->value() );
    re_tile_set->texture_source = image_node->first_attribute("source")->value();


    return re_tile_set;
}

/// \brief returns a 2d vector of Tile
///
/// returns a 2d vector of Tile from the file that includes per Tile:
/// * texture_id
/// * x position
/// * y position
/// * tile_type
///
/// \return returns a 2d vector of Tile*
std::vector<std::vector<Tile*>> WorldParser::_read_map()
{
    std::vector<std::vector<int>> int_map;

    rapidxml::xml_node<> * layer_node = _map_node->first_node( "layer" );
    rapidxml::xml_node<> * data_node = layer_node->first_node( "data" );

    char* data_value = data_node->value();
    

    std::stringstream ss(data_value);
    std::string row_chars;

    
    while ( std::getline(ss,row_chars,'\n') ) {

        std::vector<int> row_ints;
        std::stringstream inner_ss(row_chars);
        std::string x_y_char;

        while (std::getline(inner_ss, x_y_char, ',')) {
            row_ints.push_back(std::atoi(x_y_char.c_str()));
        }
        int_map.push_back(row_ints);
    }

    std::vector<std::vector<Tile*>> map;

    for ( int i = 1; i < int_map.size(); i++ ) {
        std::vector<Tile*> map_row;
        for ( int j = 0; j < int_map.at(i).size(); j++ ) {
            std::cout << int_map.at( i ).at( j );
            Tile* new_tile = new Tile;
            new_tile->texture_id = int_map.at(i).at(j);
            new_tile->x = i-1;
            new_tile->y = j;
            new_tile->type = NORMAL;
            map_row.push_back(new_tile);
        }
        map.push_back(map_row);
        std::cout << "\n";
    }
    return map;
}

/// \brief changes tile_types of tiles with objects
///
/// checks the file for object and if object is found changes the tile_type of the tiles within the objects range.
/// for now only works with spawn objects.
void WorldParser::_read_objects()
{
    rapidxml::xml_node<> * object_group_node = _map_node->first_node( "objectgroup" );

    for ( rapidxml::xml_node<> * object_node = object_group_node->first_node("object"); object_node; object_node = object_node->next_sibling() ) {
        if ( std::strcmp(object_node->first_attribute( "type" )->value(), "Spawn") == 0 ) {
            int x = std::atoi( object_node->first_attribute( "x" )->value() ) / 64;
            int y = std::atoi( object_node->first_attribute( "y" )->value() ) / 64;
            _map.at( x ).at( y )->type = SPAWN;
        }
    }
}
