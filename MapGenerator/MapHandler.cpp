#include "MapHandler.h"
#include "MapGenerator.h"
#include "POI.h"
#include <thread>

//internal functions signature
void generateMapSlice(MapGenerator& MG, std::vector<std::vector<float>>& map, const int& fromX, const int& toX, const int& fromY, const int& toY);
float calculateCellSize(const int& sizeX, const int& sizeY);
float linearMapValue(float min, float max, float value);
sf::Color interpolateColor(sf::Color color1, sf::Color color2, float interpolationValue);

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

	sf::Color plainsColor(63, 156, 56);
	sf::Color shoreColor(242, 223, 78);
	sf::Color mountainColor(67, 117, 38);
	sf::Color mountainPeakColor(255, 255, 255);
	sf::Color seaColor(72, 203, 250);
	sf::Color deepSeaColor(24, 53, 158);

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

			float val = map[x][y];
			//land
			float landSize = 1 - baseCellValue;
			if (val >= baseCellValue + (landSize * .85f)) //10% of landSize
				tileColor = mountainPeakColor;
			else if(val >= baseCellValue + (landSize * .8f)) //10% of landSize
				tileColor = interpolateColor(mountainColor, mountainPeakColor, linearMapValue(baseCellValue + (landSize * .8f), baseCellValue + (landSize * .9f), val));
			else if (val >= baseCellValue + (landSize * .5f)) //30% of landSize
				tileColor = mountainColor;
			else if (val >= baseCellValue + (landSize * .45f)) //5% of landSize
				tileColor = interpolateColor(plainsColor, mountainColor, linearMapValue(baseCellValue + (landSize * .45f), baseCellValue + (landSize * .5f), val));
			else if (val >= baseCellValue + (landSize * .05f)) //40% of landSize
				tileColor = plainsColor;
			else if (val >= baseCellValue)//5% of landSize
				tileColor = shoreColor;
			//sea, note that sea size is base cell value 
			else if (val >= baseCellValue * .9f) //10% of sea size
				tileColor = seaColor;
			else if (val >= baseCellValue * .1f) //80% of sea size
				tileColor = interpolateColor(deepSeaColor, seaColor, linearMapValue(baseCellValue * .1f, baseCellValue * .9f, val));
			else if (val >= 0) //10% of sea size
				tileColor = deepSeaColor;

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

std::vector<POI> MapHandler::getPOIs() {
	return pointsOfInterests;
}

float MapHandler::getCellSize() {
	return cellSize;
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

//should return the value from the min max range in normalized form 0-1
float linearMapValue(float min, float max, float value) {
	float mapRangeMin = 0;
	float mapRangeMax = 1;

	return mapRangeMin + ((mapRangeMax - mapRangeMin) / (max - min)) * (value - min);
}

sf::Color interpolateColor(sf::Color color1, sf::Color color2, float interpolationValue) {
	//return sf::Color(
	//	color1.r + (color2.r - color1.r) * interpolationValue,
	//	color1.g + (color2.g - color1.b) * interpolationValue,
	//	color1.b + (color2.g - color1.b) * interpolationValue
	//);

	return sf::Color(
		(1.f - interpolationValue) * color1.r + interpolationValue * color2.r,
		(1.f - interpolationValue) * color1.g + interpolationValue * color2.g,
		(1.f - interpolationValue) * color1.b + interpolationValue * color2.b
	);
}