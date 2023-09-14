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
        void loadModel();
    
        ofEasyCam camera;
        ofLight spotlight;
        ofParameter<string> pathField;
    
        ofxIntSlider triangleSlider;
        ofxVec2Slider center;
        ofxToggle filled;
        ofxButton submit;
        ofxToggle toggleWireframe;
        ofxLabel triangleField;
        ofxLabel verticiesField;
        ofxLabel adjacentTitle;
        ofxLabel label;
        ofxLabel size;
        ofxPanel gui;

        bool bHide;
        bool toggleSubmit;
        bool initLoad = false;

        class Mesh{
            public:
                std::vector<glm::vec3> vertList;
                std::vector<glm::vec3> triangleInd;
                int totalVerticies = 0;
                int totalFaces = 0;
                int totalSize = 0;
                int dblSize = sizeof(double);
                void addVert(double x, double y, double z);
                void addTriangle(int i1, int i2, int i3);
                void readFile();
                void outputVertVector();
                void outputTriangleVector();
                string pathToFile = "/Users/eshaqjamdar/Downloads/61ftqcfe3d34-knife/knife.obj";
            
            
        };
        Mesh triangle;
    
};
