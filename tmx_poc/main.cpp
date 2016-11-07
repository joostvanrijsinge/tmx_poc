#include "WorldParser.hpp"
#include "Level.hpp"


int main( void )
{
    WorldParser* world_parser = new WorldParser();
    Level* level_test = world_parser->generate_level( "res/test.tmx" );//test.tmx, test2.tmx or stress_test.tmx
    
    delete world_parser;
    return 0;
}