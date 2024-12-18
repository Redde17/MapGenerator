/**
* @file POI.cpp
* @brief Implementation of the POI class
*
* This class defines a point of interest on a 2D map by a set of coordinates.
*/

#include "POI.h"
#include <format>

/**
* @brief Constructor for POI, sets the coordinates of the point
*/
POI::POI(const int x, const int y) {
	this->x = x;
	this->y = y;
}

/**
* @brief Get the x value of the point
* @return x value of the point as an integer
*/
int POI::getX() const
{
	return x;
}

/**
* @brief Get the y value of the point
* @return y value of the point as an integer
*/
int POI::getY() const
{
	return y;
}

/**
* @brief Get the point as a string
* @return x and y value of the point formatted in a string
*/
std::string POI::toString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

bool POI::operator == (const POI& poi) const
{
	if (x == poi.x && y == poi.y)
		return true;
	return false;
}