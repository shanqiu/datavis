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
    
    ofTrueTypeFont verdana;
    ofTrueTypeFont  font;
    
    ofVec3f left_hand, prev_left_hand;
    ofVec3f left_foot, prev_left_foot;
    ofVec3f left_hip, prev_left_hip;
    ofVec3f right_hand, prev_right_hand;
    ofVec3f head, prev_head;
    
    float current_time, prev_time, dist_time;
    
    bool switchT = false;
    
    bool left_drag;
    bool right_drag;
    bool running;
    
    int numUsers;
    
    int currTime;
    int keyTime; //moment we pressed key
    bool leftKeyFlag;
    bool upKeyFlag;
    bool rightKeyFlag;
    bool leftByRun = 0;
    bool rightByRun = 0;
    ofSoundPlayer  beats;
    
    
    //game part
    
    ofSoundPlayer click;
    ofSoundPlayer  openDoor;
    ofSoundPlayer  foot;
    ofSoundPlayer  birdL;
    ofSoundPlayer  birdR;
    ofSoundPlayer  foot2;
    ofSoundPlayer foot2_2;
    ofSoundPlayer rain;
    ofSoundPlayer lobby;
    ofSoundPlayer laugh;
    ofSoundPlayer drum;
    ofSoundPlayer info;
    ofSoundPlayer sing;
    ofSoundPlayer talk;
    ofSoundPlayer applause;
    ofSoundPlayer drumDrop;
    ofSoundPlayer final;
    ofSoundPlayer intro;
    ofSoundPlayer drum2;

    ofTrueTypeFont	fontTitle;
    int timer=0;
    bool foot_flag=true;
    
    bool touch_door=false;
    bool flag=true;
    int keyTimeOpenDoor;
    int keyTimeRain;

    int keyTimeBird;

    bool leftFlag=true;
    bool rainFlag=true;
    
    int countLevel2=0;
    int keyTimeDelay;
    
    int firstDelay;
    bool firstDelayFlag=true;
    //-------------------------------------------------
    
    
    bool introOk=true;
    bool introFlag=true;
    
    bool bgFlag=true;
    bool laughFlag=true;
    ofPoint laughPerson;
    ofPoint stage;
    ofPoint lobbyPos;
    
    bool beatFirst;
    bool beatSecond;
    
    float beatTime;
    bool infoFlag=true;
    
    int countKey=0;
    bool singFlag=true;
    bool finalFlag=true;
    bool startCount=false;
    float reduce=0.01;
    float tempVol=0.8f;
    
    bool finalFlag2=false;
    
    int writeCount=0;
    string write;
    bool drum_flag=true;
    bool drum_flag2=true;
    
    bool firstInfo=false;
    bool someFlag=true;
    bool lobbyFlag=true;
    bool stopDrumFlag=false;
      //-------------------------------------------------
    int level=0;

};

#endif
