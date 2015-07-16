#include "testApp.h"
#include "stdio.h"


const int N = 256;
float spectrum[ N ];
float Rad = 500;
float Vel = 0.1;
int bandRad = 2;
int bandVel = 100;

const int n = 300;

float tx[n], ty[n];

ofPoint pCloud[n];

float time0 = 0;
Params param;

void Params::setup() {
	eCenter = ofPoint( ofGetWidth() / 2, ofGetHeight() / 2 );
	eRad = 800;
	velRad = 0;
	lifeTime = 2.0;
	rotate = 0;
	force = 1000;
	spinning = 1000;
	friction = 0.05;
}

Particle::Particle() {
	live = false;
}

//--------------------------------------------------------------
ofPoint randomPointInCircle( float maxRad ){
	ofPoint pnt;
	float rad = ofRandom( 0, maxRad );
	float angle = ofRandom( 0, M_TWO_PI );
	pnt.x = cos( angle ) * rad;
	pnt.y = sin( angle ) * rad;
	return pnt;
}

//--------------------------------------------------------------
void Particle::setup() {
	pos = param.eCenter + randomPointInCircle( param.eRad );
	vel = randomPointInCircle( param.velRad );
	time = 0;
	lifeTime = param.lifeTime;
	live = true;
}

//--------------------------------------------------------------
void Particle::update( float dt ){
	if ( live ) {
		//Rotate vel
		vel.rotate( 0, 0, param.rotate * dt );
        
		ofPoint acc;         //Acceleration
		ofPoint delta = pos - param.eCenter;
		float len = delta.length();
		if ( ofInRange( len, 0, param.eRad ) ) {
			delta.normalize();
            
			acc += delta * param.force;
            
			acc.x += -delta.y * param.spinning;
			acc.y += delta.x * param.spinning;
		}
		vel += acc * dt;            //Euler method
		vel *= ( 1 - param.friction );  //Friction
        
		pos += vel * dt;    //Euler method
        
		time += dt;
		if ( time >= lifeTime ) {
			live = false;   //Particle is now considered as died
		}
	}
}

//--------------------------------------------------------------
void Particle::draw(){
	if ( live ) {
        
		float size = ofMap(fabs(time - lifeTime/2), 0, lifeTime/2, 4, 0.5 );
        ofColor colorYo;
        colorYo.setHsb(ofRandom(255), 255, 255);
        ofSetColor(colorYo);
        
        //        ofColor colorYo;
        //        float hue = ofRandom(255);
        //        colorYo.setHue( hue );
        //		ofSetColor(colorYo);
        
		ofCircle( pos, size );
	}
}


void testApp::setup(){
    
    
    AA.setup();
    ofSoundStreamSetup(0, 2, this, 44100, 256, 4);
	left = new float[256];
	right = new float[256];
    // get data
    //	string filePath = "data.csv";
    //    ofFile file(filePath);
    //
    //    ofBuffer buffer(file);
    //	while (!buffer.isLastLine()) {
    //		string line = buffer.getNextLine();
    //		vector<string> words = ofSplitString(line, ",");
    //        float tempWord = ofToFloat(words[1]);
    //		timing.push_back(tempWord);
    //
    //	}
    
    // get over
    
	dinFont.loadFont("Sudbury_Basin_3D.ttf", 30);
    song.loadSound("song.wav");
    ofSetCircleResolution(100);
    ofSetFrameRate(60);
    
    
    for(int i = 0 ; i < 200 ; i++){
        timing.push_back(860+i*9);
    }
    
    
    for (int i=0; i<N; i++) {
		spectrum[i] = 0.0f;
	}
    
	//Initialize points offsets by random numbers
	for ( int j=0; j<n; j++ ) {
		tx[j] = ofRandom( 0, 1000 );
		ty[j] = ofRandom( 0, 1000 );
	}
    score=0;
    
    
    param.setup();
	history = 0.9;
	bornRate = 800;
	bornCount = 0;
	time0 = ofGetElapsedTimef();
    ofSetLogLevel(OF_LOG_VERBOSE);
    client.setup("XXI0nNrOE3qqrEf1XTvgmg","0evWZmBjWm9Y7vPUBCgHiTBTqbOO5n6s9vMiAJ1veP0");
    send = true;
    // ofSetVerticalSync(true);
    
    
    
}
void testApp::audioRequested (float * output, int bufferSize, int nChannels){
    // fill the output buffer with whatever audio samples (-1 to 1 float values) you want
}

