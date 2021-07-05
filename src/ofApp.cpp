#include "ofApp.h"
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
	opa = Painter("Heinrich");
	oma = Painter("Christel");

	canvas01.allocate(opa.width, opa.height, GL_RGBA);
	canvas02.allocate(oma.width, oma.height, GL_RGBA);

	canvas01.begin();
	ofClear(0, 0, 0, 0);
	canvas01.end();

	canvas02.begin();
	ofClear(0, 0, 0, 0);
	canvas02.end();

	// Behaviour
	opa.start();
	oma.start();
}

//--------------------------------------------------------------
void ofApp::update(){
	// Behaviour
	opa.update();
	opa.paint();
	oma.update();
	oma.paint();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0, 0, 0, 255);
	// brush.drawStrokes();
	canvas01.begin();
	ofClear(0, 0, 0, 0);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	ofBackground(255, 255, 255, 255);
	opa.showCanvas();
	canvas01.end();

	canvas02.begin();
	ofClear(0, 0, 0, 0);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	ofBackground(255, 255, 255, 255);
	oma.showCanvas();
	canvas02.end();


	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	canvas01.draw(25, 25);
	canvas02.draw(opa.width + 50, 25);
	
	ofEnableAlphaBlending();

	ofSetColor(255, 255, 255,255);
	std::string OpaStr = "Heinrich Hillebrand";
	ofDrawBitmapString(OpaStr, 240, 940);
	std::string OmaStr = "Christel Hillebrand";
	ofDrawBitmapString(OmaStr, 890, 940);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}