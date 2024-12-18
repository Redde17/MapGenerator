#include "ColorGenerator.h"


ColorGenerator* ColorGenerator::instance = nullptr;

ColorGenerator::ColorGenerator(){
    vectorIndex = 0;

	//initialize colors pool
    // Add colors to the pool
    colorPool.push_back(new Color(sf::Color(255, 0, 0, 255)));     // Red
    colorPool.push_back(new Color(sf::Color(0, 0, 255, 255)));     // Blue
    colorPool.push_back(new Color(sf::Color(0, 255, 255, 255)));   // Cyan
    colorPool.push_back(new Color(sf::Color(255, 0, 255, 255)));   // Magenta
    colorPool.push_back(new Color(sf::Color(255, 165, 0, 255)));   // Orange
    colorPool.push_back(new Color(sf::Color(128, 0, 128, 255)));   // Purple
    colorPool.push_back(new Color(sf::Color(255, 192, 203, 255))); // Pink
    colorPool.push_back(new Color(sf::Color(165, 42, 42, 255)));   // Brown
    colorPool.push_back(new Color(sf::Color(0, 128, 128, 255)));   // Teal
    colorPool.push_back(new Color(sf::Color(139, 0, 0, 255)));     // Dark Red
    colorPool.push_back(new Color(sf::Color(0, 0, 139, 255)));     // Dark Blue
    colorPool.push_back(new Color(sf::Color(211, 211, 211, 255))); // Light Gray
    colorPool.push_back(new Color(sf::Color(169, 169, 169, 255))); // Dark Gray
    colorPool.push_back(new Color(sf::Color(64, 224, 208, 255)));  // Turquoise
    colorPool.push_back(new Color(sf::Color(220, 20, 60, 255)));   // Crimson
	
    availableColors = colorPool.size();
}

/**
* @brief Gets the singleton instance for ColorGenerator
* @return The instance to the singleton class ColorGenerator
*/
ColorGenerator* ColorGenerator::getInstance(){
	if(instance == nullptr)
        instance = new ColorGenerator();

	return instance;
}

/**
* @brief Frees a used color for future use.
* @param color Color to be freed for future use
*/
void ColorGenerator::freeColor(sf::Color color){
    for (auto pooledColor : colorPool) {
        if (pooledColor->color == color) {
            pooledColor->isUsed = false;
            availableColors++;
            vectorIndex--;
            return;
        }
    }
}

/**
* @brief Retrieves a color from a pool of colors and locks it.
* @return The color retrieved from the pool
*/
sf::Color* ColorGenerator::generateColor() {
    //logic for color generation
    Color* color = nullptr;
    for (int i = 0; i < colorPool.size(); i++) {
        color = colorPool[vectorIndex % colorPool.size()];
        vectorIndex++;
        if (!color->isUsed)
            break;
    }

    if(color == nullptr) {
        return nullptr;
    } else {
        availableColors--;
        return &color->color;
    }
}

int ColorGenerator::getAvailableColorsAmount() const
{
    return availableColors;
}
