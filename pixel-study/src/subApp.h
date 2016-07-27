#ifndef subApp_h
#define subApp_h

class subApp {
    public:
        virtual void setup(ofVideoGrabber videoGrabber) = 0;
        virtual void update(float potentiometer1, float potentiometer2) = 0;
        virtual void draw() = 0;
        virtual void cleanup() = 0;
    
        float potentiometer1Max = 100;
        float potentiometer2Max = 100;
};

#endif /* subApp_h */
