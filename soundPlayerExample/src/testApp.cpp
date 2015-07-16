#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    click.loadSound("sounds/click.mp3");
	foot.loadSound("sounds/f.wav");
    openDoor.loadSound("sounds/o.wav");
    birdL.loadSound("sounds/birdL.mp3");
    birdR.loadSound("sounds/birdR.mp3");
    foot2_2.loadSound("sounds/walk_leaf.wav");
    foot2.loadSound("sounds/water_step.wav");
    rain.loadSound("sounds/rain.wav");
    lobby.loadSound("sounds/lobby.wav");
    laugh.loadSound("sounds/laugh.mp3");
    info.loadSound("sounds/info.wav");
    talk.loadSound("sounds/talk.mp3");
    drum.loadSound("sounds/d.wav");
    sing.loadSound("sounds/sing.mp3");
    applause.loadSound("sounds/applaud.wav");
    drumDrop.loadSound("sounds/stick_drop.wav");
    final.loadSound("sounds/final.mp3");
    
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
	//foot.setMultiPlay(true);
	//openDoor.setMultiPlay(true);
    first.loadImage("images/sc02.jpg");
    first.resize(500, 300);
 	ofSetBackgroundAuto(false);
    
    string str="hello";
    ofBuffer msg(str.c_str(), str.length());
    ofBufferToFile("out.txt", msg);
    

}

