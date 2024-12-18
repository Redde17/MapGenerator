#pragma once
#include <string>

class POI
{
private:
	int x, y;

public:
	POI(const int x, const int y);

	int getX() const;
	void setX(int x);

	int getY() const;
	void setY(int y);

	std::string toString() const;

	bool operator == (const POI& poi) const;
};

