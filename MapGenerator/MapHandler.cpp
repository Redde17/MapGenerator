#include "MapHandler.h"
#include "MapGenerator.h"

//internal functions signature
float calculateCellSize(const int& sizeX, const int& sizeY);

//private functions

//public functions
//MapHandler::MapHandler() {
//	MapHandler(1, 1);
// }

MapHandler::MapHandler(const int& sizeX, const int& sizeY) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	cellSize = calculateCellSize(sizeX, sizeY);

	window = new sf::RenderWindow(sf::VideoMode(sizeX * cellSize, sizeY * cellSize), APP_NAME, sf::Style::Close);
	map = *new std::vector<std::vector<float>>();
	map.resize(sizeX, std::vector<float>(sizeY, BASE_CELL_VALUE));

	tile = new sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
}

void MapHandler::mapDraw() {
	window->clear();

	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {

			tile->setPosition(sf::Vector2f(x * cellSize, y * cellSize));
			if (map[x][y] > BASE_CELL_VALUE)
				tile->setFillColor(sf::Color(0, 255 * (1.2f - map[x][y]), 0));
			else 
				tile->setFillColor(sf::Color(0, 0, 255 * map[x][y]));
			window->draw(*tile);
		}
	}

	window->display();
}

void MapHandler::generateMap() {
	MapGenerator MG;

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			auto n = 0.0,
				a = 1.0,
				f = 0.005;
			for (int o = 0; o < 8; o++) {
				auto v = a * MG.noise2D(x * f, y * f);
				n += v;

				a *= 0.5;
				f *= 2.0;
			}
			n += 1.0;
			n *= 0.5;

			//std::cout << "noiseValue[" << x << "][" << y << "]" << n << std::endl;
			
			if (n > 1.f)
				n = 1.f;
			if (n < .0f)
				n = .0f;

			map[x][y] = n;
		}
	}
}

bool MapHandler::windowIsOpen() {
	return window->isOpen();
}

//internal functions implementation

float calculateCellSize(const int& sizeX, const int& sizeY) {
	float cellSize = 1;
	
	//do something for dynamic size based on map dimension
	//or implement map navigation with static window size

	return cellSize;
}