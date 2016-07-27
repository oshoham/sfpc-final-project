#pragma once

#include "ofMain.h"
#include "subApp.h"
#include "opticalFlowApp.h"
#include "asciiMosaicApp.h"
#include "energyWaveApp.h"
#include "voronoiApp.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        float potentiometer1;
        float potentiometer2;
        int mode;
    
        ofVideoGrabber grabber;
        opticalFlowApp flowApp;
        asciiMosaicApp mosaicApp;
        energyWaveApp waveApp;
        voronoiApp vorApp;
        subApp * currentApp;
};
