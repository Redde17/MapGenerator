/**
* @file MapHandler.cpp
* @brief Implementation of the MapHandler class
*
* This class handles the map drawing process and elaboration including the POI generation
*/

#include "MapHandler.h"

#include <random>

#include "MapGenerator.h"
#include "POI.h"
#include <thread>

#include "ColorGenerator.h"

//internal functions signature
void generateMapSlice(MapGenerator& MG, std::vector<std::vector<float>>& map, const int& fromX, const int& toX, const int& fromY, const int& toY);
float calculateCellSize(const int& sizeX, const int& sizeY);
float linearMapValue(float min, float max, float value);
sf::Color interpolateColor(sf::Color color1, sf::Color color2, float interpolationValue);

//public functions

MapHandler::MapHandler(const int& sizeX, const int& sizeY) {
	srand(time(NULL));

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

/**
* @brief Generate the vertex map inside a VertexArray
*/
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
			//generates a cell inside the map 4 using vertices
			sf::Vertex* quad = &vertices_map[(x + y * sizeY) * 4];

			quad[0].position = sf::Vector2f(x * cellSize, y * cellSize);
			quad[1].position = sf::Vector2f((x + 1) * cellSize, y * cellSize);
			quad[2].position = sf::Vector2f((x + 1) * cellSize, (y + 1) * cellSize);
			quad[3].position = sf::Vector2f(x * cellSize, (y + 1) * cellSize);

			//assing the generated cell a color based on it's float value 

			float mapValue = map[x][y];
			float val = map[x][y];
			//land
			float landSize = 1 - baseCellValue;
			if (val >= baseCellValue + (landSize * .85f)) //10% of landSize
				tileColor = mountainPeakColor;
			else if (val >= baseCellValue + (landSize * .8f)) //10% of landSize
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
	for (Cluster* cluster : clusters)
	{
		tileColor = cluster->getClusterColor();
		std::list<POI*>* poiList = cluster->getPoints();
		for (POI* poi : *poiList)
		{
			sf::Vertex* quad = &vertices_map[(poi->getX() + poi->getY() * sizeY) * 4];

			quad[0].color = tileColor;
			quad[1].color = tileColor;
			quad[2].color = tileColor;
			quad[3].color = tileColor;
		}
		
	}
}

/**
* @brief Draws the map stored inside the VertexArray into a RenderTexture
*/
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

/**
* @brief Adds a cluster to the vector of clusters on the map
*/
void MapHandler::addCluster(Cluster* cluster) {
	clusters.push_back(cluster);
}

/**
* @brief Removes a cluster from the vector of clusters on the map
* @param i Index of the cluster to be removed
*/
void MapHandler::removeCluster(int i) {
	ColorGenerator* CG = ColorGenerator::getInstance();

	CG->freeColor(clusters.at(i)->getClusterColor());
	clusters.erase(clusters.begin() + i);
}

/**
* @brief Removes all clusters from the vector of clusters on the map
*/
void MapHandler::removeAllClusters(){
	ColorGenerator* CG = ColorGenerator::getInstance();

	for (auto cluster : clusters) {
		CG->freeColor(clusters.back()->getClusterColor());
		clusters.pop_back();
	}
}

/**
* @brief Gets a cluster from the vector of clusters on the map
* @param i Index of the cluster to get
*/
Cluster* MapHandler::getCluster(int i) const {
	return clusters[i];
}

/**
* @brief Gets the vector of clusters on the map
*/
std::vector<Cluster*>* MapHandler::getAllClusters() {
	return &clusters;
}

/**
* @brief Return the amount of clusters in the clusters vector
*/
int MapHandler::getClustersAmount() const {
	return clusters.size();
}

/**
* @brief Calculates the amount of points of interest in all the clusters
* @return An integer representing the total amount od points of interest
*/
int MapHandler::getPointsAmount() const {
	int amount = 0;
	for (Cluster* cluster : clusters)
		amount += cluster->getPointsAmount();

	return amount;
}

/**
* @brief Generates a random cluster of points of interest
* @param size amount od POI inside the cluster
*/
//TODO:Implement cluster generation
void MapHandler::generateRandomCluster(int size) {
	Cluster* cluster = new Cluster();

	ColorGenerator* CG = ColorGenerator::getInstance();
	cluster->setClusterColor(*CG->generateColor());

	//generate random POIs and add them to the cluster
	for (int i = 0; i < size; i++)
	{
		int x = rand() % sizeX;
		int y = rand() % sizeY;

		//force generation on land
		if (map[x][y] < baseCellValue) {
			i--;
			continue;
		}

		cluster->addPoint(*new POI(x, y));
		//map[x][y] = 10;
	}

	addCluster(cluster);
}



/**
* @brief Get a reference of the points of interest on the map
* @return Single cell size
*/
float MapHandler::getCellSize() {
	return cellSize;
}


//internal functions implementation

/**
* @brief Generates a portion of the map and adds noise for improved looks
* @param MG instance of the map generator passed by reference
* @param map instance of the map passed by reference
* @param fromX starting point on the x axis passed by reference
* @param toX ending point on the x axis passed by reference
* @param fromY starting point on the y axis passed by reference
* @param toY ending point on the y axis passed by reference
*/
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

/**
* @brief Calculate the Size for each pixel on the map
* @param sizeX width of the map
* @param sizeY height of the map
* @return The value of cellSize
*/
float calculateCellSize(const int& sizeX, const int& sizeY) {
	float cellSize = 2;

	//TODO:
	//do something for dynamic size based on map dimension
	//or implement map navigation with static window size

	return cellSize;
}

/**
* @brief Calculate the passed value inside a range of 0 and 1
* @param min min value of the range
* @param max max value of the range
* @return The normalized value inside of a range from 0 to 1
*/
float linearMapValue(float min, float max, float value) {
	//should return the value from the min max range in normalized form 0-1
	float mapRangeMin = 0;
	float mapRangeMax = 1;

	return mapRangeMin + ((mapRangeMax - mapRangeMin) / (max - min)) * (value - min);
}

/**
* @brief Calculate the color interpolation between two colors
* @param color1 first color
* @param color2 second color
* @interpolationValue interpolation strenght
* @return The new color generated from the interpolation
*/
sf::Color interpolateColor(sf::Color color1, sf::Color color2, float interpolationValue) {
	return sf::Color(
		(1.f - interpolationValue) * color1.r + interpolationValue * color2.r,
		(1.f - interpolationValue) * color1.g + interpolationValue * color2.g,
		(1.f - interpolationValue) * color1.b + interpolationValue * color2.b
	);
}