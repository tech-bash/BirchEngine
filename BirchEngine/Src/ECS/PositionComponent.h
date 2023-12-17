#pragma once

#include "ECS.h"

class PositionComponent : public Component {
private:
	int xPos, yPos;

public:

	PositionComponent() {
		xPos = 0;
		yPos = 0;
	}

	PositionComponent(int x, int y) {
		xPos = x;
		yPos = y;
	}

	int x() { return xPos; }
	int y() { return yPos; }

	void x(int x) { xPos = x; }
	void y(int y) { yPos = y; }

	void setPos(int x, int y) {
		xPos = x;
		yPos = y;

	}

	void update() override
	{
		xPos++;
		yPos++;
	}
};