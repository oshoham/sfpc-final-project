#ifndef asciiMosaicApp_h
#define asciiMosaicApp_h

#include "ofMain.h"
#include "subApp.h"

typedef struct {
    int value;
    float brightness;
} charWithBrightness;

class asciiMosaicApp : public subApp {
    public:
        void setup(ofVideoGrabber videoGrabber);
        void update(float potentiometer1, float potentiometer2);
        void draw();
        void cleanup();
        
        int screenElementSize;
        
        ofVideoGrabber grabber;
        ofTrueTypeFont font;
        
        vector<charWithBrightness> charactersByBrightness;
        ofFbo fbo;
};

#endif /* asciiMosaicApp_h */
