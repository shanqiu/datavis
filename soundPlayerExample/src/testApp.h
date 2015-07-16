#pragma once

#include "ofMain.h"

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

		ofTrueTypeFont	font;
        ofTrueTypeFont	fontTitle;
		float 			synthPosition;
    
    //-------------------------------------------------
    bool switchPhone=false;
    bool goLevel0= false;
    
    //-------------------------------------------------
    bool inroom = false;
    float speedX;
    float speedY;
    float posX;
    float posY;
    int currTime;
    int keyTime;
    int keyTimeOpenDoor;
    
    bool stopUp=false;
    bool stopRight=false;
    bool stopLeft=false;
    bool stopDown=false;
    
    bool touchDoor=false;
    bool flag=true;
    

    bool showTuto=false;
    bool switchStart=false;
    bool switchTuto=false;
    
    ofImage first;
    //-------------------------------------------------
    int keyTime2;
    int keyTimeRain;

    bool playLeft=true;
    bool playRight=false;
    int keyTimeBird;
    int keyTimeDelay;

    
    float speedX2;
    float speedY2;
    float posX2;
    float posY2;
    
    float prePosX2=0;
    float prePosY2=0;
    
    bool leftFlag=true;
    bool rightFlag=true;
    bool rainFlag=true;
    bool delayFlag=false;
    
    int countLevel2=0;
    //-------------------------------------------------
    int keyTime3;
    float speedX3;
    float speedY3;
    float posX3;
    float posY3;
    
    bool bgFlag=true;
    bool laughFlag=true;
    ofPoint laughPerson;
    ofPoint stage;
    
    bool beatFirst;
    bool beatSecond;
    
    float beatTime;
    bool infoFlag=true;
    
    int countKey;
    bool singFlag=true;
    bool finalFlag=true;
    bool startCount=false;
    float reduce=0.01;
    float tempVol=0.8f;
    
    bool finalFlag2=false;
    
    int writeCount=0;
    string write;
    
    //--------------------------------------------------
    
    int keyTime4;
    int keyTimeStop;
    
    float speedX4;
    float speedY4;
    
    float posX4=0;
    float posY4=0;
    
    bool coverFlag=true;
    
    //-------------------------------------------------
    int level=-1;
};

