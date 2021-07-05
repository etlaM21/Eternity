#pragma once

#include "Stroke.h"
#include <math.h> 

//--------------------------------------------------------------
Stroke::Stroke() {
	radius = 250;
	// Set first previous Point to something impossible to check later
	previousPoint = { -1, -1 };
	color = ofColor(255, 0, 0, 150);
	path.setFillColor(color);
	path.setFilled(true);
}

Stroke::Stroke(float _radius, ofColor _color, float _fadeAwayTime, float _driftAmount) {
	radius = _radius;
	initRadius = _radius;
	fadeAwayTime = _fadeAwayTime;
	// Set first previous Point to something impossible to check later
	previousPoint = { -1, -1 };
	color = _color;
	path.setFillColor(color);
	path.setFilled(true);
	driftAmount = _driftAmount;
	visible = true;
}

void Stroke::update() {
	// radius = initRadius + initRadius * ofRandom(1);
	if (strokePoints.size() > 0) {
		path.clear();
		float alpha = color.a;
		if (ofGetElapsedTimef() - creationTime > fadeAwayTime) {
			alpha -= 0.0025;
			color.a = alpha;
			if (alpha <= 0.01) {
				visible = false;
			}
			std::cout << "Alpha: " << alpha << "; Visible: " << visible << endl;
		}
		if (visible) {
			// Creater the first point depending on the rel difference the first strokePoint has
			// This is to make a more rounded brush-like start
			path.curveTo(strokePoints[0].x + (radius * 2 * firstPointRelDiff.x) * firstPointDiffSign.x, strokePoints[0].y + (radius * 2 * firstPointRelDiff.y) * firstPointDiffSign.y);
			// We create both sides of the strokes at once, but we have two draw the line per side, not per point
			// So we first connect even points then odd points
			for (int i = 0; i < strokePoints.size(); i++) {
				if (i % 2 == 0) {
					// path.curveTo(strokePoints[i]);
					// float alpha = 255 + ((strokePointsTimes[i] - ofGetElapsedTimef()) * 100);
					path.setColor(ofColor(color.r, color.g, color.g, alpha));
					path.curveTo(lerp(strokeCenterPoints[i], strokePoints[i], (strokePointsTimes[i] - ofGetElapsedTimef()) * driftAmount - 1));
				}
			}
			// Now we need to go backwards through our other list!
			for (int i = strokePoints.size(); i > 0; i--) {
				if (i % 2 != 0) {
					// path.curveTo(strokePoints[i]);
					// float alpha = 255 + ((strokePointsTimes[i] - ofGetElapsedTimef()) * 100);
					path.setColor(ofColor(color.r, color.g, color.g, alpha));
					path.curveTo(lerp(strokeCenterPoints[i], strokePoints[i], (strokePointsTimes[i] - ofGetElapsedTimef()) * driftAmount - 1));
				}
			}
			// Create the last point depending on the rel difference the last strokePoint has
			// This is to make a more rounded brush-like end
			path.curveTo(strokePoints[strokePoints.size() - 1].x + (radius * 5 * lastPointRelDiff.x) * lastPointDiffSign.x, strokePoints[strokePoints.size() - 1].y + (radius * 5 * lastPointRelDiff.y) * lastPointDiffSign.y);
			path.close();
		}
	}
}

void Stroke::addStrokePoint(int x, int y) {
	// Strokepoints Ansatz
	const glm::vec2 newPoint{ x, y };
	// If first point is set
	if (previousPoint.x != -1) {
		float diffX = abs(newPoint.x - previousPoint.x);
		float diffY = abs(newPoint.y - previousPoint.y);
		float diffTotal = diffX + diffY;
		float relDiffX = diffX / diffTotal;
		float relDiffY = diffY / diffTotal;
		// If no strokePoints were set so far
		if (strokePoints.size() <= 0) {
			strokePoints.push_back({ previousPoint.x - radius * relDiffX, previousPoint.y - radius * relDiffY });
			strokePoints.push_back({ previousPoint.x + radius * relDiffX, previousPoint.y + radius * relDiffY });
			firstPointRelDiff = { relDiffX, relDiffY };
			firstPointDiffSign = { copysignf(1.0, previousPoint.x - newPoint.x), copysignf(1.0, previousPoint.y - newPoint.y) };
		}
		strokePoints.push_back({ newPoint.x - radius * relDiffX, newPoint.y - radius * relDiffY });
		strokePoints.push_back({ newPoint.x + radius * relDiffX, newPoint.y + radius * relDiffY });
		lastPointRelDiff = { relDiffX, relDiffY };
		lastPointDiffSign = { copysignf(1.0, previousPoint.x - newPoint.x), copysignf(1.0, previousPoint.y - newPoint.y) };
	}
	else { // First Point
		previousPoint = { newPoint };
	}
	// We add the centerpoint two times because we always have two strokepoints and this makes life easier
	strokeCenterPoints.push_back(newPoint);
	strokeCenterPoints.push_back(newPoint);
	// We add the time two times because we always have two strokepoints and this makes life easier
	strokePointsTimes.push_back(ofGetElapsedTimef());
	strokePointsTimes.push_back(ofGetElapsedTimef());
	// By changing the creationTime with every new point added, we end up with counting the fade down only once we're finished with the stroke
	creationTime = ofGetElapsedTimef();
}

void Stroke::draw() {
	path.draw();
}

void Stroke::clean() {
	path.clear();
}

glm::vec2 Stroke::lerp(glm::vec2 x, glm::vec2 y, float t) {
	return x * (1.f - t) + y * t;
}