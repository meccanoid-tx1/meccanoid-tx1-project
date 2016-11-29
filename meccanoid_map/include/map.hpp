#pragma once
namespace meccanoid_map{

class Map{

    public:
        Map();
        Map(int);
        void generateMap0(void);
        void generateMap1(void);
        void generateDefaultMap(void);

    private:
        int mapType;

        //TODO: add map logic
};

}