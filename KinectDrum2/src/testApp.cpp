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
      
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
    font.loadFont("verdana.ttf", 60);
    
    prev_time = 0;
    
    beats.loadSound("sounds/synth.wav");
    
    
    click.loadSound("sounds/click.mp3");
	foot.loadSound("sounds/footsound.wav");
    openDoor.loadSound("sounds/o.wav");
    birdL.loadSound("sounds/birdL.mp3");
    birdR.loadSound("sounds/birdR.mp3");
    foot2_2.loadSound("sounds/walk_leaf.wav");
    foot2.loadSound("sounds/water_step.wav");
    rain.loadSound("sounds/rain.wav");
    lobby.loadSound("sounds/lobby.wav");
    laugh.loadSound("sounds/laugh.mp3");
    info.loadSound("sounds/infoNew.wav");
    talk.loadSound("sounds/talk.mp3");
    drum.loadSound("sounds/don2.wav");
    sing.loadSound("sounds/sing.mp3");
    applause.loadSound("sounds/applaud.wav");
    drumDrop.loadSound("sounds/stick_drop.wav");
    final.loadSound("sounds/intro2.wav");
    intro.loadSound("sounds/introNew.wav");
    drum2.loadSound("sounds/don2.wav");
    
    laugh.setVolume(0.3f);
	foot.setVolume(0.75f);
    foot2.setVolume(0.75f);
    rain.setVolume(0.9f);
    openDoor.setVolume(0.75f);
    birdR.setVolume(0.75f);
    birdL.setVolume(0.75f);
    info.setVolume(0.95f);
    lobby.setVolume(0.8f);
    drum.setVolume(0.8f);
	font.loadFont("alienleagueexpand.ttf", 32);
    fontTitle.loadFont("alienleagueexpand.ttf", 46);
    intro.setVolume(0.9f);
 	ofSetBackgroundAuto(false);
    
  //  string str="hello";
   // ofBuffer msg(str.c_str(), str.length());
    //ofBufferToFile("out.txt", msg);
    
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    ofSoundUpdate();
    
    int holdTime = 300;
    currTime = ofGetElapsedTimeMillis();
    

}

