#pragma once

#include "GlobalInclude.h"

#define APP_NAME "MapGenerator"
#define BASE_CELL_VALUE 0.5f

class MapHandler
{
private:
	sf::RenderWindow* window;
	std::vector<std::vector<float>> map;

	sf::RectangleShape* tile;

	int sizeX, sizeY;
	float cellSize;


public:
	//MapHandler();
	MapHandler(const int &sizeX, const int& sizeY);

	void mapDraw();
	void generateMap();

	//window access function
	bool windowIsOpen();
};

