#pragma once

#include "ofMain.h"
#include "Stroke.h"

class Brush {

	public:
		Brush();
		Brush(float _size, int _hairs, int _maxStrokes, Stroke _strokeStyle);

		void updateStrokes();
		void drawStrokes();
		void addStroke(ofColor strokeColor);
		void cleanStrokes();
		// Debug / Testing
		void paint(glm::vec2 paintPos, float pressure);
		// Agent
		void setupAgent();
		// Agent
		void updateAgent();
		// Agent
		void drawAgent();
		float slowDownThreshhold;
		float noiseInfluence;
		float hitRadius;

	private:
		float size;
		int hairs;
		std::vector<std::vector <Stroke>> strokes;
		int maxStrokes;
		Stroke strokeStyle;

		// Agent
		glm::vec2 location;
		glm::vec2 lastLocation;
		glm::vec2 velocity;
		glm::vec2 acceleration;
		glm::vec2 target;
		float maxSpeed;
		float maxForce;

		void seek(glm::vec2 target);
		void applyForce(glm::vec2 force);
		bool targetHit();
};