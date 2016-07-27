#include "asciiMosaicApp.h"

//--------------------------------------------------------------
bool charWithBrightnessComparator(charWithBrightness & a, charWithBrightness & b) {
    return a.brightness < b.brightness;
}

//--------------------------------------------------------------
void asciiMosaicApp::setup(ofVideoGrabber videoGrabber){
    grabber = videoGrabber;
    
    screenElementSize = 8;
    
    font.load("NotoSans-Regular.ttf", screenElementSize - 2, true, true, true);
    font.setLineHeight(18.0f);
    font.setLetterSpacing(1.037);
    
    int fboSize = 50;
    fbo.allocate(fboSize, fboSize);
    
    ofSetColor(0);
    for (int i = 0; i < 255; i++) {
        ofTTFCharacter character = font.getCharacterAsPoints(i);
        fbo.begin();
        ofClear(255, 255, 255, 255);
        character.draw(fbo.getWidth() / 2, fbo.getHeight() / 2);
        fbo.end();
        
        ofPixels pixels;
        fbo.readToPixels(pixels);
        
        float totalBrightness = 0;
        for (int x = 0; x < pixels.getWidth(); x++) {
            for (int y = 0; y < pixels.getHeight(); y++) {
                totalBrightness += pixels.getColor(x, y).getBrightness();
            }
        }
        float averageBrightness = totalBrightness / (float)(fboSize * fboSize);
        
        charWithBrightness cb;
        cb.value = i;
        cb.brightness = averageBrightness;
        charactersByBrightness.push_back(cb);
    }
    
    ofSort(charactersByBrightness, charWithBrightnessComparator);
}

//--------------------------------------------------------------
void asciiMosaicApp::update(float potentiometer1, float potentiometer2){
    grabber.update();
}

//--------------------------------------------------------------
void asciiMosaicApp::draw(){
    ofBackground(255);
    ofSetColor(0);
    
    ofRectangle viewport = ofGetCurrentViewport();
    
    ofPixels pixels = grabber.getPixels();
    pixels.mirror(false, true);
    
    for (int i = 0; i < grabber.getWidth(); i+=screenElementSize) {
        for (int j = 0; j < grabber.getHeight(); j+=screenElementSize) {
            float sum = 0;
            float numPixels = 0;
            for (int k = 0; k < screenElementSize; k++) {
                for (int l = 0; l < screenElementSize; l++) {
                    if (viewport.inside(i + k, j + l)) {
                        ofColor color = pixels.getColor(i + k, j + l);
                        float luma = color.r * 0.2126 + color.g * 0.7152 + color.b * 0.0722;
                        sum += luma;
                        numPixels++;
                    }
                }
            }
            
            float averageLuma = sum / numPixels;
            
            averageLuma = 255 * pow(averageLuma / 255, 3);
            
            charWithBrightness cb = charactersByBrightness[averageLuma];
            ofTTFCharacter character = font.getCharacterAsPoints(cb.value);
            character.draw(i, j);
            
        }
    }
}

//--------------------------------------------------------------
void asciiMosaicApp::cleanup(){
    charactersByBrightness.clear();
}
