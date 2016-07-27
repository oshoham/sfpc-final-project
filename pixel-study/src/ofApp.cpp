#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(ofGetWidth(), ofGetHeight());
    currentApp = &mosaicApp;
    currentApp->setup(grabber);
    
    mode = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    currentApp->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentApp->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        currentApp->cleanup();
        currentApp = &flowApp;
        currentApp->setup(grabber);
    } else if (key == '2') {
        currentApp->cleanup();
        currentApp = &mosaicApp;
        currentApp->setup(grabber);
    } else if (key == '3') {
        currentApp->cleanup();
        currentApp = &waveApp;
        currentApp->setup(grabber);
    } else if (key == '4') {
        currentApp->cleanup();
        currentApp = &vorApp;
        currentApp->setup(grabber);
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
