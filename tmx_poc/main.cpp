#include "WorldParser.hpp"
#include "Level.hpp"


int main( void )
{
    WorldParser* world_parser = new WorldParser();
    //succes: test.tmx, test2.tmx or stress_test.tmx fail: test_no_objects.tmx
    Level* level_test = world_parser->generate_level("res/test.tmx");

    delete world_parser;
    return 0;
}