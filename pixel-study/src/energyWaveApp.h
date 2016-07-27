#ifndef energyWaveApp_h
#define energyWaveApp_h

#include "ofMain.h"
#include "subApp.h"

class energyWaveApp : public subApp {
    public:
        void setup(ofVideoGrabber videoGrabber);
        void update();
        void draw();
        void cleanup();
    
        void keyPressed(int key);
    
        int pixelStep;
    
        ofVideoGrabber grabber;
        vector<vector<ofColor>> pixelColors;
        vector<vector<float>> energy;
        int drawMode;
};


#endif /* energyWaveApp_h */
