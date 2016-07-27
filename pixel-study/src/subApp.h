#ifndef subApp_h
#define subApp_h

class subApp {
    public:
        virtual void setup(ofVideoGrabber videoGrabber) = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void cleanup() = 0;
};

#endif /* subApp_h */
