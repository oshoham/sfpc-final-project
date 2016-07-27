#ifndef voronoiApp_h
#define voronoiApp_h

#include "ofMain.h"
#include "subApp.h"

#define SQRT1_2 0.7071067811865476

class voronoiApp : public subApp {
    public:
        void setup(ofBaseVideoGrabber * videoGrabber);
        void update(float potentiometer1, float potentiometer2);
        void draw();
        void cleanup();
        
        void keyPressed(int key);
        
        ofPoint poissonDiscSample();
        bool far(int x, int y);
        ofPoint sample(int x, int y);
        
        int k;
        int radius;
        int radius2;
        int R;
        int cellSize;
        int gridWidth;
        int gridHeight;
        vector<ofPoint> grid;
        vector<ofPoint> queue;
        int sampleSize;
        
        vector<ofPoint> points;
        ofBaseVideoGrabber * grabber;
};

#endif /* voronoiApp_h */
