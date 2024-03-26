#include "GlobalInclude.h"
#include "MapHandler.h"

#include <chrono>
#include <thread>
#include <fstream>

using namespace std::chrono_literals;
using std::chrono::duration;
using std::chrono::high_resolution_clock;


#define MAP_X 500
#define MAP_Y 500

int main() {
    //sf::RenderWindow window(sf::VideoMode(MAP_X * GRID_SIZE, MAP_Y * GRID_SIZE), "MapGenerator", sf::Style::Close);
    //window.setFramerateLimit(60);

    std::cout << "Program start" << std::endl;

    MapHandler MH(MAP_X, MAP_Y);

    auto t1 = high_resolution_clock::now();
    MH.generateMap();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Map generation time: " << ms_double.count() << "ms\n";
    
    t1 = high_resolution_clock::now();
    MH.generatePOI(100);
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    std::cout << "POI generation time: " << ms_double.count() << "ms\n";

    t1 = high_resolution_clock::now();
    MH.mapDraw();
    t2 = high_resolution_clock::now();
    ms_double = t2 - t1;
    std::cout << "draw time: " << ms_double.count() << "ms\n";


    while (MH.windowIsOpen()) {}

    return 0;
}