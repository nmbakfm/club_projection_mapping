#include "ofApp.h"
#include "SoundReactiveDataSetManager.hpp"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    ofHideCursor();
    
    ofLogToFile(LOG_FILENAME);
    
    Settings::load(SETTINGS_XML_FILENAME);
    
    movieWidth = Settings::movieWidth;
    movieHeight = Settings::movieHeight;
    
    movieManager.setup();
    
    fbo.allocate(movieWidth, movieHeight, GL_RGB);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for(int i=0; i<MESH_RESOLUTION_X; ++i){
        for (int j=0; j<MESH_RESOLUTION_Y; ++j) {
            float ratio_x = i/MESH_RESOLUTION_X;
            float ratio_y = j/MESH_RESOLUTION_Y;
            float ratio_x_next = (i+1)/MESH_RESOLUTION_X;
            float ratio_y_next = (j+1)/MESH_RESOLUTION_Y;
            
            mesh.addTexCoord(originalMeshVertex(i,j));
            mesh.addVertex(rectMeshVertex(i,j));
            
            mesh.addTexCoord(originalMeshVertex(i+1,j));
            mesh.addVertex(rectMeshVertex(i+1,j));
            
            mesh.addTexCoord(originalMeshVertex(i,j+1));
            mesh.addVertex(rectMeshVertex(i,j+1));
            
            mesh.addTexCoord(originalMeshVertex(i+1,j+1));
            mesh.addVertex(rectMeshVertex(i+1,j+1));
        }
    }
    
    fbo.setUseTexture(true);
    
    zimaInterval = Settings::zimaInterval;
    
    ofSetFullscreen(false);
    if(Settings::bMainScreen){
        ofSetWindowPosition(0, 0);
    }else{
        ofSetWindowPosition(1200, 0);
    }
    //ofSetFullscreen(true);
    //TODO:戻す
    
    for(auto data : Settings::movieData){
        if(data->getMovieType() == MovieType::MovieTypeSoundReactive){
            SoundRactiveDataManager::addPath(data->getFilePath());
        }
    }
    
    
    int bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}

ofPoint ofApp::originalMeshVertex(int x, int y){
    return ofPoint(x/MESH_RESOLUTION_X*ORIGINAL_WIDTH, y/MESH_RESOLUTION_Y*ORIGINAL_HEIGHT);
}

ofPoint ofApp::rectMeshVertex(int x, int y){
    float ratio_x = x/MESH_RESOLUTION_X;
    float ratio_y = y/MESH_RESOLUTION_Y;
    
    ofPoint b = Settings::rectVertices[1] - Settings::rectVertices[0];
    ofPoint c = Settings::rectVertices[2] - Settings::rectVertices[0];
    ofPoint d = Settings::rectVertices[3] - Settings::rectVertices[0];
    
    return Settings::rectVertices[0] + ratio_x*(1-ratio_y)*b + ratio_x*ratio_y*c + (1-ratio_x)*ratio_y*d;
}
//--------------------------------------------------------------
void ofApp::update(){
    
    movieManager.setCurrendVolume(smoothedVol);
    
#if CALIBRATION
    if(bReload){
        Settings::load(SETTINGS_XML_FILENAME);
        bReload = false;
    }
#endif
    if(Settings::bMainScreen){
        if(isFirstTime && ofGetFrameNum() % zimaInterval == zimaInterval-1){
            isFirstTime = false;
            movieManager.startZima();
        }
    }
    
    SoundRactiveDataManager::loadData();
    movieManager.update();
    
    fbo.begin();
    ofBackground(0);
    movieManager.draw();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.getTexture().bind();
    mesh.draw();
    fbo.getTexture().unbind();
    
    
#if DEBUG
    stringstream ss;
    ss << "FPS:" << ofGetFrameRate() << endl;
    ofDrawBitmapString(ss.str(), 20, 20);
#endif
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    Settings::soFarMaxVol = MAX(curVol, Settings::soFarMaxVol);
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    bufferCounter++;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
#if CALIBRATION
    if(key == ' '){
        bReload = true;
    }
#endif
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

