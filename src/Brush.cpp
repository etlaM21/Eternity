#pragma once

#include "Brush.h"

Brush::Brush() {
	size = 7.5;
	hairs = 25;
	maxStrokes = 100;
	strokeStyle = Stroke();
}

 Brush::Brush(float _size, int _hairs, int _maxStrokes, Stroke _strokeStyle) {
	size = _size;
	hairs = _hairs;
	maxStrokes = _maxStrokes;
	strokeStyle = _strokeStyle;
}

 //--------------------------------------------------------------

void  Brush::updateStrokes() {
	if (strokes.size() > 0) {
		for (int i = 0; i < strokes.size(); i++) {
			for (int o = 0; o < strokes[i].size(); o++) {
				strokes[i][o].update();
			}
		}
	}
}

void Brush::paint(glm::vec2 paintPos, float pressure) {
	// x = location.x;
	// y = location.y;
	float pressureSize = size * (pressure + 0.1);
	if (strokes.size() > 0) {
		if (glm::distance(paintPos, lastLocation) > 5) { // Else OF crashes because it looks for the same point in memory or something
			// 5 as threshold seems to be a good mix for a smooth looking and still fast drawing stroke
			lastLocation = paintPos;
			int n = hairs / 2 - 1;
			// Outer Circle
			for (int i = 0; i < hairs / 2; i++)
			{
				float circle_x = pressureSize * sin((2 * PI * i) / n) + paintPos.x;
				float circle_y = pressureSize * cos((2 * PI * i) / n) + paintPos.y;
				strokes[strokes.size() - 1][i].addStrokePoint(circle_x, circle_y);
			}
			// Inner Circle
			for (int i = hairs / 2; i < hairs - 1; i++)
			{
				float circle_x = pressureSize / 2 * sin((2 * PI * i) / n) + paintPos.x;
				float circle_y = pressureSize / 2 * cos((2 * PI * i) / n) + paintPos.y;
				strokes[strokes.size() - 1][i].addStrokePoint(circle_x, circle_y);
			}
			// Midpoint
			strokes[strokes.size() - 1][hairs].addStrokePoint(paintPos.x, paintPos.y);
		}
	}
}
 
void  Brush::drawStrokes() {
	if (strokes.size() > 0) {
		for (int i = 0; i < strokes.size(); i++) {
			for (int o = 0; o < strokes[i].size(); o++) {
				strokes[i][o].draw();
			}
		}
	}
}

void Brush::addStroke(ofColor strokeColor) {
	std::vector<Stroke> newStroke;
	for (int i = 0; i <= hairs; i++) {
		newStroke.push_back(Stroke(strokeStyle.radius, strokeColor, strokeStyle.fadeAwayTime, strokeStyle.driftAmount));
	}
	strokes.push_back(newStroke);
}
void  Brush::cleanStrokes() {
	if (! strokes[0][0].visible) {
		for (int i = 0; i < strokes[0].size(); i++) {
			strokes[0][i].clean();
		}
		strokes.erase(strokes.begin());
		std::cout << "Removed stroke, new size = " << strokes.size() << endl;
	}
}