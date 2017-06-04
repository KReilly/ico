#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //x,y,z,w,p,r;
    //numPlacement = 0.0; //vales = 0,10.00, 1.00, 0.10, 0.01
    //numBuilding = 0.0;
    //ofPoint xyz, ypr;

    for(int i=0; i<12; i++){
        touchPoints.push_back(false);
    }
    
    for(int i=0; i<12; i++){
        emitter.push_back(*new ofPoint((i+1)*ofGetWindowWidth()/14.0, ofGetWindowHeight()/2.0));
    }
  
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    ofSetColor(255,0,0);
    ofFill();

    
    for(int i=0; i<touchPoints.size(); i++){
        //cout<<emitter[i].x<<", "<<emitter[i].y<<endl;
        
        ofSetColor(255,0,0);
        ofFill();
        ofDrawCircle(emitter[i], 5.0);
        if(touchPoints[i]){
            ofSetColor(255,0,0);
            ofFill();
            ofDrawCircle(emitter[i], 10.0);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
            //touchpoints
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
                cout<<"Touchpoint = "<<key-'a'<<endl;
                touchPoints[key-'a'] = true;
                break;
            case 'o':
                for(int i=0; i<touchPoints.size(); i++){
                    touchPoints[i] = false;
                }
                break;
/*
            case 'x':   //x acc
            case 'y':   //y acc
            case 'z':   //z acc
            case 'w':   //yaw acc
            case 'p':   //pitch acc
            case 'r':   //roll acc
            
            case 'n':   //new transmission
                for(int i=0; i<touchPoints.size(); i++){
                    touchPoints[i] = false;
                }
                break;
  */
            default:
                cout<<"Error on input. Value = "<<key<<endl;
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
