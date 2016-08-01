#ifndef voronoiApp_h
#define voronoiApp_h

#include "ofMain.h"
#include "subApp.h"
#include "ofxVoronoi.h"
#include "ofxRPiCameraVideoGrabber.h"

#define SQRT1_2 0.7071067811865476

class voronoiApp : public subApp {
    public:
        void setup(ofxRPiCameraVideoGrabber * videoGrabber);
        void update(float potentiometer1, float potentiometer2);
        void draw();
        void cleanup();
        
        vector<ofPoint> points;
        ofxRPiCameraVideoGrabber * grabber;
    
        ofxVoronoi voronoi;
        int numPoints;
};

#endif /* voronoiApp_h */
