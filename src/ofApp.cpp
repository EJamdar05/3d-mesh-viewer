#include "ofApp.h"
#include <fstream>
#include <string>
#include <iostream>
//--------------------------------------------------------------
void ofApp::setup(){

    gui.setup(); // most of the time you don't need a name
    gui.add(label.setup("","Control Panel"));
    gui.add(filled.setup("Wireframes", false));
    gui.add(sneed.setup("Solid Color", true));
    gui.add(sneed1.setup("Number of Faces: ", "200"));
    gui.add(sneed2.setup("Number of Verticies", "400"));
    bHide = false;
    
    ofSetBackgroundColor(ofColor::black);
    camera.setDistance(10);
    camera.setNearClip(.1);


    triangle.readFile();
    

    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    camera.begin();
    
    //grid
    ofPushMatrix();
    ofSetBackgroundColor(ofColor::grey);
    ofSetColor(ofColor::dimGray);
    ofRotateDeg(90);
    ofDrawGridPlane();
    ofPopMatrix();
    ofSetColor(ofColor::white);

    for(int i = 0 ; i < triangle.triangleInd.size() ; i++){
        ofSetColor(ofColor::green);
        ofDrawTriangle(triangle.vertList[triangle.triangleInd[i].x], triangle.vertList[triangle.triangleInd[i].y], triangle.vertList[triangle.triangleInd[i].z]);

    }
    
//    ofNoFill();
    
    camera.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 't':
            ofNoFill();
            break;
        case 'r':
            ofFill();

            break;
        default:
            cout<<"Not recognized input"<<endl;
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

void ofApp::Mesh::addVert(double x, double y, double z){
    glm::vec3 v(x,y,z);
    vertList.push_back(v);
}

void ofApp::Mesh::addTriangle(int x, int y, int z){
    glm::vec3 v(x-1,y-1,z-1);
    triangleInd.push_back(v);
}

void ofApp::Mesh::readFile(){
    ofBuffer buffer = ofBufferFromFile("/Users/eshaqjamdar/Downloads/61ftqcfe3d34-knife/knife.obj");
    for(auto line : buffer.getLines()){
        vector<string> token = ofSplitString(line, " ");
        if(token[0] == "v"){
            addVert(stof(token[1]), stof(token[2]), stof(token[3]));
        }else if (token[0] == "f"){
            addTriangle(stoi(token[1]), stoi(token[2]), stoi(token[3]));
        }
            
    }
}

//void ofApp::Mesh::readFile(){
//    std::ifstream modelFile;
//    string line;
//    Boolean isVert = false;
//    Boolean isInd = false;
//    double values[3];
//    int totalRead = 0;
//    string letterF = "f";
//
//    modelFile.open("/Users/eshaqjamdar/Documents/Open Frameworks/of_v0.11.2_osx_release/apps/myApps/3DMeshViewer/bin/data/geo/teapot.obj");
//
//    if(modelFile){
//        while(getline(modelFile, line, ' ')){
//            if(line == "v"){
//                continue;
//            }else if (line.find(letterF) != std::string::npos){
//                isInd = true;
//                continue;
//            }else{
//                values[totalRead] = stof(line);
//                totalRead++;
//                if(totalRead == 3){
//                    if(isInd){
//                        addTriangle(values[0] - 1, values[1] - 1, values[2] - 1);
//                    }else{
//                        addVert(values[0], values[1], values[2]);
//                    }
//                    isVert = false;
//                    totalRead = 0;
//                }
//            }
//        }
//
//        for(int i = 0 ; i < triangleInd.size() ; i++){
//            cout<<triangleInd[i]<<endl;
//        }
//
//    }else{
//        cout<<"Error: Could not load model file"<<endl;
//    }
//}

