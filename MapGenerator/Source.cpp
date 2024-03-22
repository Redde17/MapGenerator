#include "GlobalInclude.h"
#include "MapHandler.h"

#define MAP_X 500
#define MAP_Y 500

int main() {
    //sf::RenderWindow window(sf::VideoMode(MAP_X * GRID_SIZE, MAP_Y * GRID_SIZE), "MapGenerator", sf::Style::Close);
    //window.setFramerateLimit(60);

    std::cout << "Program start" << std::endl;

    MapHandler MH(MAP_X, MAP_Y);

    MH.generateMap();
    MH.mapDraw();

    while (MH.windowIsOpen())
    {
        /*sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }*/
    }
    return 0;
}