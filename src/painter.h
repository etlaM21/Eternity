#pragma once

#include "ofMain.h"
#include "Stroke.h"
#include "Brush.h"

class Painter {

public:
	Painter();
	Painter(string name);

	Brush brush;
	Stroke strokeStyle;
	std::vector <ofColor> palette;

	void paint();
	void showCanvas();

	// Helper
	bool finishedStroke;
	int width;
	int height;

	// Behaviour
	int slowDownThreshhold;
	float noiseInfluence;
	int hitRadius;
	float maxSpeed;
	float maxForce;

	void start();
	void seek(glm::vec2 target);
	void applyForce(glm::vec2 force);
	bool targetHit();
	void update();
	void drawAgent();

	glm::vec2 location;
	glm::vec2 lastLocation;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	glm::vec2 target;
};