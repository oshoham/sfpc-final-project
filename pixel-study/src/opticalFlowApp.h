#ifndef opticalFlowApp_h
#define opticalFlowApp_h

#include "ofMain.h"
#include "ofxOpticalFlowFarneback.h"
#include "particle.h"
#include "subApp.h"

class opticalFlowApp: public subApp {
    public:
        void setup(ofBaseVideoGrabber * videoGrabber);
        void update(float potentiometer1, float potentiometer2);
        void draw();
        void cleanup();
        
        void drawLineAsRect(ofPoint startVec, ofPoint endVec, float thickness);
        
        ofBaseVideoGrabber * grabber;
        ofxOpticalFlowFarneback flowSolver;
        vector<particle> particles;
        vector<ofPolyline> lines;
        vector<int> lineWidths;
        vector<int> lineLengths;
        ofImage frame;
    
        int maxLineLength;
        int maxLineWidth;
        int numParticles;
};

#endif /* opticalFlowApp_h */
