#include "ofApp.h"
ofImage screenshottedImage;
float angle = 0;
//--------------------------------------------------------------
void ofApp::setup(){
	//lerp stuff
	//threshold = 400;
	//lerpTowardsOrigin = true;
	//background stuff
	ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);

	//Frame Rate Stuff
	ofSetFrameRate(30);

	//screen size
	window_width = 1000;
	window_height = 1000;
	ofSetWindowShape(window_width, window_height);

	//gui stuff
	isDrawingGui = true;
	gui.setup("X->hide|S->screenshot");
	gui.add(lineColor.set("Line Color", ofColor(0, 255, 255), ofColor(0), ofColor(255)));
	gui.add(numberOfPoints.set("number of points", 100, 100, 200));
	gui.add(timeToChangePoints.set("Toggle Points", false));
	gui.add(variation1.set("Variation 1", true));
	gui.add(variation2.set("Variation 2", false));
	gui.add(variation3.set("Variation 3", false));
	gui.add(variation4.set("Variation 4", false));
	gui.add(variation5.set("Variation 5", false));
	gui.add(variation6.set("Variation 6", false));
	gui.add(toggleColorChange.set("Toggle Changing Colors", false));
	gui.add(screenShot.set("Screenshot"));

	//point stuff
	origin = ofVec2f(window_width, window_height);
	for (int i = 0; i < numberOfPoints; i++) {
		int randomX = ofRandom(0, window_width);
		int randomY = ofRandom(0, window_height);
		points.push_back(new ofVec2f(randomX, randomY));
	}
	currentNumberOfPoints = numberOfPoints;
	//color stuff
	gotCurrentColorAlready = false;
	gotChangingColorAlready = false;
	color = lineColor;
	hue = 0;
	hueModifier = 0.1f;

	//y boundary stuff
	isIncreasingY = true;
	normalY = 0;
	normalYModifier = 0.075f;

	//x boundary stuff
	isIncreasingX = true;
	normalX = 0;
	normalXModifier = 0.075f;
}

