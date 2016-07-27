#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(ofGetWidth(), ofGetHeight());
    currentApp = &flowApp;
    currentApp->setup(grabber);
    
    mode.addListener(this, &ofApp::modeChanged);
    mode = 0;
    
    params.add(potentiometer1.set("potentiometer1", 5, 0, 100));
    params.add(potentiometer2.set("potentiometer2", 5, 0, 100));
    panel.setup(params);
}

void ofApp::modeChanged(int & value) {
    currentApp->cleanup();

    if (mode == 0) {
        currentApp = &flowApp;
    } else if (mode == 1) {
        currentApp = &mosaicApp;
    } else if (mode == 2) {
        currentApp = &waveApp;
    } else if (mode == 3) {
        currentApp = &vorApp;
    }
    
    currentApp->setup(grabber);
}

//--------------------------------------------------------------
void ofApp::update(){
    currentApp->update(potentiometer1, potentiometer2);
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentApp->draw();
    panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        mode = (mode + 1) % 4;
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