//--------------------------------------------------------------
void testApp::draw(){
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	ofSetColor(255, 255, 255);

    openNIDevice.drawImage(640, 0, 640, 480);
    openNIDevice.drawSkeletons(0, 0, 640, 480);
    
    numUsers = openNIDevice.getNumTrackedUsers();
    
    for (int i = 0; i < numUsers; i++){
        
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(0);
        
        ofSetColor(255, 255, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        user.drawMask();
       
       current_time=ofGetElapsedTimef();
       left_hand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
       right_hand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
       //left_foot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        left_hip = user.getJoint(JOINT_LEFT_HIP).getProjectivePosition();
        
        if(timer>18){
            prev_left_hand=user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
            prev_right_hand=user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
            prev_left_hip= user.getJoint(JOINT_LEFT_HIP).getProjectivePosition();
            prev_right_hand=user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
            timer=0;
            foot_flag=true;
            if(!stopDrumFlag){
            drum_flag=true;
            drum_flag2=true;
            }
        }
        else{
            timer++;
        }
        
        float diff_left_hand=left_hand.y-prev_left_hand.y;
        float diff_right_hand=prev_right_hand.y-right_hand.y;
        float diff_left_hip_x=prev_left_hip.x-left_hip.x;

        float diff_left_hip_z=prev_left_hip.z-left_hip.z;
        
        if(firstDelayFlag){
            firstDelay=currTime;
            firstDelayFlag=false;
        }
        
        if(currTime-firstDelay>2000){
        if(left_hand.y<100 && level==0){
            introOk=false;
            
        }
        }
        
        
        if(startCount==true){
        if(diff_left_hand <-20){
            ofSetColor(0, 255, 255);
            ofRect(100, 100, 100, 100);
            if(drum_flag){
                drum.play();
                drum_flag=false;
                countKey++;
            }
        }
        if(diff_right_hand<-20){
        
            ofSetColor(0, 0, 255);
            ofRect(500, 100, 100, 100);
            if(drum_flag2){
                drum2.play();
                drum_flag2=false;
                countKey++;
            }

        }
        
        }
        if(diff_left_hip_x>30||diff_left_hip_x<-30|| diff_left_hip_z >30||diff_left_hip_z<-30){
            if(level==1){
                ofSetColor(255, 0, 0);
                ofRect(100, 100, 100, 100);
                if(foot_flag){
                foot2.play();
                foot_flag=false;
                }
            }
            if(level==2){
                ofSetColor(100, 100, 0);
                ofRect(100, 100, 100, 100);
                if(foot_flag){
                foot.play();
                foot_flag=false;
                }
            }
        
            
        }
        if(currTime-firstDelay>4000){
        if(level==0){
            if(introFlag&&introOk){
                intro.play();
                introFlag=false;
            }
            if(intro.getPosition()>0.99f){
                intro.stop();
                introFlag=true;
            }
            if(!introOk){
                intro.stop();
                level=1;
            }
            ofSetHexColor(0x000000);
            string tempStr = "x "+ofToString(left_hand.x)+"\ny"+ofToString(left_hand.y)+"\nz"+ofToString(left_hand.z);
            ofDrawBitmapString(tempStr, 50,ofGetHeight()-200);
            
        
            }
        }
        
        if(level==1){
            

            ofPoint door;
            door.x=300;
            door.y=1300;
            float dist=ofDist(left_hip.x, left_hip.z, door.x, door.y);
            
            ofSetColor(255,0,0);
            ofRect(ofGetWidth()/2,ofGetHeight()/2,dist/10,dist/10);
            if(dist<200){
                touch_door=true;
            }
            if(touch_door==true && flag==true){
                foot2.stop();
                openDoor.play();
                level=2;
                keyTimeOpenDoor=ofGetElapsedTimeMillis();
                flag=false;
            }
            
            
            //go closed to lobby,set volume
            float volumeL=dist/250;
            
            if(lobbyFlag){
                lobby.play();
                lobbyFlag=false;
            }
            if(lobby.getPosition()>0.99f){
                lobby.play();
            }
            lobby.setVolume(volumeL);
            
            // rain
            if(currTime-keyTimeOpenDoor>2000) openDoor.stop();
            keyTimeRain=ofGetElapsedTimeMillis();
            if(rainFlag){
                if(keyTimeRain>10000) {
                    rain.play();
                    rainFlag=false;
                }
            }
            
            if(rain.getPosition()>0.95f){
                rain.play();
            }
            if(leftFlag==true){
                //birdL.play();
               // leftFlag=false;
            }
            if(birdL.getIsPlaying()){
               // birdL.setVolume(volumeL+0.1);
            }
            
            if(birdL.getPosition()>0.99l){
                leftFlag=true;
               // birdL.stop();
            }
            
            ofSetHexColor(0x000000);
            string tempStr = "opendoor "+ofToString(openDoor.getPosition())+"\ndist " + ofToString(dist) + "\nBOOLtouchdoor: " +ofToString(touch_door)+"\nx"+ofToString(left_hip.x)+"\ny"+ofToString(left_hip.y)+"\nz"+ofToString(left_hip.z)+"\nTIMER"+ofToString(timer);
            ofDrawBitmapString(tempStr, 50,ofGetHeight()-200);
            

            
        }
        if(level==2){

            
            
            rain.stop();
            
            laughPerson.x=0;
            laughPerson.y=2500;
            stage.x=0;
            stage.y=2500;
            
            float distLaugh = ofDist(laughPerson.x, laughPerson.y, left_hip.x,left_hip.z);
            
            float distStage = ofDist(stage.x, stage.y, left_hip.x,left_hip.z);
            float volumeLobby= distStage/100+0.4;
            lobby.setVolume(volumeLobby);
            
            ofSetHexColor(0x000000);
            string tempStr = "distLaugh: "+ofToString(distLaugh)+"\nvolLobby: "+ofToString(volumeLobby)+"\ndistStage"+ofToString(distStage);
            ofDrawBitmapString(tempStr, 50,ofGetHeight()-200);
            
            if(bgFlag) {
                lobby.play();
                bgFlag=false;
            }
            if(lobby.getPosition()>0.99f){
                lobby.stop();
                bgFlag=true;
            }
            
            if(laughFlag){
                if(distLaugh<300){
                    laugh.play();
                    laughFlag=false;
                }else laughFlag=true;
            }
            
           
                if(infoFlag&&someFlag){
                    if(distStage<300){
                    writeCount=1;
                    info.play();
                    startCount=true;
                    infoFlag=false;
                    }
                }
                if(info.getPosition()>0.98f){
                    info.stop();
                    infoFlag=true;
                    firstInfo=true;
                }
            
            if(firstInfo&&countKey>2){
                someFlag=false;
            }
            
            if(startCount){
                
                if(countKey>2&&firstInfo==true){
                    info.stop();
                    lobby.setVolume(tempVol);
                    if(singFlag){
                        sing.play();
                        beatTime=ofGetElapsedTimeMillis();
                        //talk.play();
                        singFlag=false;
                    }
                }
                if(countKey>1){
                    tempVol=tempVol-0.001;
                    if(tempVol<0){
                        lobby.stop();
                    }
                }
                
                if(finalFlag){
                    if(sing.getPosition()>0.093f){
                        if(countKey>4){
                            sing.stop();
                            applause.play();
                            drumDrop.play();
                            keyTimeDelay=ofGetElapsedTimeMillis();
                            finalFlag=false;
                            finalFlag2=true;
                        }
                    }
                }
                
                if(finalFlag2){
                    if(currTime-keyTimeDelay>4000&&keyTimeDelay>1000){
                        lobby.stop();
                        applause.stop();
                        drumDrop.stop();
                        stopDrumFlag=true;
                        
                        final.play();
                        writeCount=2;
                        finalFlag2=false;
                        
                    }
                }
                
            }
            
            
        }
        
    }
    //level 1 find exit
    
    
   

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