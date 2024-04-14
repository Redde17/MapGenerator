#include "MapHandler.h"
#include "MapGenerator.h"
#include <thread>

//internal functions signature
void generateMapSlice(MapGenerator& MG, std::vector<std::vector<float>>& map, const int& fromX, const int& toX, const int& fromY, const int& toY);
float calculateCellSize(const int& sizeX, const int& sizeY);


//private functions
MapHandler::POI::POI(const int& x, const int& y) {
	this->x = x;
	this->y = y;
}

//public functions

MapHandler::MapHandler(const int& sizeX, const int& sizeY) {
	baseCellValue = 0.45f;

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	cellSize = calculateCellSize(sizeX, sizeY);

	mapTexture.create(sizeX * cellSize, sizeY * cellSize);

	map = *new std::vector<std::vector<float>>();
	map.resize(sizeX, std::vector<float>(sizeY, baseCellValue));

	tile = new sf::RectangleShape(sf::Vector2f(cellSize, cellSize));

	vertices_map.setPrimitiveType(sf::Quads);
	vertices_map.resize(sizeX * sizeY * 4);
}

void MapHandler::generateVertexMap() {
	sf::Color tileColor;

	//map generation
	for (size_t x = 0; x < sizeX; x++)
	{
		for (size_t y = 0; y < sizeY; y++)
		{
			sf::Vertex* quad = &vertices_map[(x + y * sizeY) * 4];

			quad[0].position = sf::Vector2f(x * cellSize, y * cellSize);
			quad[1].position = sf::Vector2f((x + 1) * cellSize, y * cellSize);
			quad[2].position = sf::Vector2f((x + 1) * cellSize, (y + 1) * cellSize);
			quad[3].position = sf::Vector2f(x * cellSize, (y + 1) * cellSize);

			float mapValue = map[x][y];

			//if(map[x][y] == 10)
			//	tileColor = sf::Color(255, 0, 0);
			if(map[x][y] > baseCellValue)
				tileColor = sf::Color(100 , 255 * (1.2 - mapValue), 50);
			//else if(map[x][y] > (BASE_CELL_VALUE + BASE_CELL_VALUE * .5f))
			//	tileColor = sf::Color(255, 255, 255 * mapValue);
			else 
				tileColor = sf::Color(77 * mapValue, 158 * mapValue, 255 * mapValue);

			quad[0].color = tileColor;
			quad[1].color = tileColor;
			quad[2].color = tileColor;
			quad[3].color = tileColor;
		}
	}

	//POI set generation
	tileColor = sf::Color(255, 0, 0);
	for (auto poi : pointsOfInterests) {
		sf::Vertex* quad = &vertices_map[(poi.x + poi.y * sizeY) * 4];
		
		quad[0].color = tileColor;
		quad[1].color = tileColor;
		quad[2].color = tileColor;
		quad[3].color = tileColor;
	}
}

void MapHandler::generateMap() {
	MapGenerator MG;

	std::vector<std::thread> threads;

	int startX = 0;
	int finishX = sizeX / THREADS_FOR_GENERATION;

	for (size_t i = 0; i < THREADS_FOR_GENERATION; i++) {
		threads.push_back(std::thread(
			generateMapSlice, 
			std::ref(MG), 
			std::ref(map), 
			startX, finishX,
			0, sizeY));

		startX = finishX;
		finishX += sizeX / THREADS_FOR_GENERATION;
	}


	for (auto& thread : threads)
		thread.join();
}

void MapHandler::generatePOIset(const int& amount) {
	srand(time(NULL));
	for (int i = 0; i < amount; i++)
	{
		int x = rand() % sizeX;
		int y = rand() % sizeY;

		//force generation on land
		if (map[x][y] < baseCellValue) {
			i--;
			continue;
		}

		pointsOfInterests.push_back(*new POI(x, y));
		//map[x][y] = 10;
	}
}

void MapHandler::deletePOIset() {
	pointsOfInterests.clear();
}

int MapHandler::getPOIamount() {
	return pointsOfInterests.size();
}

float MapHandler::getCellSize() {
	return cellSize;
}

std::vector<MapHandler::POI> MapHandler::getPOIs() {
	return pointsOfInterests;
}

//internal functions implementation
void generateMapSlice(MapGenerator& MG, std::vector<std::vector<float>>& map, const int& fromX, const int& toX, const int& fromY, const int& toY) {
	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
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

			if (n > 1.f)
				n = 1.f;
			else if (n < .0f)
				n = .0f;

			map[x][y] = n;

		}
	}
}

float calculateCellSize(const int& sizeX, const int& sizeY) {
	float cellSize = 2;
	
	//do something for dynamic size based on map dimension
	//or implement map navigation with static window size

	return cellSize;
}