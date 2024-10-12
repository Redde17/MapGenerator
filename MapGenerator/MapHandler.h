/**
* @file MapHandler.h
*
*/

#pragma once

#include "GlobalInclude.h"
#include "POI.h"

#define APP_NAME "MapGenerator"
//#define BASE_CELL_VALUE 0.45f

#define THREADS_FOR_GENERATION std::thread::hardware_concurrency()

class MapHandler
{
private:
	std::vector<std::vector<float>> map;
	std::vector<POI> pointsOfInterests;

	sf::RectangleShape* tile;

	int sizeX, sizeY;
	float cellSize;

public:
	float baseCellValue;
	sf::RenderTexture mapTexture;
	sf::VertexArray vertices_map;
	sf::RenderTexture colorInterpolationTexture;

	MapHandler(const int &sizeX, const int& sizeY);
	void generateVertexMap();
	void generateMap();
	void generatePOIset(const int& amount);
	void deletePOIset();
	int getPOIamount();
	std::vector<POI> getPOIs();
	float getCellSize();
	void generateColorInterpolationTexture();
};
