#pragma once

#include "Stroke.h"
#include <math.h> 

//--------------------------------------------------------------
Stroke::Stroke() {
	radius = 100;
	// Set first previous Point to something impossible to check later
	previousPoint = { -1, -1 };
	path.setFillColor(ofColor(255, 0, 0, 150));
	path.setFilled(true);
}

void Stroke::update() {
	radius = 20 + 5 * ofRandom(1);
	if (strokePoints.size() > 0) {
		path.clear();
		// Creater the first point depending on the rel difference the first strokePoint has
		// This is to make a more rounded brush-like start
		path.curveTo(strokePoints[0].x + (radius * 2 * firstPointRelDiff.x) * firstPointDiffSign.x, strokePoints[0].y + (radius * 2 * firstPointRelDiff.y) * firstPointDiffSign.y);
		// We create both sides of the strokes at once, but we have two draw the line per side, not per point
		// So we first connect even points then odd points
		for (int i = 0; i < strokePoints.size(); i++) {
			if (i % 2 == 0) {
				path.curveTo(strokePoints[i].x, strokePoints[i].y);
			}
		}
		// Now we need to go backwards through our other list!
		for (int i = strokePoints.size(); i > 0; i--) {
			if (i % 2 != 0) {
				path.curveTo(strokePoints[i].x, strokePoints[i].y);
			}
		}
		// Create the last point depending on the rel difference the last strokePoint has
		// This is to make a more rounded brush-like end
		path.curveTo(strokePoints[strokePoints.size() - 1].x + (radius * 5 * lastPointRelDiff.x) * lastPointDiffSign.x, strokePoints[strokePoints.size() - 1].y + (radius * 5 * lastPointRelDiff.y) * lastPointDiffSign.y);
		path.close();
	}
}

void Stroke::addStrokePoint(int x, int y) {
	// float circle_x;
	// float circle_y;
	// int n = 10;
	// const glm::vec2 center{ mouseX, mouseY };
	/* path.moveTo(center.x, center.y + radius);
	path.curveTo(center.x, center.y + radius);
	for (int i = 0; i < n; i++)
	{
		circle_x = radius * sin((2 * PI * i) / n) + center.x;
		circle_y = radius * cos((2 * PI * i) / n) + center.y;
		path.curveTo(circle_x, circle_y);
	}
	circle_x = radius * sin((2 * PI * 0) / n) + center.x;
	circle_y = radius * cos((2 * PI * 0) / n) + center.y;
	path.curveTo(circle_x, circle_y);
	path.curveTo(center.x, center.y + radius);
	path.close(); */

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
	else {
		previousPoint = { x, y };
	}
}

void Stroke::draw() {
	path.draw();
}