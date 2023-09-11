#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
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
    
        ofEasyCam camera;
        ofLight spotlight;
    
        ofxFloatSlider radius;
        ofxColorSlider color;
        ofxVec2Slider center;
        ofxIntSlider circleResolution;
        ofxToggle filled;
        ofxToggle sneed;
        ofxLabel sneed1;
        ofxLabel sneed2;
        ofxButton twoCircles;
        ofxButton ringButton;
        ofxLabel screenSize;
        ofxLabel label;

        ofxPanel gui;

        ofSoundPlayer ring;
        bool bHide;

        class Mesh{
            public:
                std::vector<glm::vec3> vertList;
                std::vector<glm::vec3> triangleInd;
            
                void addVert(double x, double y, double z);
                void addTriangle(int i1, int i2, int i3);
                void readFile();
                void outputVertVector();
                void outputTriangleVector();
            
            
        };
        Mesh triangle;
    
};
