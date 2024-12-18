#pragma once
#include <vector>
#include "GlobalInclude.h"

class ColorGenerator{
private:
	//offers a pool of colors usable only once
	struct Color{
		sf::Color color;
		bool isUsed = false;

		Color(sf::Color color)
		{
			this->color = color;
		}
	};

	std::vector<Color*> colorPool;
	int availableColors;
	int vectorIndex;

protected:
	static ColorGenerator* instance;

	ColorGenerator();

public:
	static ColorGenerator* getInstance();

	ColorGenerator(ColorGenerator& other) = delete;
	void operator = (const ColorGenerator&) = delete;

	void freeColor(sf::Color color);
	sf::Color* generateColor();

	int getAvailableColorsAmount() const;
};

