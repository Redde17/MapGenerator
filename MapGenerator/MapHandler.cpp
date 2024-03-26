#include "MapHandler.h"
#include "MapGenerator.h"

//internal functions signature
float calculateCellSize(const int& sizeX, const int& sizeY);

//private functions
MapHandler::POI::POI(const int& x, const int& y) {
	this->x = x;
	this->y = y;
}

//public functions

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
			if (map[x][y] == 10)
				tile->setFillColor(sf::Color(255, 0, 0));
			else if (map[x][y] > BASE_CELL_VALUE)
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

	//should be possible to add multi threading for faster generation
	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			auto n = 0.0,
				a = 1.0,
				f = 0.005;
			for (int o = 0; o < 15; o++) {
				auto v = a * MG.noise2D(x * f, y * f);
				n += v;

				a *= 0.5;
				f *= 2.0;
			}
			n += 1.0;
			n *= 0.5;

			if (n > 1.f)
				n = 1.f;
			if (n < .0f)
				n = .0f;

			map[x][y] = n;
		}
	}
}

void MapHandler::generatePOI(const int& amount) {
	srand(time(NULL));
	for (int i = 0; i < amount; i++)
	{
		int x = rand() % sizeX;
		int y = rand() % sizeY;

		//force generation on land
		if (map[x][y] < BASE_CELL_VALUE) {
			i--;
			continue;
		}

		pointsOfInterests.push_back(*new POI(x, y));
		map[x][y] = 10;
	}
}

bool MapHandler::windowIsOpen() {

	sf::Event event;
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;
		default:
			break;
		}
	}

	return window->isOpen();
}

std::vector<MapHandler::POI> MapHandler::getPOIs() {
	return pointsOfInterests;
}

//internal functions implementation

float calculateCellSize(const int& sizeX, const int& sizeY) {
	float cellSize = 1;
	
	//do something for dynamic size based on map dimension
	//or implement map navigation with static window size

	return cellSize;
}