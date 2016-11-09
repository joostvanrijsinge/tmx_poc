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
    try {
        // parses the .tmx into a xml_document object which rapidxml uses to get the nodes.
        xml_document<> doc;
        std::ifstream the_file( file_name );
        if ( the_file.is_open() ) {
            vector<char> buffer( ( std::istreambuf_iterator<char>( the_file ) ), std::istreambuf_iterator<char>() );
            // if we don't append '\0' rapidxml throws parse_exception
            buffer.push_back( '\0' );
            doc.parse<0>( &buffer[0] );

            xml_node<> * map_node = doc.first_node( "map" );
            if ( map_node == 0 ) {
                throw exception( "file invalid no TileMap" );
            }

            TileSet * tile_set = this->_read_tile_set(map_node);
            vector<vector<int>> int_map = this->_read_int_map(map_node);
            TileMap map = this->_read_map(map_node, int_map);
            this->_read_objects(map_node, map);

            // generated_level needs to be deleted in the mainclass/gameloop when this level has been completed/finished/player quits.
            Level* generated_level = new Level;
            generated_level->tile_set = tile_set;
            generated_level->tiles = map;

            return generated_level;
        }
        else {
            throw exception("can't open file");
        }
    }
    catch ( const exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
}

/// \brief returns a TileSet
///
/// returns a TileSet from the file that includes:
/// * texture_name
/// * tile_width
/// * tile_height
/// * texture_source
///
/// \param map_node the node named map from the .tmx
/// \return returns a TileSet*
TileSet* WorldParser::_read_tile_set(xml_node<> * map_node)
{
    TileSet* tile_set = new TileSet();

    xml_node<> * tileset_node = map_node->first_node("tileset");
    if ( tileset_node == 0 ) {
        throw exception("file invalid no textures");
    }
    xml_node<> * image_node = tileset_node->first_node("image");
    if ( image_node == 0 ) {
        throw exception( "file invalid no textures" );
    }

    tile_set->texture_name = tileset_node->first_attribute( "name" )->value();
    tile_set->tile_width = std::stoi( tileset_node->first_attribute( "tilewidth" )->value() );
    tile_set->tile_height = std::stoi( tileset_node->first_attribute( "tileheight" )->value() );
    tile_set->texture_source = image_node->first_attribute( "source" )->value();

    return tile_set;
}

/// \brief returns a 2d vector of ints
///
/// returns a 2d vector of ints from the file that includes the texture value
///
/// \param map_node the node named map from the .tmx
/// \return returns a 2d vector of Tile*
vector<vector<int>> WorldParser::_read_int_map( xml_node<>* map_node )
{
    vector<vector<int>> int_map;

    xml_node<> * layer_node = map_node->first_node( "layer" );
    if ( layer_node == 0 ) {
        throw exception( "file invalid no TileMap" );
    }
    xml_node<> * data_node = layer_node->first_node( "data" );
    if ( data_node == 0 ) {
        throw exception( "file invalid no TileMap" );
    }

    char* data_value = data_node->value();
    std::stringstream row_ss( data_value );
    string row_chars;

    while ( std::getline( row_ss, row_chars, '\n' ) ) {
        vector<int> row_ints;
        std::stringstream char_ss( row_chars );
        string x_y_char;

        while ( std::getline( char_ss, x_y_char, ',' ) ) {
            row_ints.push_back( std::stoi( x_y_char.c_str() ) );
        }
        int_map.push_back( row_ints );
    }

    return int_map;
}

/// \brief returns a 2d vector of Tile
///
/// returns a 2d vector of Tile from the file that includes per Tile:
/// * texture_id
/// * x position
/// * y position
/// * tile_type
///
/// \param map_node the node named map from the .tmx
/// \param int_map 2d vector of ints with texture values
/// \return returns a TileMap
TileMap WorldParser::_read_map( xml_node<> * map_node, vector<vector<int>> int_map )
{
    TileMap map;

    for ( int y = 1; y < int_map.size(); y++ ) {
        vector<Tile*> map_row;
        for ( int x = 0; x < int_map[y].size(); x++ ) {
            Tile* new_tile = new Tile;
            new_tile->texture_id = int_map[y][x];
            new_tile->type = NORMAL;
            map_row.push_back(new_tile);
        }
        map.push_back(map_row);
    }
    return map;
}

/// \brief changes tile_types of tiles with objects
///
/// checks the file for object and if object is found changes the tile_type of the tiles within the objects range.
/// for now only works with spawn objects.
///
/// \param map_node the node named map from the .tmx
/// \param map the current TileMap of this level to be edited with objects
void WorldParser::_read_objects( xml_node<> * map_node, TileMap map )
{
    xml_node<> * object_group_node = map_node->first_node("objectgroup");
    if ( object_group_node == 0 ) {
        throw exception( "file invalid no Objects" );
    }
    bool has_player_spawn = false;
    for ( xml_node<> * object_node = object_group_node->first_node("object"); object_node; object_node = object_node->next_sibling() ) {
        if ( std::strcmp(object_node->first_attribute("type")->value(), "Spawn") == 0 ) {
            int x = std::stoi( object_node->first_attribute( "x" )->value() ) / 64;
            int y = std::stoi( object_node->first_attribute( "y" )->value() ) / 64;
            map[x][y]->type = SPAWN;
            has_player_spawn = true;
        }
    }
    if ( !has_player_spawn ) {
        throw exception( "file invalid no SpawnPoint" );
    }
}
