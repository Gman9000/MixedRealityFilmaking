#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:

		//gui stuff
		ofxPanel gui;
		ofParameter<ofColor> lineColor;
		ofParameter<int> numberOfPoints;
		ofParameter<bool> timeToChangePoints;
		ofParameter<bool> variation1;
		ofParameter<bool> variation2;
		ofParameter<bool> variation3;
		ofParameter<bool> variation4;
		ofParameter<bool> variation5;
		ofParameter<bool> variation6;
		ofParameter<bool> toggleColorChange;
		ofParameter<string> screenShot;
		bool isDrawingGui;

		//lerping stuff
		//float threshold;
		//bool lerpTowardsOrigin;

		// window stuff
		int window_width;
		int window_height;

		//line stuff
		vector<ofVec2f*> points;
		ofVec2f origin;

		//points checking
		int currentNumberOfPoints;

		//angle stuff
		float startAngle = 0;
		float angleVar = 0.1;

		//color stuff
		bool gotCurrentColorAlready;
		bool gotChangingColorAlready;
		ofColor color;
		float hue;
		float hueModifier;

		//y boundary stuff
		bool isIncreasingY;
		float normalY;
		float normalYModifier;

		//x boundary stuff
		bool isIncreasingX;
		float normalX;
		float normalXModifier;

		float distanceBetweenTwoPoints(float x, float y, float a, float b);


		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
