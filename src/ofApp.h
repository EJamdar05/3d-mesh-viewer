#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
        //methods for OpenFrameworks
		void setup(); //initilization
		void draw(); //draw at every frame
		void keyPressed(int key); //key press handling
        void loadModel(); //loadModel will reset data attr and load new model
    
        ofEasyCam camera; //camera for the scene
        ofParameter<string> pathField; //holds path to file
    
        //GUI elements
        ofxIntSlider triangleSlider; //slider to show shared verticies
        ofxButton submit; //submit button for loading a new model
        ofxToggle toggleWireframe; //wireframe toggle
        ofxLabel triangleField; //shows total triangle count from model
        ofxLabel verticiesField; //shows total verticies from model
        ofxLabel adjacentTitle; //title seperator
        ofxLabel size; //shows total size of the model
        ofxPanel gui; //gui panel

        bool bHide; //toggle for hiding gui
        bool toggleSubmit; //deprecated
        bool initLoad = false; //redundant

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
