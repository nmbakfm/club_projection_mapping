#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetVerticalSync(false);
    ofSetFrameRate(30);
    
    
    ofLogToFile(LOG_FILENAME);
    Settings::load(SETTINGS_XML_FILENAME);
    
    movieWidth = Settings::movieWidth;
    movieHeight = Settings::movieHeight;
    
    movieManager.setup(Settings::fileNames, Settings::fileOrder, Settings::zimaFileName);
    
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
    
#if CALIBRATION
    if(bReload){
        Settings::load(SETTINGS_XML_FILENAME);
        bReload = false;
    }
#endif
    if(Settings::bMainScreen){
        int test = ofGetFrameNum();
        cout << 60*1*30 << endl;
        cout << ofGetFrameNum() % (60*1*30) << endl;
        if(ofGetFrameNum() % (60*1*30) == 60*1*30-1){
            movieManager.startZima();
        }
    }
    
    movieManager.update();
    
    fbo.begin();
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

