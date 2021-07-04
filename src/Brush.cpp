#pragma once

#include "Brush.h"

Brush::Brush() {
	size = 20;
	hairs = 10;
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
			strokes[i].update();
		}
	}
}

void Brush::paint(int x, int y) {
	if (strokes.size() > 0) {
		for (int i = 0; i < strokes.size(); i++) {
			strokes[i].addStrokePoint(x, y);
		}
	}
}
 
void  Brush::drawStrokes() {
	if (strokes.size() > 0) {
		for (int i = 0; i < strokes.size(); i++) {
			strokes[i].draw();
		}
	}
}

void Brush::addStroke() {
	strokes.push_back(Stroke());
}
void  Brush::cleanStroke() {
	
}

void Brush::applyForce(glm::vec2 force) {
	acceleration += force;
}

void Brush::seek(glm::vec2 target) {
	glm::vec2 desired = target - location;
	desired = glm::normalize(desired);
	float distance = glm::distance(location, target);
	if (distance < slowDownThreshhold) {
		desired *= ofMap(distance, 0, slowDownThreshhold, 0, maxSpeed);
	}
	else {
		desired *= maxSpeed;
	}
	desired += (ofNoise(location) * 2 - 1) * noiseInfluence;
	glm::vec2 steer = desired - velocity;
	cout << (ofNoise(location) * 2 - 1) * noiseInfluence << endl;
	// Limit
	if (glm::length(steer) > maxForce) {
		steer = glm::normalize(steer) * maxForce;
	}
	applyForce(steer);
}

bool Brush::targetHit() {
	if (glm::distance(location, target) < hitRadius) {
		return true;
	}
	return false;
}

void Brush::setupAgent() {
	acceleration = { 0, 0 };
	velocity = { 0, 0 };
	location = { 10, 50 };
	target = { 500, 500 };
	maxSpeed = 6;
	maxForce = 0.5;
	slowDownThreshhold = 100;
	noiseInfluence = 1;
	hitRadius = 5.0;
}

void Brush::updateAgent() {
	seek(target);
	velocity += acceleration;
	// Limit
	if (glm::length(velocity) > maxSpeed) {
		velocity = glm::normalize(velocity) * maxSpeed;
	}
	location += velocity;
	acceleration *= 0;
	if (targetHit()) {
		location = { ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()) };
		target = { ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()) };
		velocity = { ofRandom(0, 50) - 25, ofRandom(0, 50) - 25 };
	}

	maxSpeed = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 10);
	maxForce = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 2);
}

void Brush::drawAgent() {
	ofSetColor(0, 0, 255);
	ofFill();
	ofDrawCircle(location, 10);
	ofSetColor(0, 255, 0);
	ofFill();
	ofDrawCircle(target, 10);
	ofSetColor(120, 255, 100);
	std::string speedStr = "MaxSpeed = ";
	speedStr += ofToString(maxSpeed);
	ofDrawBitmapString(speedStr, 10, 25);
	std::string forceStr = "MaxForce = ";
	forceStr += ofToString(maxForce);
	ofDrawBitmapString(forceStr, 10, 50);
	std::string thresholdStr = "SlowDownThreshhold = ";
	thresholdStr += ofToString(slowDownThreshhold);
	ofDrawBitmapString(thresholdStr, 10, 75);
	std::string noiseInfluenceStr = "NoiseInfluence = ";
	noiseInfluenceStr += ofToString(noiseInfluence);
	ofDrawBitmapString(noiseInfluenceStr, 10, 100);
	std::string hitRadiusStr = "HitRadius = ";
	hitRadiusStr += ofToString(hitRadius);
	ofDrawBitmapString(hitRadiusStr, 10, 125);
}