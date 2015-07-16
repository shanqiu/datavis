#ifndef _TEST_APP
#define _TEST_APP



#include "ofMain.h"
#include "aubioAnalyzer.h"
#include "ofEvents.h"
#include "ofxExampleTwitterClient.h"




class Particle {
public:
	Particle();                //Class constructor
	void setup();              //Start particle
	void update( float dt );   //Recalculate physics
	void draw();               //Draw particle
    
	ofPoint pos;               //Position
	ofPoint vel;               //Velocity
	float time;                //Time of living
	float lifeTime;            //Allowed lifetime
	bool live;
    
};

class Params {
public:
	void setup();
	ofPoint eCenter;    //Emitter center
	float eRad;         //Emitter radius
	float velRad;       //Initial velocity limit
	float lifeTime;     //Lifetime in seconds
    
	float rotate;   //Direction rotation speed in angles per second
    
	float force;       //Attraction/repulsion force inside emitter
	float spinning;    //Spinning force inside emitter
	float friction;    //Friction, in the range [0, 1]
};

extern Params param; //Declaration of a global variable


class testApp : public ofSimpleApp{
	
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    void audioReceived		(float * input, int bufferSize, int nChannels);
    void audioRequested (float * output, int bufferSize, int nChannels);
    
    float * left;
    float * right;
    
    bool playSong = true;
    bool stopAdd =  true;
    aubioAnalyzer AA;
	
    ofTrueTypeFont dinFont;
	
    vector<float> timing;
    
    ofSoundPlayer song;
    float move = -5;
    int score;
    
    
    int count;
    
    vector<Particle> p;	  //Particles
	ofFbo fbo;            //Off-screen buffer for trails
    
	float history;        //Control parameter for trails
	float time0;          //Time value for computing dt
    
	float bornRate;       //Particles born rate per second
	float bornCount;      //Integrated number of particles to born
    
    ofxExampleTwitterClient client;
    bool send;
    
};



#endif	

