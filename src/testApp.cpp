#include "testApp.h"

#define WIDTH 640
#define HEIGHT 480

#include "vidQueue.h"

//--------------------------------------------------------------
void testApp::setup(){
  ofBackground(20,20,20);
	//ofSetFrameRate(32);

  bDisplayCam = true;
  bFullScreen = false;

  ofSetDataPathRoot("data/");

  vidGrabber.setVerbose(false);
  //vidGrabber.setDeviceID(1);
  vidGrabber.initGrabber(WIDTH, HEIGHT); 


  image.allocate(WIDTH, HEIGHT);
  gimage.allocate(WIDTH, HEIGHT); 
  deplay.init();
  
  
  //vq.init(640, 512);

  vq.init(640, 512); //, 512);

}

//--------------------------------------------------------------
void testApp::update(){
  bool previousStatus = deplay.bTrigger; 
  int previousFaceFound = deplay.iFacesFound;
  vidGrabber.grabFrame();
  
  
  if( vidGrabber.isFrameNew()){
    image.setFromPixels(vidGrabber.getPixels(), WIDTH, HEIGHT); 
    gimage = image; 
    deplay.update(gimage); 
  
  }

  while(deplay.iFacesFound > vq.players.size()){
    vq.pushRandom(); 
  }
  while(deplay.iFacesFound < vq.players.size()){ vq.popRandom();
  }
  
  vq.update();
  
}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetColor(255, 255, 255);
  int width = ofGetWidth(); 
  int height = ofGetHeight(); 
  //vidGrabber.draw(0, 0);
  //gimage.draw(0,0); 
  //deplay.draw();
  
  //gimage.draw(640, 0);
  //player.draw(100, 100, 200, 200);
  vq.draw(width, height);
  
 if(bDisplayCam){ 
  gimage.draw(width - WIDTH/3, height - HEIGHT/4, WIDTH/4, HEIGHT/4);
  deplay.draw(width - WIDTH/3, height - HEIGHT/4, WIDTH/4, HEIGHT/4);
 }
  //skin_classifier.draw(700, 700);
  //skin_classifier.draw(700, 700);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

  switch(key){
    case 'g':
      break;
    case OF_KEY_DOWN:
      bDisplayCam = !bDisplayCam;
      break;
   case OF_KEY_UP:
      bFullScreen = !bFullScreen; 
      ofSetFullscreen(bFullScreen);
      break;

  }
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

  //cout<<"Mouse pressed "<<endl;

}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