//--------------------------------------------------------------
void ofApp::update(){
	startAngle += 0.015;
	angle = startAngle;

	if (toggleColorChange) {
		if (!gotCurrentColorAlready) {
			color = lineColor;
			hue = color.getHue();
			gotCurrentColorAlready = true;
			gotChangingColorAlready = false;
		}
		hue += hueModifier;
		if (hue >= 255) {
			hue = 0;
		}
		color.setHue(hue);
	}
	else
	{
		if (!gotChangingColorAlready) {
			lineColor.set("Line Color", color, ofColor(0), ofColor(255));
			gotChangingColorAlready = true;
			gotCurrentColorAlready = false;
		}
	}

	if ((window_width != ofGetWidth()) || (window_height != ofGetHeight()) || (currentNumberOfPoints != numberOfPoints)) {
		points.clear();
		window_width = ofGetWindowWidth();
		window_height = ofGetWindowHeight();
		currentNumberOfPoints = numberOfPoints;
		for (int i = 0; i < numberOfPoints; i++) {
			int randomX = ofRandom(0, window_width);
			int randomY = ofRandom(0, window_height);
			points.push_back(new ofVec2f(randomX, randomY));
		}
	}
	if (timeToChangePoints) {
		timeToChangePoints.set("Toggle Points", false);
		points.clear();
		window_width = ofGetWindowWidth();
		window_height = ofGetWindowHeight();
		for (int i = 0; i < numberOfPoints; i++) {
			int randomX = ofRandom(0, window_width);
			int randomY = ofRandom(0, window_height);
			points.push_back(new ofVec2f(randomX, randomY));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 0, 0, 5);
	ofDrawRectangle(0, 0, window_width, window_height);
	if (isDrawingGui) {
		gui.draw();
	}
	if (toggleColorChange) {
		ofSetColor(color);
	}
	else {
		ofSetColor(lineColor);
	}
	for (vector<ofVec2f*>::iterator itr = points.begin(); itr != points.end(); ++itr) {
		float y = ofMap(sin(angle), -1, 1, 0, float(ofGetWindowHeight()));
		float x = ofMap(cos(angle), -1, 1, 0, float(ofGetWindowWidth()));
		if (variation1) {
			variation2.set("Variation 2", false);
			variation3.set("Variation 3", false);
			variation4.set("Variation 4", false);
			variation5.set("Variation 5", false);
			variation6.set("Variation 6", false);
			origin = ofVec2f(x, y);
		}
		else if (variation2) {
			variation1.set("Variation 1", false);
			variation3.set("Variation 3", false);
			variation4.set("Variation 4", false);
			variation5.set("Variation 5", false);
			variation6.set("Variation 6", false);
			origin = ofVec2f(window_width / 2, y);
		}
		else if (variation3) {
			variation1.set("Variation 1", false);
			variation2.set("Variation 2", false);
			variation4.set("Variation 4", false);
			variation5.set("Variation 5", false);
			variation6.set("Variation 6", false);
			if (isIncreasingY) {
				normalY -= normalYModifier;
				if (normalY <= 0) {
					isIncreasingY = false;
				}
			}
			else {
				normalY += normalYModifier;
				if (normalY >= window_height) {
					isIncreasingY = true;
				}
			}
			origin = ofVec2f(x, normalY);
		}
		else if (variation4) {
			variation1.set("Variation 1", false);
			variation2.set("Variation 2", false);
			variation3.set("Variation 3", false);
			variation5.set("Variation 5", false);
			variation6.set("Variation 6", false);
			if (isIncreasingX) {
				normalX += normalXModifier;
				if (normalX >= window_width) {
					isIncreasingX = false;
				}
			}
			else {
				normalX -= normalXModifier;
				if (normalX <= 0) {
					isIncreasingX = true;
				}
			}
			origin = ofVec2f(normalX, y);
		}
		else if (variation5) {
			variation1.set("Variation 1", false);
			variation2.set("Variation 2", false);
			variation3.set("Variation 3", false);
			variation4.set("Variation 4", false);
			variation6.set("Variation 6", false);
			if (isIncreasingX) {
				normalX += normalXModifier;
				if (normalX >= window_width) {
					isIncreasingX = false;
					if (round(ofRandom(0, 1))) {
						isIncreasingY = true;
					}
					else {
						isIncreasingY = false;
					}
				}
			}
			else {
				normalX -= normalXModifier;
				if (normalX <= 0) {
					isIncreasingX = true;
					if (round(ofRandom(0, 1))) {
						isIncreasingY = true;
					}
					else {
						isIncreasingY = false;
					}
				}
			}
			if (isIncreasingY) {
				normalY -= normalYModifier;
				if (normalY <= 0) {
					isIncreasingY = false;
					if (round(ofRandom(0, 1))) {
						isIncreasingX = true;
					}
					else {
						isIncreasingX = false;
					}
				}
			}
			else {
				normalY += normalYModifier;
				if (normalY >= window_height) {
					isIncreasingY = true;
					if (round(ofRandom(0, 1))) {
						isIncreasingX = true;
					}
					else {
						isIncreasingX = false;
					}
				}
			}
			origin = ofVec2f(normalX, normalY);
		}
		else if (variation6) {
			variation1.set("Variation 1", false);
			variation2.set("Variation 2", false);
			variation3.set("Variation 3", false);
			variation4.set("Variation 4", false);
			variation5.set("Variation 5", false);
			if (ofGetFrameNum() % 180 == 0) {
				if (round(ofRandom(0, 1))) {
					isIncreasingX = true;
				}
				else {
					isIncreasingX = false;
				}
				if (round(ofRandom(0, 1))) {
					isIncreasingY = true;
				}
				else {
					isIncreasingY = false;
				}
			}
			if (isIncreasingX) {
				normalX += normalXModifier;
				if (normalX >= window_width) {
					isIncreasingX = false;
					/*if (round(ofRandom(0, 1))) {
						isIncreasingY = true;
					}
					else {
						isIncreasingY = false;
					}*/
				}
			}
			else {
				normalX -= normalXModifier;
				if (normalX <= 0) {
					isIncreasingX = true;
					/*if (round(ofRandom(0, 1))) {
						isIncreasingY = true;
					}
					else {
						isIncreasingY = false;
					}*/
				}
			}
			if (isIncreasingY) {
				normalY -= normalYModifier;
				if (normalY <= 0) {
					isIncreasingY = false;
				}
			}
			else {
				normalY += normalYModifier;
				if (normalY >= window_height) {
					isIncreasingY = true;
				}
			}
			origin = ofVec2f(normalX, normalY);
			(**itr).set(ofLerp((**itr).x, origin.x, 0.005), (**itr).y);
		}
		ofDrawLine((**itr), origin);
		angle += angleVar;
	}
	if (variation6) {
		ofSetColor(0, 0, 0, 20);
		ofDrawRectangle(0, 0, window_width, window_height);
	}
}

float ofApp::distanceBetweenTwoPoints(float x, float y, float a, float b) {
	return sqrt(pow(x - a, 2) + pow(y - b, 2));
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'x') {
		isDrawingGui = !isDrawingGui;
	}
	else if (key == 's') {
		screenshottedImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshottedImage.save(screenShot.toString() + ".png");
		screenShot.set("Screenshot Saved!");
	}
	//this is for clearing the screen purposes (developer functionality only)
	else if (key == 'f') {
		ofSetColor(0, 0, 0);
		ofDrawRectangle(0, 0, window_width, window_height);
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
