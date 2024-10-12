/**
* @file MapGenerator.cpp
* @brief Implementation of the perlin noise algorithm
* 
* This class implements all the necessary functions to generate perlin noise
*/

#include "MapGenerator.h"
#include <corecrt_math.h>

//Vector2 class implementation
MapGenerator::Vector2::Vector2(const float& x, const float& y) {
	this->x = x;
	this->y = y;
}

float MapGenerator::Vector2::dot(Vector2 other) {
	return this->x * other.x + this->y * other.y;
}

//MapGenerator class implementation

//internal functions signture
void shuffle(std::vector<unsigned char>& vector);
MapGenerator::Vector2 getConstantVector(const unsigned char& permutationValue);
float fade(const float& t);
float lerp(const float& t, const float& a1, const float& a2);

//class functions

float MapGenerator::noise2D(const float& x, const float& y) {
	int xFloor = floor(x);
	int yFloor = floor(y);

	const auto X = xFloor & 255;
	const auto Y = yFloor & 255;

	const auto xf = x - xFloor;
	const auto yf = y - yFloor;

	Vector2 topRight(xf - 1.0, yf - 1.0);
	Vector2 topLeft(xf, yf - 1.0);
	Vector2 bottomRight(xf - 1.0, yf);
	Vector2 bottomLeft(xf, yf);

	const auto valueTopRight = permutationTable[permutationTable[X + 1] + Y + 1];
	const auto valueTopLeft = permutationTable[permutationTable[X] + Y + 1];
	const auto valueBottomRight = permutationTable[permutationTable[X + 1] + Y];
	const auto valueBottomLeft = permutationTable[permutationTable[X] + Y];


	const auto dotTopRight = topRight.dot(getConstantVector(valueTopRight));
	const auto dotTopLeft = topLeft.dot(getConstantVector(valueTopLeft));
	const auto dotBottomRight = bottomRight.dot(getConstantVector(valueBottomRight));
	const auto dotBottomLeft = bottomLeft.dot(getConstantVector(valueBottomLeft));

	const auto u = fade(xf);
	const auto v = fade(yf);

	return lerp(u,
		lerp(v, dotBottomLeft, dotTopLeft),
		lerp(v, dotBottomRight, dotTopRight)
	);
}

std::vector<unsigned char> MapGenerator::generatePermutationTable() {
	std::vector<unsigned char> permutationTable;
	for (int i = 0; i < 256; i++)
		permutationTable.push_back(i);

	//shuffle
	shuffle(permutationTable);

	for (int i = 0; i < 256; i++)
		permutationTable.push_back(permutationTable[i]);

	return permutationTable;
}

void shuffle(std::vector<unsigned char>& vector) {
	srand(time(NULL));

	/*
	for(let e = arrayToShuffle.length-1; e > 0; e--) {
		const index = Math.round(Math.random()*(e-1));
		const temp = arrayToShuffle[e];
		
		arrayToShuffle[e] = arrayToShuffle[index];
		arrayToShuffle[index] = temp;
	}
	*/

	for (int i = vector.size() - 1; i > 0; i--)
	{
		//get random index
		const auto index = rand()%i;
		const auto temp = vector[i];

		vector[i] = vector[index];
		vector[index] = temp;
	}
}

const MapGenerator::Vector2 constVectorPP(1.0, 1.0);
const MapGenerator::Vector2 constVectorMP(-1.0, 1.0);
const MapGenerator::Vector2 constVectorMM(-1.0, -1.0);
const MapGenerator::Vector2 constVectorPM(1.0, -1.0);

MapGenerator::Vector2 getConstantVector(const unsigned char& permutationValue) {
	const auto h = permutationValue & 3;
	if (h == 0)
		return constVectorPP;
	else if (h == 1)
		return constVectorMP;
	else if (h == 2)
		return constVectorMM;
	else
		return constVectorPM;
}

float fade(const float& t) {
	return ((6 * t - 15) * t + 10) * t * t * t;
}

float lerp(const float& t, const float& a1, const float& a2) {
	return a1 + t * (a2 - a1);
}