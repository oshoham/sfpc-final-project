#pragma once

#include "ofMain.h"
#include "ofxGui.h"
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
    
        void setupArduino(const int & version);
        void digitalPinChanged(const int & pinNum);
        void analogPinChanged(const int & pinNum);
        void updateArduino();
    
        void modeChanged(int & value);
    
        ofArduino ard;
        bool bSetupArduino;
    
        ofVideoGrabber grabber;
        opticalFlowApp flowApp;
        asciiMosaicApp mosaicApp;
        energyWaveApp waveApp;
        voronoiApp vorApp;
        subApp * currentApp;
    
        ofxPanel panel;
        ofParameterGroup params;
        ofParameter<float> potentiometer1;
        ofParameter<float> potentiometer2;
        ofParameter<int> mode;
};