//--------------------------------------------------------------
void testApp::update(){
    ofSoundUpdate();
    float *val = ofSoundGetSpectrum( N );
    
	for ( int i=0; i<N; i++ ) {
		spectrum[i] *= 0.97;	//Slow decreasing
		spectrum[i] = max( spectrum[i], val[i] );
	}
    
	float time = ofGetElapsedTimef();
	float dt = time - time0;
	dt = ofClamp( dt, 0.0, 0.1 );
	time0 = time; //Store the current time
    
	Rad = ofMap( spectrum[ bandRad ], 1, 3, 400, 800, true );
	Vel = ofMap( spectrum[ bandVel ], 0, 0.1, 0.05, 0.5 );
    
	for (int j=0; j<n; j++) {
		tx[j] += Vel * dt;	//move offset
		ty[j] += Vel * dt;	//move offset
		pCloud[j].x = ofSignedNoise( tx[j] ) * Rad;
		pCloud[j].y = ofSignedNoise( ty[j] ) * Rad;
	}
    
    
    
	int i=0;
	while (i < p.size()) {
		if ( !p[i].live ) {
			p.erase( p.begin() + i );
		}
		else {
			i++;
		}
	}
    
    
	bornCount += dt * bornRate;
	if ( bornCount >= 1 ) {          //It's time to born particle(s)
		int bornN = int( bornCount );//How many born
		bornCount -= bornN;          //Correct bornCount value
		for (int i=0; i<bornN; i++) {
			Particle newP;
			newP.setup();            //Start a new particle
			p.push_back( newP );     //Add this particle to array
		}
	}
    
	for (int i=0; i<p.size(); i++) {
		p[i].update( dt );
	}
    
}


//--------------------------------------------------------------
void testApp::draw(){
    count = ofGetFrameNum();
    
	if(playSong){
        song.play();
        playSong = false;
    }
    if(song.getPosition()>0.99){
        playSong=true;
    }
    
    if(client.isAuthorized())
    {
        ofBackground(255,200,0);
    }
    else
    {
        ofBackground(255,0,0);
    }
    //	ofBackground(255,219,0);
    ofColor color;
    color.setHsb(Rad-400, 255, 255);
    ofSetColor(color);
	for (int i = 0; i < 256; i++){
        ofSetLineWidth(4);
		ofLine(i*5,ofGetHeight()/2,i*5,ofGetHeight()/2+left[i]*5000);
	}
    
    
	ofSetColor(87,61,15);
    for(int i = 0; i<199; i=i+2){
        if(count>840){
            ofSetColor(255);
            if((i*120+move)< -200){
                ofSetColor(255,0,0);
            }else{
                ofSetColor(87,61,15);
            }
            
            dinFont.drawString("chuck", 700+i*120+move, 600);
            
            if(count>timing[i] && count < timing[i+1]){
                if(!stopAdd && AA.amplitude>1){
                    stopAdd = true ;
                }
            }
            
            if(count>timing[i+2] && count < timing[i+3]){
                if(stopAdd && AA.amplitude<0.5){
                    score =  score + 1 ;
                    stopAdd=false;
                }
            }
            
        }
        
    }
    move = move-9;
    
    
    dinFont.drawString( "score is : " + ofToString(score), 350,50);
    // dinFont.drawString( "count is : " + ofToString(count), 350,100);
    //	dinFont.drawString( "pitch is : " + ofToString((int)AA.pitch), 50,500);
    //  dinFont.drawString( "amplitude is : " + ofToString(AA.amplitude,3), 50,375);
    //  dinFont.drawString( "rad is : " + ofToString(Rad), 50,55);
    //	dinFont.drawString( "confidence is : " + ofToString(AA.confidence), 50,450);
	
    if(send){
        if(client.isAuthorized())
        {
            
            std::string s = client.exampleUpdateStatusMethod("#ydasdka67"+ofToString(ofRandom(200)));
            
            ofLogNotice("testApp::keyPressed") << s;
        }
        send=false;
    }
    
    
	ofPushMatrix();
	ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );
    
	ofSetColor(255,0,0,120);
	ofFill();
    ofSetLineWidth(1);
    
	for (int i=0; i<n; i++) {
		ofCircle( pCloud[i], 2 );
	}
    
	float dist = 40;	//Threshold parameter of distance
	for (int j=0; j<n; j++) {
		for (int k=j+1; k<n; k++) {
			if ( ofDist( pCloud[j].x, pCloud[j].y, pCloud[k].x, pCloud[k].y )
				< dist ) {
                ofLine( pCloud[j], pCloud[k] );
			}
		}
	}
    
	ofPopMatrix();
    
	ofEnableAlphaBlending();
	float alpha = (1-history) * 255;
	ofSetColor( 255, 255, 255, alpha );
	ofFill();
	ofRect( 0, 0, ofGetWidth(), ofGetHeight() );
	ofDisableAlphaBlending();
    
	ofFill();
	for (int i=0; i<p.size(); i++) {
		p[i].draw();
	}
    //    if(count<8
    //    ofSetColor(0);
    //    dinFont.drawString("READY", 450,600);
}


//--------------------------------------------------------------
void testApp::audioReceived (float * input, int bufferSize, int nChannels){
	
	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
    
	AA.processAudio(left, bufferSize);
}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    //    if(client.isAuthorized()) {
    //	if(key == 'p'){
    //
    //        string p = client.exampleUpdateStatusMethod("openFrameworks to Twitter !!"); //put the post content in here
    //        cout << "post result:  "<< p <<endl;
    //    }
    //    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	
}


