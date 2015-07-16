#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(1);
    openNIDevice.start();

    openNIDevice.setUseMaskTextureAllUsers(true);
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(1); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(1); // resolution of the mesh created for the point cloud eg., this will
    
    
    
    speed =0;
    which=0;
    lineSpeed=0;
	currentIndex = 0;
    ofColor c(0,0,0);
    startColor=c;

    ofSetFrameRate(60);
    ofBackground(255);
    
    path.setCurveResolution(120);
    
    

    //ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofSetBackgroundAuto(true);
    
    
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
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
   // ofSoundUpdate();
    currTime = ofGetElapsedTimeMillis();


}

//--------------------------------------------------------------
void testApp::draw(){
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	ofSetColor(255, 255, 255);
    ofColor c(0,0,0);
 
    ofColor e(255,255,255);

    //openNIDevice.drawImage(640, 0, 640, 480);
   // openNIDevice.drawSkeletons(ofGetWidth()/2-320, ofGetHeight()/2-240, 640, 480);
    
    numUsers = openNIDevice.getNumTrackedUsers();
    ofColor d(255,0,0);
    if(currScene==0){
        ofSetColor(startColor);
        font2.drawString("Touch to start", ofGetWidth()/2-100, 200);
    }
    if(currScene==1){
        
        if(which < 51){
            diffRate = rate[which+1]-rate[which];
            accel = diffRate /96;
            if(diffRate<0){
                if(speed< diffRate){
                    speed=0;
                    which=which+1;
                    //fill(255,0,0);
                }else{
                    speed=speed+accel;
                }
            }else if(diffRate>0){
                if(speed> diffRate){
                    speed=0;
                    which=which+1;
                    //fill(255,0,0);
                }else{
                    speed=speed+accel;
                }
            }
            
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
        font2.drawString(ofToString(which+1961), ofGetWidth()/2-35, 53);
        // font2.drawString(ofToString(rate[which]), ofGetWidth()/2-100, 50);
        lineSpeed=lineSpeed+0.5;
        if(lineSpeed>9){
            lineSpeed=0;
        }
    }

    for (int i = 0; i < numUsers; i++){
        
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(0);
        
        //ofSetColor(255, 255, 255);
        //ofRect(0, 0, ofGetWidth(), ofGetHeight());
       // user.drawMask();
        //current_time=ofGetElapsedTimef();
       // ofTexture & tex = user.getMaskTextureReference();
        //tex.draw(0, 0,1280,960);
       
        if(startFlag){
            keyTime = currTime;
            startFlag=false;
        }
        left_shoulder = user.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition();
        left_elbow = user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition();
        left_hand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
        left_hip = user.getJoint(JOINT_LEFT_HIP).getProjectivePosition();
        left_knee = user.getJoint(JOINT_LEFT_KNEE).getProjectivePosition();
        left_foot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        
        
       
        right_shoulder = user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();
        right_elbow = user.getJoint(JOINT_RIGHT_ELBOW).getProjectivePosition();
        right_hand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
        right_hip = user.getJoint(JOINT_RIGHT_HIP).getProjectivePosition();
        right_knee = user.getJoint(JOINT_RIGHT_KNEE).getProjectivePosition();
        right_foot = user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
        
        head = user.getJoint(JOINT_HEAD).getProjectivePosition();

        float diff_left_hand=left_hand.y-prev_left_hand.y;
        float diff_right_hand=prev_right_hand.y-right_hand.y;
        float diff_left_hip_x=prev_left_hip.x-left_hip.x;
        float diff_left_hip_z=prev_left_hip.z-left_hip.z;
        
        
        if(currTime-keyTime>1000){
        if(left_hand.y<100 || right_hand.y<100){
            currScene=1;
            startColor=d;
        }else{
            startColor=c;
        }
        }
        pathPerson.clear();
        pathPerson.setFillColor(e);
        pathPerson.setStrokeWidth(3);
        pathPerson.setStrokeColor(c);
        pathPerson.moveTo(head.x, head.y+20);
        pathPerson.lineTo(left_shoulder.x,left_shoulder.y);
        pathPerson.lineTo(left_elbow.x,left_elbow.y);
        pathPerson.lineTo(left_hand.x,left_hand.y);
        pathPerson.lineTo(left_hip.x-15,left_hip.y);
        pathPerson.lineTo(left_foot.x,left_foot.y-footSpeed*4);
        pathPerson.lineTo((left_hip.x+right_hip.x)/2,(left_foot.y+right_hip.y)/2);
        pathPerson.lineTo(right_foot.x, right_foot.y+footSpeed*4);
        pathPerson.lineTo(right_hip.x+15,right_hip.y);
        pathPerson.lineTo(right_hand.x,right_hand.y);
        pathPerson.lineTo(right_shoulder.x,right_shoulder.y);
        pathPerson.lineTo(head.x,head.y+20);
        pathPerson.close();
        
        
        pathPerson.draw(ofGetWidth()/2-320,200);
        
        
        if(direction){
        footSpeed = footSpeed+0.5;
            if(footSpeed>10){
                direction=false;
            }
        }else{
        footSpeed=footSpeed-0.5;
            if(footSpeed<0){
                direction=true;
            }
        }
        
        
    }
    

    
    
}


//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}




//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}