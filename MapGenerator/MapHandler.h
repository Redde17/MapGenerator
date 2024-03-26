#pragma once

#include "GlobalInclude.h"

#define APP_NAME "MapGenerator"
#define BASE_CELL_VALUE 0.55f

class MapHandler
{
public:
	struct POI {
		int x, y;

		POI(const int& x, const int& y);
	};

private:
	sf::RenderWindow* window;
	std::vector<std::vector<float>> map;
	std::vector<POI> pointsOfInterests;

	sf::RectangleShape* tile;

	int sizeX, sizeY;
	float cellSize;

public:
	//MapHandler();
	MapHandler(const int &sizeX, const int& sizeY);

	void mapDraw();
	void generateMap();
	void generatePOI(const int& amount);
	std::vector<POI> getPOIs();

	//window access function
	bool windowIsOpen();
};

