#ifndef CCPPCLASS_H
#define CCPPCLASS_H

class TrVector { // Tracking vector | DO NOT USE 'new' operation, JUST FOR TRACKING
public:
    float* x;
    float* y;
    TrVector();
    TrVector(float* _x, float* _y);
};

#endif