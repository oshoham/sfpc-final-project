#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(ofGetWidth(), ofGetHeight());
    currentApp = &flowApp;
    currentApp->setup(&grabber);
    
    mode.addListener(this, &ofApp::modeChanged);
    mode = 0;
    
    params.add(potentiometer1.set("potentiometer1", 0, 0, 1023));
    params.add(potentiometer2.set("potentiometer2", 0, 0, 1023));
    panel.setup(params);
    
    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application or via command line
    // for OSX, in your terminal type "ls /dev/tty.*" to get a list of serial devices
    ard.connect("/dev/tty.usbmodem1411", 57600);
    
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    bSetupArduino = false;
    lastButtonPress = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set pins D4 and D6 to digital input
    //    ard.sendDigitalPinMode(4, ARD_INPUT);
    //    ard.sendDigitalPinMode(6, ARD_INPUT);
    
    // set pin D5 & D7 as digital output
    
    //ARD_ANALOG ?
    ard.sendAnalogPinReporting(2, ARD_ANALOG);
    ard.sendAnalogPinReporting(3, ARD_ANALOG);
    
    ard.sendDigitalPinMode(2, ARD_INPUT);
    ard.sendDigital(2, ARD_HIGH); // connect internal pull-up resistor
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    // update the arduino, get any data or messages.
    // the call to ard.update() is required
    ard.update();
    
    // do not send anything until the arduino has been set up
    if (bSetupArduino) {
    }
}

// digital pin event handler, called whenever a digital pin value has changed
// note: if an analog pin has been set as a digital pin, it will be handled
// by the digitalPinChanged function rather than the analogPinChanged function.
//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
    int buttonState = ard.getDigital(pinNum);
    float now = ofGetElapsedTimef();
    
    if (pinNum == 2 && buttonState == ARD_LOW && now - lastButtonPress > 0.5) {
        mode = (mode + 1) % 4;
        lastButtonPress = now;
    }
}

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    int val = ard.getAnalog(pinNum);
    if (pinNum == 2) {
        potentiometer1 = val;
    }
    else if (pinNum == 3) {
        potentiometer2 = val;
    }
}

//--------------------------------------------------------------
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
    
    currentApp->setup(&grabber);
}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
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
