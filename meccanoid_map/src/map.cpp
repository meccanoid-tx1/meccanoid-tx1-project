#include "map.hpp"

using namespace meccanoid_map;

/*
/ Default contructor
*/
Map::Map(){
    Map::generateDefaultMap();
}

/*
/ Map configuration constructor
*/
Map::Map(int arg){
    switch(arg){
        case 0:
            Map::generateMap0();
            break;
        case 1:
            Map::generateMap1();
            break;
        //TODO: possibly add more maps...
        default:
            Map::generateDefaultMap();
    }
}

void Map::generateMap0(){
    mapType = 0;
    //TODO: set up first map representation...
}

void Map::generateMap1(){
    mapType = 1;
    //TODO: set up second map representation...
}

void Map::generateDefaultMap(){
    mapType = -1;
    //TODO: set up default map representation...
}

// TODO: implement map logic