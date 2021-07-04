#include "ofApp.h"
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
	brush = Brush(20.5, 10, 100, Stroke());
	brush.addStroke();
	// Agent
	brush.setupAgent();
}

//--------------------------------------------------------------
void ofApp::update(){
	brush.updateStrokes();
	// Agent
	brush.updateAgent();
}

//--------------------------------------------------------------
void ofApp::draw(){
	brush.drawStrokes();
	// Agent
	brush.drawAgent();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_UP) {
		brush.slowDownThreshhold++;
	}
	if (key == OF_KEY_DOWN) {
		brush.slowDownThreshhold--;
	}
	if (key == OF_KEY_LEFT) {
		brush.noiseInfluence = brush.noiseInfluence - 0.01;
	}
	if (key == OF_KEY_RIGHT) {
		brush.noiseInfluence = brush.noiseInfluence + 0.01;
	}
	if (key == OF_KEY_PAGE_DOWN) {
		brush.hitRadius = brush.hitRadius - 0.1;
	}
	if (key == OF_KEY_PAGE_UP) {
		brush.hitRadius = brush.hitRadius + 0.1;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	brush.paint(x, y);
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