#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	speed =0;
    which=0;
    lineSpeed=0;
    lineAceel=1;
	currentIndex = 0;
	string filePath = "data.csv";
	font.loadFont("frabk.ttf", 6);
    font2.loadFont("frabk.ttf", 20);
	ofFile file(filePath);
	
	if(!file.exists()){
		ofLogError("The file " + filePath + " is missing");
	}
	
	ofBuffer buffer(file);
	while (!buffer.isLastLine()) {
		string line = buffer.getNextLine();
		vector<string> words = ofSplitString(line, ",");
        
        float tempWord = ofToFloat(words[1]);
        
		rate.push_back(tempWord);
        
    
	}
    ofSetFrameRate(60);
    ofBackground(255);
    
    path.setCurveResolution(120);
    
    ofSetBackgroundAuto(true);
    
}

//--------------------------------------------------------------
void testApp::update(){



}

//--------------------------------------------------------------
void testApp::draw(){
    
    if(currScene==0){
    
    
    
    
    }
    
    
    
    
    if(currScene==1){
    
    if(which < 51){
    diffRate = rate[which+1]-rate[which];
    
    if(diffRate<0){
        
        accel = -0.1;
        if(speed< diffRate){
                speed=0;
                which=which+1;
                //fill(255,0,0);
            }else{
                speed=speed+accel;
            }
    }else if(diffRate>0){
        accel = 0.1;
            if(speed> diffRate){
                speed=0;
                which=which+1;
                //fill(255,0,0);
            }else{
                speed=speed+accel;
            }
    }
    ofColor c(0,0,0);
    path.clear();
    ofSetColor(0, 0, 0);
    for (int i=0; i<rate.size(); i++) {
   
       //font.drawString(ofToString(rate[i]), ofGetWidth()/2, i*10);
		
	}
    path.setFillColor(c);
    path.moveTo(ofGetWidth()/2-(rate[which]+speed)/10,0);
    path.bezierTo(ofGetWidth()/2-(rate[which]+speed)/10, ofGetHeight(), ofGetWidth()/2-(rate[which]+speed)/10, ofGetHeight(), 0, ofGetHeight());
    path.bezierTo(ofGetWidth(), ofGetHeight(), 0, ofGetHeight(), ofGetWidth(), ofGetHeight());
    path.bezierTo(ofGetWidth()/2+(rate[which]+speed)/10, ofGetHeight(), ofGetWidth()/2+(rate[which]+speed)/10, ofGetHeight(), ofGetWidth()/2+(rate[which]+speed)/10, 0);
    path.close();
    
    path.draw();
        ofSetColor(255);
        for(int i=0; i<40; i++){
            ofRect(ofGetWidth()/2-2,i*(4 +i*4+lineSpeed),4 ,(5 + 5*i+lineSpeed));
        }
    }
    ofSetColor(255);
    
    ofRect(ofGetWidth()/2-100, 20, 200, 50);
    
    ofNoFill();
    ofSetColor(0);//stroke color
    ofRect(ofGetWidth()/2-100, 20, 200, 50);
    
    ofFill();
    ofSetColor(0);
        
    font2.drawString(ofToString(which+1+1961), ofGetWidth()/2-35, 53);
        
 
    font2.drawString(ofToString(rate[which+1]), ofGetWidth()/2-150, 53);
        
    font2.drawString(ofToString(rate[which]+speed), ofGetWidth()/2-300, 53);
 
    lineSpeed=lineSpeed+lineAceel;
    if(lineSpeed>9){
        lineSpeed=0;
        lineAceel=0;
    }
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	//Create a comparable string from an int
	

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
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
	

}




