#include "ofApp.h"

#define MESH_RESOLUTION_X 320.f
#define MESH_RESOLUTION_Y 180.f

#define ORIGINAL_WIDTH 320
#define ORIGINAL_HEIGHT 240

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    
    Settings::load("settings.xml");
    mainMovieManager.setup(Settings::mainFileNames, Settings::mainFileOrder, Settings::mainZimaFileName);
    mainFbo.allocate(ORIGINAL_WIDTH, ORIGINAL_HEIGHT, GL_RGB);
    mainMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for(int i=0; i<MESH_RESOLUTION_X; ++i){
        for (int j=0; j<MESH_RESOLUTION_Y; ++j) {
            float ratio_x = i/MESH_RESOLUTION_X;
            float ratio_y = j/MESH_RESOLUTION_Y;
            float ratio_x_next = (i+1)/MESH_RESOLUTION_X;
            float ratio_y_next = (j+1)/MESH_RESOLUTION_Y;
            
            mainMesh.addTexCoord(originalMeshVertex(i,j));
            mainMesh.addVertex(mainRectMeshVertex(i,j));
            
            mainMesh.addTexCoord(originalMeshVertex(i+1,j));
            mainMesh.addVertex(mainRectMeshVertex(i+1,j));
            
            mainMesh.addTexCoord(originalMeshVertex(i,j+1));
            mainMesh.addVertex(mainRectMeshVertex(i,j+1));
            
            mainMesh.addTexCoord(originalMeshVertex(i+1,j+1));
            mainMesh.addVertex(mainRectMeshVertex(i+1,j+1));
        }
    }
    
    mainFbo.setUseTexture(true);
    
    
    subMovieManager.setup(Settings::subFileNames, Settings::subFileOrder, Settings::subZimaFileName);
    subFbo.allocate(ORIGINAL_WIDTH, ORIGINAL_HEIGHT, GL_RGB);
    
    subMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for(int i=0; i<MESH_RESOLUTION_X; ++i){
        for (int j=0; j<MESH_RESOLUTION_Y; ++j) {
            float ratio_x = i/MESH_RESOLUTION_X;
            float ratio_y = j/MESH_RESOLUTION_Y;
            float ratio_x_next = (i+1)/MESH_RESOLUTION_X;
            float ratio_y_next = (j+1)/MESH_RESOLUTION_Y;
            
            subMesh.addTexCoord(originalMeshVertex(i,j));
            subMesh.addVertex(subRectMeshVertex(i,j));
            
            subMesh.addTexCoord(originalMeshVertex(i+1,j));
            subMesh.addVertex(subRectMeshVertex(i+1,j));
            
            subMesh.addTexCoord(originalMeshVertex(i,j+1));
            subMesh.addVertex(subRectMeshVertex(i,j+1));
            
            subMesh.addTexCoord(originalMeshVertex(i+1,j+1));
            subMesh.addVertex(subRectMeshVertex(i+1,j+1));
        }
    }
    
    subFbo.setUseTexture(true);
    
    cout << "mainZima" << Settings::mainZimaFileName << endl << "subZima:" << Settings::subZimaFileName << endl;
}

ofPoint ofApp::originalMeshVertex(int x, int y){
    return ofPoint(x/MESH_RESOLUTION_X*ORIGINAL_WIDTH, y/MESH_RESOLUTION_Y*ORIGINAL_HEIGHT);
}

ofPoint ofApp::mainRectMeshVertex(int x, int y){
    float ratio_x = x/MESH_RESOLUTION_X;
    float ratio_y = y/MESH_RESOLUTION_Y;
    
    ofPoint b = Settings::mainRectVertices[1] - Settings::mainRectVertices[0];
    ofPoint c = Settings::mainRectVertices[2] - Settings::mainRectVertices[0];
    ofPoint d = Settings::mainRectVertices[3] - Settings::mainRectVertices[0];
    
    return Settings::mainRectVertices[0] + ratio_x*(1-ratio_y)*b + ratio_x*ratio_y*c + (1-ratio_x)*ratio_y*d;
}

ofPoint ofApp::subRectMeshVertex(int x, int y){
    float ratio_x = x/MESH_RESOLUTION_X;
    float ratio_y = y/MESH_RESOLUTION_Y;
    
    ofPoint b = Settings::subRectVertices[1] - Settings::subRectVertices[0];
    ofPoint c = Settings::subRectVertices[2] - Settings::subRectVertices[0];
    ofPoint d = Settings::subRectVertices[3] - Settings::subRectVertices[0];
    
    return Settings::subRectVertices[0] + ratio_x*(1-ratio_y)*b + ratio_x*ratio_y*c + (1-ratio_x)*ratio_y*d;
}

//--------------------------------------------------------------
void ofApp::update(){
    if(ofGetFrameNum() % 500 == 0){
        mainMovieManager.startZima();
        subMovieManager.startZima();
    }
    
    mainMovieManager.update();
    subMovieManager.update();
    
    mainFbo.begin();
    mainMovieManager.draw();
    mainFbo.end();
    
    subFbo.begin();
    subMovieManager.draw();
    subFbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    mainFbo.getTexture().bind();
    mainMesh.draw();
    mainFbo.getTexture().unbind();
    
    subFbo.getTexture().bind();
    subMesh.draw();
    subFbo.getTexture().unbind();
    
    stringstream ss;
    ss << "FPS:" << ofGetFrameRate() << endl;
    ofDrawBitmapString(ss.str(), 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    mainMovieManager.startZima();
    subMovieManager.startZima();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
