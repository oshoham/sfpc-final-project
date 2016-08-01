#include "opticalFlowApp.h"

//--------------------------------------------------------------
void opticalFlowApp::setup(ofxRPiCameraVideoGrabber * videoGrabber){
    grabber = videoGrabber;
//    videoGrabber->setDesiredFrameRate(30);
//    flowSolver.setup(grabber->getWidth() / 2, grabber->getHeight() / 2, 0.35, 5, 10, 1, 3, 2.25, false, false);
    flowSolver.setup(grabber->getWidth() / 2, grabber->getHeight() / 2);
    ofSetBackgroundAuto(false);
    
    maxLineWidth = 15;
    maxLineLength = 3;
    numParticles = 1000;
    
    for (int i = 0; i < numParticles; i++) {
        particle p = particle();
        p.pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        p.vel.set(0, 0);
        particles.push_back(p);
        lines.push_back(ofPolyline());
        lineWidths.push_back(ofRandom(1, maxLineWidth));
        lineLengths.push_back(ofRandom(2, maxLineLength));
    }
    ofBackground(255);
}

//--------------------------------------------------------------
void opticalFlowApp::update(float potentiometer1, float potentiometer2){
    float gravity = 0.2;
    int newMaxLineLength = ofMap(potentiometer2, 0, 1023, 3, 5);
    int newMaxLineWidth = ofMap(potentiometer2, 0, 1023, 8, 30);
    int newNumParticles = ofMap(potentiometer1, 0, 1023, 1000, 10000);
    
    if (newMaxLineLength != maxLineLength || newMaxLineWidth != maxLineWidth) {
        maxLineLength = newMaxLineLength;
        maxLineWidth = newMaxLineWidth;
        
        for (int j = 0; j < lineLengths.size(); j++) {
            lineLengths[j] = ofRandom(2, maxLineLength);
            lineWidths[j] = ofRandom(1, maxLineWidth);
        }
    }
    
    if (newNumParticles != numParticles) {
        if (numParticles < newNumParticles) {
            for (int k = 0; k < newNumParticles - numParticles; k++) {
                particle p = particle();
                p.pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
                p.vel.set(0, 0);
                particles.push_back(p);
                lines.push_back(ofPolyline());
                lineWidths.push_back(ofRandom(1, maxLineWidth));
                lineLengths.push_back(ofRandom(2, maxLineLength));
            }
        } else {
            int amountToErase = numParticles - newNumParticles;
            particles.erase(particles.end() - amountToErase, particles.end());
            lines.erase(lines.end() - amountToErase, lines.end());
            lineWidths.erase(lineWidths.end() - amountToErase, lineWidths.end());
            lineLengths.erase(lineLengths.end() - amountToErase, lineLengths.end());
        }
        numParticles = newNumParticles;
    }
    
    if (grabber->isFrameNew()) {
        ofPixels pixels;
        pixels.setFromPixels(grabber->getPixels(), grabber->getWidth(), grabber->getHeight(), OF_IMAGE_COLOR);
        pixels.mirror(false, true);
        flowSolver.update(pixels.getData(), ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
        
        for (int i = 0; i < particles.size(); i++) {
            particles[i].resetForce();
            particles[i].addForce(0.0, 0.2);
            ofPoint flowVelocity = flowSolver.getVelAtNorm(particles[i].pos.x / (float)ofGetWidth(), particles[i].pos.y / (float)ofGetHeight()) * 0.5;
            particles[i].addForce(flowVelocity.x, flowVelocity.y);
            particles[i].addDampingForce();
            particles[i].update();
            
            if (particles[i].isOutsideWalls()) {
                lines[i].clear();
                particles[i].wrapAroundWalls();
            }
            
            lines[i].addVertex(particles[i].pos);
            
            if (lines[i].size() > lineLengths[i]) {
                lines[i].getVertices().erase(lines[i].getVertices().begin());
            }
        }
    }
}

//--------------------------------------------------------------
void opticalFlowApp::draw(){
    ofPixels pixels;
    pixels.setFromPixels(grabber->getPixels(), grabber->getWidth(), grabber->getHeight(), OF_IMAGE_COLOR);
    pixels.mirror(false, true);
    ofRectangle viewport = ofGetCurrentViewport();
    
    for (int i = 0; i < particles.size(); i++) {
        if (viewport.inside(particles[i].pos)) {
            ofSetColor(pixels.getColor(particles[i].pos.x, particles[i].pos.y));
            if (lines[i].getVertices().size() > 0) {
                drawLineAsRect(lines[i].getVertices().front(), lines[i].getVertices().back(), lineWidths[i]);
            }
        }
    }
}

//--------------------------------------------------------------
void opticalFlowApp::drawLineAsRect(ofPoint startVec, ofPoint endVec, float thickness) {
    float angle = atan((endVec.y-startVec.y)/(endVec.x-startVec.x));
    ofPushMatrix();
    ofTranslate(startVec.x,startVec.y);
    ofRotate(ofRadToDeg(angle));
    float lineLength = (endVec.x - startVec.x)/cos(angle);
    ofDrawRectangle(0, -thickness/2, lineLength, thickness);
    ofPopMatrix();
}

//--------------------------------------------------------------
void opticalFlowApp::cleanup() {
    flowSolver.reset();
    particles.clear();
    lines.clear();
    lineWidths.clear();
    lineLengths.clear();
    
    ofSetBackgroundAuto(true);
}
