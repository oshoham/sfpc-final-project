#include "voronoiApp.h"
#include "PoissonGenerator.h"

//--------------------------------------------------------------
void voronoiApp::setup(ofBaseVideoGrabber * videoGrabber){
    grabber = videoGrabber;
    
    numPoints = 10000;
    k = 5;
    
    voronoi.setBounds(ofRectangle(0, 0, grabber->getWidth(), grabber->getHeight()));
    
    recalculateVoronoi();
}

//--------------------------------------------------------------
void voronoiApp::recalculateVoronoi(){
    points.clear();
    voronoi.clear();

    PoissonGenerator::DefaultPRNG PRNG;
    const auto poissonPoints = PoissonGenerator::GeneratePoissonPoints(numPoints, PRNG, k, false);
    for (auto & p : poissonPoints) {
        ofPoint point(p.x * grabber->getWidth(), p.y * grabber->getHeight());
        points.push_back(point);
    }
    
    voronoi.addPoints(points);
    voronoi.generate();

}


//--------------------------------------------------------------
void voronoiApp::update(float potentiometer1, float potentiometer2){    
    int newNumPoints = ofMap(potentiometer2, 0, 1023, 8000, 100);
    
    if (newNumPoints != numPoints) {
        numPoints = newNumPoints;
        recalculateVoronoi();
    }
}

//--------------------------------------------------------------
void voronoiApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    ofPixels pixels = grabber->getPixels();
    pixels.mirror(false, true);
    
    vector <ofxVoronoiCell> cells = voronoi.getCells();
    voronoi.draw();
    
    for(int i = 0; i < cells.size(); i++) {
        // Draw cell borders
        ofPolyline line;
        for(int j=0; j<cells[i].pts.size(); j++) {
            ofPoint lastPt = cells[i].pts[cells[i].pts.size()-1];
            if(j > 0) {
                lastPt = cells[i].pts[j-1];
            }
            line.addVertex(lastPt);
            ofPoint thisPt = cells[i].pts[j];
            
            if(!voronoi.isBorder(lastPt) || !voronoi.isBorder(thisPt)) {
                line.addVertex(thisPt);
            }
        }
        
        ofPath path;
        path.setFillColor(pixels.getColor(cells[i].pt.x, cells[i].pt.y));
        path.setStrokeWidth(0);
        for (int j = 0; j < line.getVertices().size(); j++) {
            if (j == 0) {
                path.newSubPath();
                path.moveTo(line.getVertices()[j]);
            } else {
                path.lineTo(line.getVertices()[j]);
            }
        }
        path.draw();
    }
}

//--------------------------------------------------------------
void voronoiApp::cleanup(){
    points.clear();
    voronoi.clear();
}
