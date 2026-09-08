#include "checkCollision.h"
#include <cmath>

bool checkCollision(float x1, float y1, float radius1, float x2, float y2, float radius2) {
	float xDistance = x1 - x2;
	float yDistance = y1 - y2;
	float objectDistance = std::sqrt((xDistance * xDistance) + (yDistance * yDistance));

	if (objectDistance <= radius1 + radius2) {
		return true;
	}
	else {
		return false;
	}
}