#pragma once

#include "ofMain.h"
#include "MorseCodePlayer.h"



class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		vector<float> rate;
		int currentIndex;
	
		ofTrueTypeFont font;
        ofTrueTypeFont font2;
        ofPath path;
    
    float accel;
    float speed;
    int which;
    float diffRate;
    
    float lineSpeed;
    
    int currScene=1;
    
    float lineAceel;

};
