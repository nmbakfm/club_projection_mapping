#pragma once

#include "ofMain.h"
#include "Constant.h"
#include "Settings.h"
#include "MovieManager.h"

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    bool bReload;
    
    MovieManager movieManager;
//    ofFbo fbo;
//    ofMesh mesh;
    
    ofShader shader;
    
    ofPoint originalMeshVertex(int x, int y);
    ofPoint rectMeshVertex(int x, int y);
    
    int movieWidth, movieHeight;
    
    int zimaInterval;
		
};
