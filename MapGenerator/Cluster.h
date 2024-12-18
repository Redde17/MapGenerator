#pragma once
#include <list>
#include <SFML/Graphics/Color.hpp>

#include "POI.h"

class Cluster
{
private:
	const sf::Color DEFAULT_COLOR = sf::Color(255, 0, 0); //red

	POI* centroid;
	std::list<POI*> points;
	sf::Color clusterColor;
	bool autoUpdateCentroid;

	//void updateCentroid(const POI& newPoi);
public:
	Cluster();
	Cluster(std::list<POI*>& points);

	~Cluster();

	int getPointsAmount() const;
	std::list<POI*>* getPoints();
	POI* getPoint(const int x, const int y) const;

	POI getCentroid() const;

	void addPoint(POI& point);
	bool removePoint(const POI& point);

	void setClusterColor(const sf::Color color);
	sf::Color getClusterColor();

	void setAutoUpdateCentroidFlag(const bool newValue);
	bool getAutoUpdateCentroidFlag() const;

	void updateCentroid();
	int getClusterSize();
};