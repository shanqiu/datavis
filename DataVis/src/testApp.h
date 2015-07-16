#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"

class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    

	void windowResized(int w, int h);


    
    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
    

    
    ofVec3f left_hand, prev_left_hand;
    ofVec3f left_foot, prev_left_foot;
    ofVec3f left_hip, prev_left_hip;
    ofVec3f left_knee, prev_left_knee;
    ofVec3f left_shoulder, prev_left_shoulder;
    ofVec3f left_elbow, prev_left_elbow;
    
    
    ofVec3f right_hand, prev_right_hand;
    ofVec3f right_foot, prev_right_foot;
    ofVec3f right_hip, prev_right_hip;
    ofVec3f right_knee, prev_right_knee;
    ofVec3f right_shoulder, prev_right_shoulder;
    ofVec3f right_elbow, prev_right_elbow;
    

    ofVec3f head, prev_head;
    
    vector<float> rate;
    int currentIndex;
	
    ofTrueTypeFont font;
    ofTrueTypeFont font2;
    ofPath path;
    ofPath pathPerson;
    
    float accel;
    float speed;
    int which;
    float diffRate;
    
    float lineSpeed;
    float footSpeed;
    
    float currTime;
    float keyTime;
    
    int currScene=0;
    
    int numUsers=1;
    
    ofColor startColor;
    
    bool startFlag= true;
    bool direction =true;
};

#endif
