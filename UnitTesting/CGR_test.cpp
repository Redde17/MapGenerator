#include "pch.h"
#include "CGR_test.h"

//#include "../MapGenerator/ColorGenerator.h"


/**
* @brief Test for correct ColorGeneration class initialization
*/
//TEST(ColorGenerationTestSuite, test_01)
//{
//	ColorGenerator* CG = ColorGenerator::getInstance();
//	ASSERT_EQ(CG->getAvailableColorsAmount(), 15)
//	<< "Color amount [" << CG->getAvailableColorsAmount() << "] does not match to expected value [15]";
//}
//
///**
//* @brief Test for correct color generation
//*/
//TEST(ColorGenerationTestSuite, test_02)
//{
//	ColorGenerator* CG = ColorGenerator::getInstance();
//
//	sf::Color color = CG->generateColor();
//	if(color == NULL)
//		FAIL() << "No color has been generated";
//
//	if(CG->getAvailableColorsAmount() > 14)
//		FAIL() << "Color has been generated but available colors are more then expected";
//
//	if (CG->getAvailableColorsAmount() < 14)
//		FAIL() << "Color has been generated but available colors are less then expected";
//
//
//}
//
///**
//* @brief Test for correct free color operation
//*/
//TEST(ColorGenerationTestSuite, test_03)
//{
//	ColorGenerator* CG = ColorGenerator::getInstance();
//
//	sf::Color color = CG->generateColor();
//
//	if (color == NULL)
//		FAIL() << "No color has been generated";
//
//	CG->freeColor(color);
//
//	if (CG->getAvailableColorsAmount() > 15)
//		FAIL() << "Color has been generated but available colors are more then expected";
//
//	if (CG->getAvailableColorsAmount() < 15)
//		FAIL() << "Color has been generated but available colors are less then expected";
//
//
//}