#include "energyWaveApp.h"

//--------------------------------------------------------------
void energyWaveApp::setup(ofVideoGrabber videoGrabber){
    grabber = videoGrabber;
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    pixelStep = 10;
    pixelColors = vector<vector<ofColor>>(grabber.getWidth(), vector<ofColor>(grabber.getHeight()));
    energy = vector<vector<float>>(grabber.getWidth(), vector<float>(grabber.getHeight()));
    
    for (int i = 0; i < grabber.getWidth(); i++) {
        for (int j = 0; j < grabber.getHeight(); j++) {
            pixelColors[i][j] = ofColor::fromHsb((ofRandom(180, 360) / 360.0) * 255, (ofRandom(80, 100) / 100.0) * 255, (ofRandom(50, 90) / 100.0) * 255);
            energy[i][j] = 0;
        }
    }
    
    drawMode = 1;
}

//--------------------------------------------------------------
void energyWaveApp::update(){
    grabber.update();
    
    ofPixels pixels = grabber.getPixels();
    pixels.mirror(false, true);
    
    for (int i = 0; i < grabber.getWidth(); i+=pixelStep) {
        for (int j = 0; j < grabber.getHeight(); j+=pixelStep) {
            for (int k = 0; k < pixelStep; k++) {
                for (int l = 0; l < pixelStep; l++) {
                    energy[i+k][j+l] *= 0.99;
                    
                    // modifying this value will affect how long the afterimages last
                    // a higher value means a shorter afterimage
                    if (energy[i+k][j+l] < 0.5) {
                        energy[i+k][j+l] = 0;
                    }
                    
                    // modifying the brightness range will affect which pixels trigger afterimages
                    int brightness = pixels.getColor(i, j).getBrightness();
                    if (ofInRange(brightness, 0, 150)){
                        energy[i+k][j+l] = 1;
                    }
                }
            }
        }
    }
}

//--------------------------------------------------------------
void energyWaveApp::draw(){
    ofBackground(0);
    
    ofPixels pixels = grabber.getPixels();
    pixels.mirror(false, true);
    
    // proper way to mosaic is to average the image, but we're just gonna step by 10
    for (int i = 0; i < grabber.getWidth(); i+=pixelStep) {
        for (int j = 0; j < grabber.getHeight(); j+=pixelStep) {
            int brightness = pixels.getColor(i, j).getBrightness();
            
            // modifying pct will affect the frequency and duration of the afterimages
            float pct = sin(energy[i][j] * TWO_PI * 5) + cos(energy[i][j] * TWO_PI * 5);
            //            brightness = (int)(brightness + (brightness / 2) * pct);
            
            ofColor pixelColor = pixelColors[i][j];
            pixelColor.setBrightness(brightness);
            ofSetColor(pixelColor);
            
            brightness = (int)(brightness + (brightness) * pct);
            
            brightness = ofClamp(brightness, 0, 255);
            
            
            if (drawMode == 1) {
                ofDrawCircle(i, j, ofMap(brightness, 0, 255, 0.5, 3));
            } else if (drawMode == 2) {
                ofPushMatrix();
                ofTranslate(i, j);
                ofRotateZ(ofMap(brightness, 0, 255, 0, 180));
                ofDrawRectangle(0, 0, ofMap(brightness, 0, 255, 0, 7), 3);
                ofPopMatrix();
            } else if (drawMode == 3) {
                ofPushMatrix();
                ofTranslate(i, j);
                ofRotateZ(ofMap(brightness, 0, 255, 0, 180));
                ofDrawTriangle(0, 0, 6, 6, 0, 6);
                ofPopMatrix();
            } else if (drawMode == 4) {
                ofPushMatrix();
                ofTranslate(i, j);
                ofRotateZ(ofMap(brightness, 0, 255, 0, 180));
                ofDrawArrow(ofPoint(0, 0), ofPoint(10, 10));
                ofPopMatrix();
            }
        }
    }
}

//--------------------------------------------------------------
void energyWaveApp::cleanup(){
    ofSetRectMode(OF_RECTMODE_CORNER);
}

//--------------------------------------------------------------
void energyWaveApp::keyPressed(int key){
    if (key == '1') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(360) / 360.0) * 255, (ofRandom(100) / 100.0) * 255, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '2') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(120, 270) / 360.0) * 255, (ofRandom(80, 100) / 100.0) * 255, 255);
            }
        }
    } else if (key == '3') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(360) / 360.0) * 255, 255, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '4') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb(0, 0, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '5') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((195 / 360.0) * 255, 255, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '6') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((195 / 360.0) * 255, (ofRandom(100) / 100.0) * 255, 255);
            }
        }
    } else if (key == '7') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(180) / 360.0) * 255, 255, (ofRandom(100) / 100.0) * 255);
            }
        }
    } else if (key == '8') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                pixelColors[i][j] = ofColor::fromHsb((ofRandom(180, 360) / 360.0) * 255, (ofRandom(80, 100) / 100.0) * 255, (ofRandom(50, 90) / 100.0) * 255);
            }
        }
    } else if (key == '9') {
        for (int i = 0; i < grabber.getWidth(); i++) {
            for (int j = 0; j < grabber.getHeight(); j++) {
                if (floor(ofRandom(2)) == 0) {
                    pixelColors[i][j] = ofColor::fromHsb((ofRandom(270, 360) / 360.0) * 255, (ofRandom(80, 100) / 100.0) * 255, 255);
                } else {
                    pixelColors[i][j] = ofColor::fromHsb((ofRandom(0, 50) / 360.0) * 255, (ofRandom(80, 100) / 100.0) * 255, 255);
                }
            }
        }
    } else if (key == 'c') {
        drawMode = 1;
    } else if (key == 'r') {
        drawMode = 2;
    } else if (key == 't') {
        drawMode = 3;
    } else if (key == 'a') {
        drawMode = 4;
    }
}