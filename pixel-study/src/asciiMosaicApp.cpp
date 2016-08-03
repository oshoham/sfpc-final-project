#include "asciiMosaicApp.h"

//--------------------------------------------------------------
bool charWithBrightnessComparator(charWithBrightness & a, charWithBrightness & b) {
    return a.brightness < b.brightness;
}

//--------------------------------------------------------------
void asciiMosaicApp::setup(ofBaseVideoGrabber * videoGrabber){
    grabber = videoGrabber;
    
    screenElementSize = 8;
    characterRangeSize = 26;
    
    font.load("Helvetica.dfont", screenElementSize - 2, true, true, true);
    font.setLineHeight(18.0f);
    font.setLetterSpacing(1.037);
    
    int fboSize = 50;
    fbo.allocate(fboSize, fboSize);
    
    sortCharacters();
}

//--------------------------------------------------------------
void asciiMosaicApp::sortCharacters(){
    charactersByBrightness.clear();
    int fboSize = 50;
    ofSetColor(0);
    for (int i = 0; i < 255; i++) {
        fbo.begin();
        ofClear(255, 255, 255, 255);
        string s;
        char c = (char)i;
        s += c;
        font.drawString(s, fbo.getWidth() / 2, fbo.getHeight() / 2);
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
    characterRangeStart = ofMap(potentiometer1, 0, 1023, 5, 127);
    int newFontMode = ofMap(potentiometer1, 0, 1023, 0, 8);
    int newScreenElementSize = ofMap(potentiometer2, 0, 1023, 6, 32);
    
    if (newFontMode != fontMode || newScreenElementSize != screenElementSize) {
        screenElementSize = newScreenElementSize;
        string fontname;
        
        if (newFontMode == 0) {
            fontname = "Helvetica.dfont";
        } else if (newFontMode == 1) {
            fontname = "Phosphate.ttc";
        } else if (newFontMode == 2) {
            fontname = "HeadlineA.ttf";
        } else if (newFontMode == 3) {
            fontname = "Papyrus.ttc";
        } else if (newFontMode == 4) {
            fontname = "Comic Sans MS.ttf";
        } else if (newFontMode == 5) {
            fontname = "Brush Script.ttf";
        } else if (newFontMode == 6) {
            fontname = "Chalkduster.ttf";
        } else if (newFontMode == 7) {
            fontname = "Hanzipen.ttc";
        } else if (newFontMode == 8) {
            fontname = "cmuntt.otf";
        }
    
        font.load(fontname, screenElementSize - 2, true, true, true);
    
        if (newFontMode != fontMode) {
            sortCharacters();
        }
        
        fontMode = newFontMode;
    }
}

//--------------------------------------------------------------
void asciiMosaicApp::draw(){
    ofBackground(255);
    ofSetColor(0);
    
    ofRectangle viewport = ofRectangle(0, 0, grabber->getWidth(), grabber->getHeight());
    
    ofPixels pixels = grabber->getPixels();
    pixels.mirror(false, true);
    
    for (int i = 0; i < grabber->getWidth(); i+=screenElementSize) {
        for (int j = 0; j < grabber->getHeight(); j+=screenElementSize) {
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
//            averageLuma = ofMap(averageLuma, 0, 255, 0, characterRangeSize);
            
            charWithBrightness cb = charactersByBrightness[averageLuma];
            string s;
            char c = (char)cb.value;
            s += c;
            font.drawString(s, i, j);
        }
    }
}

//--------------------------------------------------------------
void asciiMosaicApp::cleanup(){
    charactersByBrightness.clear();
}
