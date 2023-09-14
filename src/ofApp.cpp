#include "ofApp.h"
#include <fstream>
#include <string>
#include <iostream>
//--------------------------------------------------------------
/*
setup()
    ~Setup will load in all configurations for the 3D model viewer
 */
void ofApp::setup(){
    toggleSubmit = false;

    //helper function that reads obj file to find verticies and face data
    triangle.readFile();
    //gui setup process
    if(!initLoad){
        gui.setup();
        gui.add(toggleWireframe.setup("Wireframes (on/off)", true)); //wireframe toggle
        gui.add(verticiesField.setup("Verticies", to_string(triangle.totalVerticies))); //# verticies label
        gui.add(triangleField.setup("Faces", to_string(triangle.totalFaces))); //# faces label
        gui.add(size.setup("Total Size", to_string(triangle.totalSize)+"KB")); //total size of model in KB
        gui.add(adjacentTitle.setup("Find Adjacent Triangles", "")); //adjacent triangle label
        gui.add(triangleSlider.setup("Triangle", 0, 1, triangle.totalFaces)); //slider to show shared verticies based off triangle index
        gui.add(pathField.set("Load file (.obj)", "")); //path field (string input)
        gui.add(submit.setup("Load Model")); //load model button
        ofSetBackgroundColor(ofColor::black); //gui background
        //snap camera closer to object
        camera.setDistance(10); //distance set
        camera.setNearClip(.1); //snap camera
        initLoad = true;
    }
    //event driven listener connected to button (loads new model)
    submit.addListener(this,&ofApp::loadModel);
    //controls gui display (on or off)
    bHide = false;

}

//--------------------------------------------------------------
void ofApp::update(){

}

/*/
 loadModel()
    ~Loads a new model by clearing the vertList and triangleIndexes
    ~resets size of model to 0
    ~sets the new path
    ~readsFile
    ~draws model
 */
void ofApp::loadModel(){
    triangle.vertList.clear();
    triangle.triangleInd.clear();
    triangle.totalSize = 0;
    triangle.pathToFile = pathField;
    triangle.readFile();
    draw();
}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.begin();
    

    //grid setup
    ofPushMatrix();
    ofSetBackgroundColor(ofColor::grey);
    ofSetColor(ofColor::dimGray);
    ofRotateDeg(90);
    ofDrawGridPlane();
    ofPopMatrix();
    
    
    ofSetColor(ofColor::white);
    
    //triangleList and verticiesList will hold a copy of the triangleInd and vertList from Mesh class
    vector<glm::vec3> triangleList = triangle.triangleInd;
    vector<glm::vec3> verticiesList = triangle.vertList;
    //loop through the triangleList and draw triangle
    for(int i = 0 ; i < triangleList.size() ; i++){
        ofSetColor(ofColor::green); //draw triangle in green
        //draw mesh by calling verticiesList and constructing each triangle by the index of
        //triangleList at x,y,z
        ofDrawTriangle(verticiesList[triangleList[i].x], verticiesList[triangleList[i].y], verticiesList[triangleList[i].z]);

    }
    //find adjacent points by triangleSlider having a value inside of it
    if(triangleSlider){
        ofNoFill();
        ofSetColor(ofColor::red); //set the color of the selected triangle as red
        ofDrawTriangle(verticiesList[triangleList[triangleSlider].x], verticiesList[triangleList[triangleSlider].y], verticiesList[triangleList[triangleSlider].z]); //draw the first triangle based off triangleSlider value
        for(int i = 0 ; i < triangle.triangleInd.size(); i++){
            //draw the points based off a shared verticies value
            if(verticiesList[triangleList[triangleSlider].x] == verticiesList[triangleList[i].x] ||
               verticiesList[triangleList[triangleSlider].y] == verticiesList[triangleList[i].y] ||
               verticiesList[triangleList[triangleSlider].x] == verticiesList[triangleList[i].x]
               ){
                ofSetColor(ofColor::black); //draw adjacent triangles as black
                ofDrawTriangle(verticiesList[triangleList[i].x], verticiesList[triangleList[i].y], verticiesList[triangleList[i].z]); //draw triangle
            }
        }
    }
    
    //toggle wireframe mode
    if(toggleWireframe){
        ofNoFill();
    }else{
        ofFill();
    }
    camera.end();
    if(!bHide){
        gui.draw();
    }
    
    ofSetColor(ofColor::green);
    //let user know what model was loaded 
    ofDrawBitmapString("Loaded: "+triangle.pathToFile, 10, 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout<<key<<endl;
    switch(key){
        case 't': //wireframe
            ofNoFill();
            break;
        case 'r': //fill shape
            ofFill();
            break;
        case 'h': //hide gui
            bHide = !bHide;
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

/**
    addVert()
        takes in 3 double values of verticies and apends them to verticiesList as a vec3
*/
void ofApp::Mesh::addVert(double x, double y, double z){
    glm::vec3 v(x,y,z);
    vertList.push_back(v);
}
/**
    addVert()
        takes in 3 int values of index of triangles and apends them to triangleInd as a vec3
*/
void ofApp::Mesh::addTriangle(int x, int y, int z){
    glm::vec3 v(x-1,y-1,z-1); //subtract index by 1 due to obj not being zero indexed
    triangleInd.push_back(v);
}

void ofApp::Mesh::readFile(){
    int total = 0; //total size in KB
    ofBuffer buffer = ofBufferFromFile(pathToFile); //readfile from path string
    for(auto line : buffer.getLines()){ //loop through file
        vector<string> token = ofSplitString(line, " "); //split the line by space delimiter
        if(token[0] == "v"){ //if verticies identified
            addVert(stof(token[1]), stof(token[2]), stof(token[3])); //add vert
            totalVerticies++; //append to totalVerticies
        }else if (token[0] == "f"){ //if faces identified
            totalFaces+=1; //add to totalfaces
            addTriangle(stoi(token[1]), stoi(token[2]), stoi(token[3])); //conver string to int
        }
            
    }
    //size of verticies and faces in kb added and assigned to totalSize
    total = sizeof(int) * totalVerticies;
    total += sizeof(int) * totalFaces;
    totalSize = total;
    
}


