#pragma once

#include "Painter.h"

Painter::Painter() {

}
Painter::Painter(string name) {
	if (name == "Christel") {
		int alpha = 150;
		palette.push_back(ofColor(241, 141, 190, alpha)); // Hellrosa
		palette.push_back(ofColor(243, 219, 108, alpha)); // Gold
		palette.push_back(ofColor(40, 33, 51, alpha)); // Ganz dunkles Lila
		palette.push_back(ofColor(62, 60, 51, alpha)); // Ganz dunkles Gelb
		palette.push_back(ofColor(40, 33, 51, alpha)); // Ganz dunkles Lila
		palette.push_back(ofColor(62, 60, 51, alpha)); // Ganz dunkles Gelb
		palette.push_back(ofColor(40, 33, 51, alpha)); // Ganz dunkles Lila
		palette.push_back(ofColor(62, 60, 51, alpha)); // Ganz dunkles Gelb
		strokeStyle = Stroke(5, palette[rand() % palette.size()], 240.0f, 0.0f);
		brush = Brush(7.5, 25, 100, strokeStyle);
		maxSpeed = 8.5f;
		maxForce = 0.4f;
		slowDownThreshhold = 30;
		noiseInfluence = 1.75f;
		hitRadius = 10;
	}
	if (name == "Heinrich") {
		int alpha = 50;
		palette.push_back(ofColor(0, 84, 22, alpha)); // Dunkelgruen
		palette.push_back(ofColor(9, 52, 13, alpha)); // Holz
		palette.push_back(ofColor(165, 176, 0, alpha)); // Hellgruen
		palette.push_back(ofColor(64, 89, 49, alpha)); // Mattgruen
		palette.push_back(ofColor(173, 97, 25, alpha)); // Herbst
		palette.push_back(ofColor(41, 93, 64, alpha)); // Blaugruen
		strokeStyle = Stroke(20.0f, palette[rand() % palette.size()], 240.0f, 0.1f);
		brush = Brush(10.0f, 21, 100, strokeStyle);
		maxSpeed = 4.1f;
		maxForce = 1.5f;
		slowDownThreshhold = 175;
		noiseInfluence = 2.0f;
		hitRadius = 40;
	}
	width = 600;
	height = 900;
	brush.addStroke(palette[rand() % palette.size()]);
}

void Painter::paint() {
	if (finishedStroke) {
		brush.addStroke(palette[rand() % palette.size()]);
	}
	else {
		brush.paint(location, ofNoise(location.x + ofGetElapsedTimef()) + 0.1);
		brush.updateStrokes();
		brush.cleanStrokes();
	}
}

void Painter::showCanvas() {
	brush.drawStrokes();
}


// BEHAVIOUR


void Painter::applyForce(glm::vec2 force) {
	acceleration += force;
}

void Painter::seek(glm::vec2 target) {
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
	// Limit
	if (glm::length(steer) > maxForce) {
		steer = glm::normalize(steer) * maxForce;
	}
	applyForce(steer);
}

bool Painter::targetHit() {
	if (glm::distance(location, target) < hitRadius) {
		return true;
	}
	return false;
}

void Painter::start() {
	acceleration = { 0, 0 };
	velocity = { ofRandom(0, 50) - 25, ofRandom(0, 50) - 25 };
	location = { ofRandom(0, width), ofRandom(0, height) };
	target = { ofRandom(0, width), ofRandom(0, height) };
	finishedStroke = false;
}

void Painter::update() {
	finishedStroke = false;
	seek(target);
	velocity += acceleration;
	// Limit
	if (glm::length(velocity) > maxSpeed) {
		velocity = glm::normalize(velocity) * maxSpeed;
	}
	location += velocity;
	acceleration *= 0;
	if (targetHit()) {
		finishedStroke = true;
		location = { ofRandom(0, width), ofRandom(0, height) };
		target = { ofRandom(0, width), ofRandom(0, height) };
		velocity = { ofRandom(0, 50) - 25, ofRandom(0, 50) - 25 };
	}

	// maxSpeed = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 10);
	// maxForce = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 2);
}

void Painter::drawAgent() {
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