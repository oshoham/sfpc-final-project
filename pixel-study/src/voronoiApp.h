#ifndef voronoiApp_h
#define voronoiApp_h

#include "ofMain.h"
#include "subApp.h"
#include "ofxVoronoi.h"

#define SQRT1_2 0.7071067811865476

class voronoiApp : public subApp {
    public:
        void setup(ofBaseVideoGrabber * videoGrabber);
        void update(float potentiometer1, float potentiometer2);
        void draw();
        void cleanup();
    
        void recalculateVoronoi();
    
        vector<ofPoint> points;
        ofBaseVideoGrabber * grabber;
    
        ofxVoronoi voronoi;
        int numPoints;
        int k;
};

#endif /* voronoiApp_h */
