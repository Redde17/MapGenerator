#pragma once
#include "GlobalInclude.h"

class MapGenerator
{
public:
	class Vector2 {
		float x, y;
	public:
		Vector2(const float& x, const float& y);
		float dot(Vector2 other);
	};

	const std::vector<unsigned char> permutationTable = generatePermutationTable();

	float noise2D(const float& x, const float& y);
	std::vector<unsigned char> generatePermutationTable();


};

