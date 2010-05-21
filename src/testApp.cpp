#include "testApp.h"

#define WIDTH 640
#define HEIGHT 480

#include "vidQueue.h"

//--------------------------------------------------------------
void testApp::setup(){
  ofBackground(20,20,20);
	//ofSetFrameRate(32);


  ofSetDataPathRoot("data/");

  vidGrabber.setVerbose(false);
  //vidGrabber.setDeviceID(1);
  vidGrabber.initGrabber(WIDTH, HEIGHT); 


  image.allocate(WIDTH, HEIGHT);
  gimage.allocate(WIDTH, HEIGHT); 
  deplay.init();
  
  
  vq.init(640, 512);

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
  //vidGrabber.draw(0, 0);
  //gimage.draw(0,0); 
  //deplay.draw();
  
  gimage.draw(640, 0);
  deplay.draw(640, 0);
  //player.draw(100, 100, 200, 200);
  vq.draw();
  //skin_classifier.draw(700, 700);
  //skin_classifier.draw(700, 700);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

  switch(key){
    case 'g':
      break;
    case OF_KEY_UP:
      break;
    case OF_KEY_DOWN:
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
