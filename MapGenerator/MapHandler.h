/**
* @file MapHandler.h
*
*/

#pragma once

#include "Cluster.h"
#include "GlobalInclude.h"
#include "POI.h"

#define APP_NAME "MapGenerator"
//#define BASE_CELL_VALUE 0.45f

#define THREADS_FOR_GENERATION std::thread::hardware_concurrency()

class MapHandler
{
private:
	std::vector<std::vector<float>> map;

	//std::vector<POI> pointsOfInterests;
	//Cluster poiCluster;

	std::vector<Cluster*> clusters;

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

	void addCluster(Cluster *cluster);
	void removeCluster(int i);
	void removeAllClusters();
	Cluster* getCluster(int i) const;
	std::vector<Cluster*>* getAllClusters();

	int getClustersAmount() const;
	int getPointsAmount() const;

	void generateRandomCluster(int size);

	float getCellSize();
	void generateColorInterpolationTexture();
};
