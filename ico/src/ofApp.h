#pragma once

#include "ofMain.h"

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
    
        vector <ofPoint> emitter;
        ofMesh mesh;
    
        vector <bool> touchPoints;
    private:
        float x,y,z,w,p,r;
        float numPlacement; //vales = 0,10.00, 1.00, 0.10, 0.01
        float numBuilding;
        ofPoint xyz, ypr;
};
