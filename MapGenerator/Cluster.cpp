#include "Cluster.h"

#include <iostream>

Cluster::Cluster()
{
	centroid = new POI(0, 0);
	clusterColor = sf::Color(255, 0, 0);

}

/**
 * @brief Create a new cluster based on a list of points.
 * Create a new cluster based on a list of points passed as param.
 * The default color for the cluster is Red.
 * @param points list of the POIs to be added to the cluster
 */
Cluster::Cluster(std::list<POI*>& points)
{
	this->points = points;

	//calculate centroid based on points passed
	updateCentroid();

	//set default color
	clusterColor = sf::Color(255, 0, 0);
}

Cluster::~Cluster()
{
	delete centroid;
	points.clear();
	//delete clusterColor;
}

/**
* @brief Update the centroid of the cluster with the new POI
* Updates the centroid only with the newPoi passed as a param.
* This function purpose is to calculate the centroid faster when a new POI is added to the cluster.
*
* @param newPoi the new POI that has been added to the cluster
*/
//void Cluster::updateCentroid(const POI& newPoi)
//{
//	//if there are no other points in the list sets the
//	//centroid coordinates to the ones of the newPoi and returns
//	if(points.size() == 1)
//	{
//		centroid->setX(newPoi.getX());
//		centroid->setY(newPoi.getY());
//		return;
//	}
//
//	//else calculate the mean value between the centroid and the new POI
//	centroid->setX((centroid->getX() + newPoi.getX()) / 2); // (centroid.x + newPoi.x) / 2
//	centroid->setY((centroid->getY() + newPoi.getY()) / 2); // (centroid.y + newPoi.y) / 2
//}

/**
* @brief Gets the amount of points of interest inside the cluster
* @return Amount of points as an integer
*/
int Cluster::getPointsAmount() const
{
	return points.size();
}

std::list<POI*>* Cluster::getPoints()
{
	return &points;
}

/**
* @brief Gets the reference to a specific point
* @param x X coordinate of the point
* @param y Y coordinate of the point
* @return Pointer to the POI
*/
POI* Cluster::getPoint(const int x, const int y) const
{
	POI* tempPoint = new POI(x, y);

	for (auto point : points)
		if (point == tempPoint) {
			delete tempPoint;
			return point;
		}

	delete tempPoint;
	return nullptr;
}

/**
* @brief Gets the center point of the cluster
* @return Copy of the POI with the coordinates of the centroid
*/
POI Cluster::getCentroid() const
{
	return *centroid;
}

/**
* @brief Adds a POI the to the cluster
* @param point reference to the POI to be added
*/
void Cluster::addPoint(POI& point)
{
	//add new point
	points.push_back(&point);

	//update centroid
	//updateCentroid(point);
	updateCentroid();
}

/**
* @brief Remove a POI from the cluster
* @param point reference to the POI to be removed
* @return true if the POI has been removed \n false if the POI has not been found
*/
bool Cluster::removePoint(const POI& point)
{
	//NEEDS TESTING
	//try to remove point
	std::list<POI*>::iterator it = points.begin();
	while(it != points.end())
	{
		if(*it == &point)
		{
			//remove point
			points.remove(*it);

			//update centroid 
			updateCentroid();
			return true;
		}
	}

	return false;
}

/**
* @brief Sets the cluster POIs color using RGB
* @param color new color for the cluster
*/
void Cluster::setClusterColor(const sf::Color color)
{
	//first delete the old color then set the new one
	//if(clusterColor != null)
	//	delete clusterColor;
	//TODO: Look into possible memory leak from clusterColor
	//can't delete cluster Color

	clusterColor = color;
}

/**
* @brief Gets the cluster POIs color
* @return Color of the cluster
*/
sf::Color Cluster::getClusterColor()
{
	return clusterColor;
}

/**
* @brief Sets the value for the auto update centroid flag
* @param newValue new bool value of the flag
*/
void Cluster::setAutoUpdateCentroidFlag(const bool newValue)
{
	autoUpdateCentroid = newValue;
}

/**
* @brief Gets the value for the auto update centroid flag
* @param value
*/
bool Cluster::getAutoUpdateCentroidFlag() const
{
	return autoUpdateCentroid;
}

/**
* @brief Update the centroid of the cluster by recalculating it
* Update the centroid of the cluster by recalculating it.
* The centroid coordinates are calculated based on the mean value
* of the x and y coordinates of all points inside the cluster.
*/
void Cluster::updateCentroid()
{
	//float sumX = 0, sumY = 0;
	//float centroidX, centroidY;

	////get the sum of the x coordinates and y coordinates of the points in the list
	//for (auto point : points)
	//{
	//	sumX += point->getX();
	//	sumY += point->getY();
	//}

	////update centroid
	//centroid->setX(sumX / points.size());
	//centroid->setY(sumY / points.size());
}

int Cluster::getClusterSize()
{
	return points.size();
}

