#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
   
public:
   void setup();
   void update();
   void draw();
   
   void mouseReleased(int x, int y, int button);
};
