#ifndef energyWaveApp_h
#define energyWaveApp_h

#include "ofMain.h"
#include "subApp.h"

class energyWaveApp : public subApp {
    public:
        void setup(ofBaseVideoGrabber * videoGrabber);
        void update(float potentiometer1, float potentiometer2);
        void draw();
        void cleanup();
    
        void keyPressed(int key);
    
        void setColorMode();
    
        int pixelStep;
    
        ofBaseVideoGrabber * grabber;
        vector<vector<ofColor>> pixelColors;
        vector<vector<float>> energy;
        int drawMode;
        int colorMode;
};


#endif /* energyWaveApp_h */