//--------------------------------------------------------------
void testApp::update(){
	ofSoundUpdate();
    currTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void testApp::draw(){
    if(level==-1){
        ofBackground(255,255,255);
        ofSetHexColor(0x000000);
        font.drawString("PUT THE HEADSET ON", ofGetWidth()/2-230,ofGetHeight()/2-220);
        if(switchPhone)ofSetHexColor(0xff6347);
        else ofSetHexColor(0x000000);
        font.drawString("DONE", ofGetWidth()/2-70,ofGetHeight()/2);
    }
    
    if(goLevel0)level=0;
    
    if(level==0){
        ofBackground(255,255,255);
        if(switchStart)ofSetHexColor(0xff6347);
        else ofSetHexColor(0x000000);
        
        font.drawString("START", ofGetWidth()/2-90,ofGetHeight()/2);
        ofSetHexColor(0x000000);
        
        fontTitle.drawString("auditory world", ofGetWidth()/2-260,ofGetHeight()/2-220);
        if(switchTuto)ofSetHexColor(0xff6347);
        else ofSetHexColor(0x000000);
        font.drawString("TUTORIAL", ofGetWidth()/2-120,ofGetHeight()/2+90);
        
        
        if(showTuto){
        ofSetColor(255);
        first.draw(250, 400);
        }
    }
    //-------------------------------------------------------------------------------------------------

    
    if(level==1){
	// draw the background colors:
	
        ofBackground(255,255,255);
        ofSetHexColor(0xff6347);
        ofRect(ofGetWidth()/2+posX, ofGetHeight()/2+posY, 50, 50);
        
	//---------------------------------- text:
        ofSetHexColor(0x000000);
        font.drawString("FIND THE EXIT", ofGetWidth()/2-110,50);
        
	//if (foot.getIsPlaying()) ofSetHexColor(0xFF0000);
	//else ofSetHexColor(0x000000);
	//font.drawString("footstep", 50,50);

        ofSetHexColor(0x000000);
        string tempStr = "click to play\npct done: "+ofToString(openDoor.getPosition())+"\nspeed: " + ofToString(openDoor.getSpeed()) + "\nBOOL: " +ofToString(touchDoor) ;
        ofDrawBitmapString(tempStr, 50,ofGetHeight()-50);
  
        if(currTime-keyTime>1000) foot.stop();
        else{
        posX=posX+speedX;
        posY=posY+speedY;
        }
        
    //key point is to list all the posX and posY possiblities and their respective result.
        if (posY>150) stopDown=true;
        else stopDown=false;
        if(posY<-150) stopUp=true;
        else stopUp=false;
        if(posX<-150) stopLeft=true;
        else stopLeft=false;
        if(posX>150 && posY<100) stopRight=true;
        else if(posX>=150 && posY>=100) touchDoor=true;
        else stopRight=false;

    // the main conflict is that openDoor can not play all the time, it needs to stop when it play and restart
    // when it stops playing
        if(touchDoor==true && flag==true){
        foot.stop();
        openDoor.play();
        level=2;
        keyTimeOpenDoor=ofGetElapsedTimeMillis();
        flag=false;
        }
    }
    
    //------------------------------------------------------------------------------------------------
    
    if(level==2){
        keyTimeRain=ofGetElapsedTimeMillis();
        ofBackground(255,255,255);
        float volumeL=(prePosX2-posX2)/200;
        float volumeR=(posX2-prePosX2+200)/200;
        ofSetHexColor(0x000000);
        font.drawString("FOLLOW THE SOUND", ofGetWidth()/2-110,50);
        ofSetHexColor(0xff6347);
        ofRect(ofGetWidth()/2+posX2, ofGetHeight()/2+posY2, 50, 50);
        //does below work?
        if(currTime-keyTimeOpenDoor>2000) openDoor.stop();
        //rain sound 
        if(rainFlag){
            if(keyTimeRain>7000) {
            rain.play();
            rainFlag=false;
            }
        }
        
        //bird sound
        if(playLeft==true && leftFlag==true){
            birdL.play();
            keyTimeBird=ofGetElapsedTimeMillis();
            playRight=false;
            birdR.stop();
            leftFlag=false;          
        }
        // the left and right are written in different way
        if(birdL.getIsPlaying()){
            birdL.setVolume(volumeL+0.1);
            if( prePosX2-posX2>200){
                playRight=true;
                playLeft=false;
                prePosX2=posX;
                countLevel2++;
            }
        }

        if(playRight==true && rightFlag==true){
            birdR.play();
            playLeft=false;
            keyTimeBird=ofGetElapsedTimeMillis();
            birdR.setVolume(volumeR+0.1);
            if(posX2-prePosX2>0){
            playLeft=true;
            playRight=false;
            prePosX2=posX;
            countLevel2++;
            }
            rightFlag=false;
            birdL.stop();
        }
        if(currTime-keyTimeBird>1000){
            leftFlag=true;
            rightFlag=true;
            birdL.stop();
            birdR.stop();
        }
        // keyboard click go and stop
        if(currTime-keyTime2>1000)foot2.stop();
        else {
        posX2=posX2+speedX2;
        posY2=posY2+speedY2;
        }
        ofSetHexColor(0x000000);
        string tempStr = "right: "+ofToString(birdR.getPosition())+"\nleft: " + ofToString(birdL.getPosition()) + "\nBOOL: " +ofToString(leftFlag) + "\nvolumeL"+ofToString(volumeL)+ "\nvolumeR"+ofToString(volumeR)+"\nTime"+ofToString(keyTimeRain);
        ofDrawBitmapString(tempStr, 50,ofGetHeight()-200);
        if(countLevel2==3) {
            delayFlag=true;
            birdL.stop();
            birdR.stop();
            openDoor.play();
            rain.stop();
        }
        if(delayFlag){
            keyTimeDelay=ofGetElapsedTimeMillis();
            delayFlag=false;
        }
        
        if(keyTimeDelay>2000){
            level=3;
           // bgFlag=true;
        }
    }
    //----------------------------------------------------------------------------------------------------
    if(level==3){
        if(writeCount==0){
            write="GO TO THE STAGE";
        }else if(writeCount==1){
            write="PRESS 'P' TO WAVE YOUR HAND";
        }else if(writeCount==2){
         write="CONGRATULATIONS, YOUR JOURNEY IS DONE";
        }
        
        ofBackground(255,255,255);
        ofSetHexColor(0x000000);
        font.drawString(write, ofGetWidth()/2-120,50);
        ofSetHexColor(0xff6347);
        ofRect(ofGetWidth()/2+posX3, ofGetHeight()/2+posY3, 50, 50);
        float volumeLobby= -posY3/100+0.5;
        lobby.setVolume(volumeLobby);
        laughPerson.x=200;
        laughPerson.y=200;
        stage.x=400;
        stage.y=400;
        float distLaugh = ofDist(laughPerson.x, laughPerson.y, ofGetWidth()/2+posX3,ofGetHeight()/2+posY3);
        float distStage = ofDist(stage.x, stage.y, ofGetWidth()/2+posX3, ofGetHeight()/2+posY3);
        
        ofSetHexColor(0x000000);
        string tempStr = "dist: "+ofToString(distLaugh) + "\nlaugh" +ofToString(laugh.getIsPlaying()) + "\ndistStage"+ ofToString(distStage)+"\nINFO" +ofToString(info.getIsPlaying())+"\nFinal" +ofToString(final.getIsPlaying())+"\nCount"+ofToString(countKey)+"\nSingPos"+ofToString(sing.getPosition())+"\nkeyTimeDelay"+ofToString(keyTimeDelay);
        ofDrawBitmapString(tempStr, 50,ofGetHeight()-200);
        
        if(bgFlag) {
        lobby.play();
        bgFlag=false;
        }
        if(laughFlag){
            if(distLaugh<350){
                laugh.play();
                laughFlag=false;
            }else laughFlag=true;
        }
    
        if(distStage<200){
            if(infoFlag){
            writeCount=1;
            info.play();
            startCount=true;
            infoFlag=false;
            }
            if(info.getPosition()>0.98f){
            info.stop();
            infoFlag=true;
            }
        }else infoFlag=true;
        

        if(startCount){
        
        if(countKey==1){
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
            
            
            else{
            
            }
            
            
            }
        }
        
        if(finalFlag2){
        if(currTime-keyTimeDelay>4000&&keyTimeDelay>1000){
            lobby.stop();
            applause.stop();
            drumDrop.stop();
            final.play();
            writeCount=2;
            finalFlag2=false;
            
        }
        }
            
        }
        
        

        if(currTime-keyTime3>1000)foot.stop();
        else{
        posX3=posX3+speedX3;
        posY3=posY3+speedY3;
        }
    }

    if(level==4){
        if(coverFlag==true){
            ofBackground(255);
            coverFlag=false;
            keyTimeStop=currTime;
        }
        ofSetHexColor(0x000000);
        font.drawString("LEVEL3", ofGetWidth()/2-110,50);
    
        ofSetHexColor(0xff6347);
        ofRect(450+posX3, 450+posY3, 10, 10);

        if(currTime-keyTime3>1000){
            
            ofRect(450+posX3, 450+posY3, (currTime-keyTimeStop)/100, (currTime-keyTimeStop)/100);
            //foot2.stop();
        }else{
            posX3=posX3+speedX3;
            posY3=posY3+speedY3;
            ofRect(450+posX3, 450+posY3, 10, 10);
        }
        
    
        
    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
   
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(level==1){
        switch(key){
            case OF_KEY_UP:
                if(!stopUp){
                    keyTime=ofGetElapsedTimeMillis();
                    speedY=-0.5;
                    speedX=0;
                    foot.play();
                    foot.setPosition(0.28f);
                }else{speedY=0;}
                break;
            case OF_KEY_DOWN:
                if(!stopDown){
                    keyTime=ofGetElapsedTimeMillis();
                    speedY=0.5;
                    speedX=0;
                    foot.play();
                    foot.setPosition(0.28f);
                }else{speedY=0;}
                break;
            case OF_KEY_LEFT:
                if(!stopLeft){
                    keyTime=ofGetElapsedTimeMillis();
                    speedX=-0.5;
                    speedY=0;
                    foot.play();
                    foot.setPosition(0.28f);
                }else{speedX=0;}
                break;
            case OF_KEY_RIGHT:
                if(!stopRight){
                    keyTime=ofGetElapsedTimeMillis();
                    speedX=0.5;
                    speedY=0;
                    foot.play();
                    foot.setPosition(0.28f);
                }else{speedX=0;}
                break;
        }
    }
    
    
    
    if(level==2){
        switch(key){
            case OF_KEY_UP:
                
                keyTime2=ofGetElapsedTimeMillis();
                speedY2=-0.5;
                speedX2=0;

                foot2.play();
                foot2.setPosition(0.1f);
                break;
            case OF_KEY_DOWN:
                
                keyTime2=ofGetElapsedTimeMillis();
                speedY2=0.5;
                speedX2=0;
                foot2.play();
                foot2.setPosition(0.1f);
                break;
            case OF_KEY_LEFT:
                
                keyTime2=ofGetElapsedTimeMillis();
                speedX2=-0.5;
                speedY2=0;
                foot2.play();
                foot2.setPosition(0.1f);
                break;
            case OF_KEY_RIGHT:
                
                keyTime2=ofGetElapsedTimeMillis();
                speedX2=0.5;
                speedY2=0;
                foot2.play();
                foot2.setPosition(0.1f);
                break;
        }
    }
    if(level==3){
        switch(key){
            case OF_KEY_UP:
                
                keyTime3=ofGetElapsedTimeMillis();
                speedY3=-0.5;
                speedX3=0;
                
                foot.play();
                foot.setPosition(0.1f);
                break;
            case OF_KEY_DOWN:
                
                keyTime3=ofGetElapsedTimeMillis();
                speedY3=0.5;
                speedX3=0;
                foot.play();
                foot.setPosition(0.1f);
                break;
            case OF_KEY_LEFT:
                
                keyTime3=ofGetElapsedTimeMillis();
                speedX3=-0.5;
                speedY3=0;
                foot.play();
                foot.setPosition(0.1f);
                break;
            case OF_KEY_RIGHT:
                
                keyTime3=ofGetElapsedTimeMillis();
                speedX3=0.5;
                speedY3=0;
                foot.play();
                foot.setPosition(0.1f);
                break;
        
           
        }
        if(startCount){
        if(key=='p'){
            countKey++;
            drum.play();
        }
        }
    }
    
    if(level==4){
        switch(key){
            case OF_KEY_UP:
                keyTimeStop=ofGetElapsedTimeMillis();
                
                keyTime4=ofGetElapsedTimeMillis();
                speedY4=-0.5;
                speedX4=0;
                //foot2.play();
                //foot2.setPosition(0.28f);
                break;
            case OF_KEY_DOWN:
                keyTimeStop=ofGetElapsedTimeMillis();
                keyTime4=ofGetElapsedTimeMillis();
                speedY4=0.5;
                speedX4=0;
                //foot.play();
                //foot.setPosition(0.28f);
                break;
            case OF_KEY_LEFT:
                keyTimeStop=ofGetElapsedTimeMillis();
                keyTime4=ofGetElapsedTimeMillis();
                speedX4=-0.5;
                speedY4=0;
                //foot.play();
                //foot.setPosition(0.28f);
                break;
            case OF_KEY_RIGHT:
                keyTimeStop=ofGetElapsedTimeMillis();
                
                keyTime4=ofGetElapsedTimeMillis();
                speedX4=0.5;
                speedY4=0;
                //foot.play();
                //foot.setPosition(0.28f);
                break;

                
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    if(x<ofGetWidth()/2+80&&x>ofGetWidth()/2-80&&y<ofGetHeight()/2 && y>ofGetHeight()/2-50)switchPhone=true;
    else switchPhone=false;
    
    
    if(x<ofGetWidth()/2+80&&x>ofGetWidth()/2-80&&y<ofGetHeight()/2 && y>ofGetHeight()/2-50) switchStart=true;
    else switchStart=false;
    
    if(x<ofGetWidth()/2+80&&x>ofGetWidth()/2-80&&y<ofGetHeight()/2+80&& y>ofGetHeight()/2+30) switchTuto=true;
    else switchTuto=false;

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    //click sound effect
    if(level==0){
        if(x<ofGetWidth()/2+80&&x>ofGetWidth()/2-80&&y<ofGetHeight()/2 && y>ofGetHeight()/2-50) click.play();
        if(x<ofGetWidth()/2+80&&x>ofGetWidth()/2-80&&y<ofGetHeight()/2+80&& y>ofGetHeight()/2+30) click.play();
    }

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if(level==-1){
        if(x<ofGetWidth()/2+80&&x>ofGetWidth()/2-80&&y<ofGetHeight()/2 && y>ofGetHeight()/2-50) goLevel0=true;
    }else goLevel0=false;
    
    //go from level 0 to level1    
    if(level==0){
        if(x<ofGetWidth()/2+80&&x>ofGetWidth()/2-80&&y<ofGetHeight()/2 && y>ofGetHeight()/2-50) level=1;
        if(x<ofGetWidth()/2+80&&x>ofGetWidth()/2-80&&y<ofGetHeight()/2+80&& y>ofGetHeight()/2+30) showTuto=true;
    }


}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
