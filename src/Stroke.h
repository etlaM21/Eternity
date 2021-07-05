#pragma once

#include "ofMain.h"

class Stroke {

public:
	Stroke();
	Stroke(float _radius, ofColor _color, float _fadeAwayTime, float _driftAmount);
	void update();
	void addStrokePoint(int x, int y);
	void draw();
	void clean();
	// Helper Functions
	glm::vec2 lerp(glm::vec2 x, glm::vec2 y, float t);


	float radius;
	float driftAmount;
	ofColor color;
	float fadeAwayTime;

	float initRadius;
	float creationTime;
	bool visible;

	ofPath path;
	std::vector <glm::vec2> strokePoints;
	std::vector <glm::vec2> strokeCenterPoints;
	std::vector <float> strokePointsTimes;

	glm::vec2 previousPoint;
	glm::vec2 firstPointRelDiff;
	glm::vec2 firstPointDiffSign;
	glm::vec2 lastPointRelDiff;
	glm::vec2 lastPointDiffSign;
};