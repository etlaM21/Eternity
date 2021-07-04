#pragma once

#include "ofMain.h"

class Stroke {

public:
	Stroke();
	void update();
	void addStrokePoint(int x, int y);
	void draw();


	float radius;
	ofPath path;
	std::vector <glm::vec2> strokePoints;
	glm::vec2 previousPoint;
	glm::vec2 firstPointRelDiff;
	glm::vec2 firstPointDiffSign;
	glm::vec2 lastPointRelDiff;
	glm::vec2 lastPointDiffSign;
};