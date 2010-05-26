//-------------------------------------------------------------------------------------
//
// \file detector.cpp
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//
// This class implement face deteciton an sound playing.
// 
// bVariable Coef allows to have different sound level depending
// on the number of people detected.
//
// iVThreshold set threshold per persons
//
//------------------------------------------------------------------------------------ 

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"

#define HAAR_FACE_XML "haarcascade_frontalface_default.xml"

class faceDeplay {

  public:
    bool bVariableCoef; 
    int iVThreshold;
    int iFacesFound;
    int bTrigger;
    int iVupTrigger;
    int iVdnTrigger; 
    int iPlayTrigger;
    int iTriggerThreshold;
    int iStopTrigger;



  faceDeplay(){}

  void init(){
    bVariableCoef = false;
    iVThreshold = 0; 

    //faceTracker = ofxCvHaarFinder(); 
    faceTracker.setup(HAAR_FACE_XML);
    iFacesFound = 0 ; 
    iTriggerThreshold = 10; 
    iVupTrigger = iTriggerThreshold; 
    iVdnTrigger = iTriggerThreshold; 
    iPlayTrigger = iTriggerThreshold; 
    iStopTrigger = iTriggerThreshold; 
    bTrigger = false;


  }
  
  void resetAllTriggers(){
    iVdnTrigger = iTriggerThreshold; 
    iVupTrigger = iTriggerThreshold; 
    iPlayTrigger = iTriggerThreshold; 
    iStopTrigger = iTriggerThreshold; 

  }

  void update(ofxCvGrayscaleImage &image){

    faceTracker.findHaarObjects(image, 100, 640*480, 0); 
    //faceTracker.findHaarObjects(image, 50, 50); //, 640*480, 0); 

    int currentFaces = faceTracker.blobs.size(); 
    int previousFaces = iFacesFound; 
    int acc;

    if ( currentFaces > previousFaces && previousFaces == 0){
      // starts count
      if(--iPlayTrigger <=0){
       resetAllTriggers(); 
       iFacesFound = currentFaces; 
       bTrigger = true; 
       cout<<"Playing"<<endl;
      }
    }
    else if ( currentFaces > previousFaces ){
      // vol up
      if(--iVupTrigger <= 0){
        resetAllTriggers(); 
        iFacesFound = currentFaces; 
        bTrigger = true; 
        // volum up
        cout<<"Vol U"<<endl;
      }
    }
    else if ( currentFaces < previousFaces && currentFaces == 0 ) {
      if(--iStopTrigger <= 0){
        resetAllTriggers(); 
        iFacesFound = currentFaces; 
        bTrigger = false;
        cout<<"Stop"<<endl;
      }
    } else if ( currentFaces < previousFaces) { //  vol down
      if(--iVdnTrigger <= 0){
       resetAllTriggers();
       iFacesFound = currentFaces; 
       bTrigger=true;
       cout<<"Vol D"<<endl;
      }
    } else 
       resetAllTriggers();  
  }

  void draw(float x, float y, float w, float h){
    
    faceTracker.draw(x, y, w, h);
    if(bTrigger)
      ofSetColor(0x00FF00);
    else
      ofSetColor(0xFF0000);
    
    /* ofDrawBitmapString("iPlayTrigger = " + ofToString(iPlayTrigger), x+10, y+10); 
    ofDrawBitmapString("iStopTrigger = " + ofToString(iStopTrigger), x+10, y+30); 
    ofDrawBitmapString("iVdnTrigger  = " + ofToString(iVdnTrigger), x+10, y+60); 
    ofDrawBitmapString("iVupTrigger  = " + ofToString(iVupTrigger), x+10, y+80); 
    ofDrawBitmapString("Faces = " + ofToString(iFacesFound), x+10, y+140);
    ofDrawBitmapString("Playing " + ofToString(bTrigger), x+10, y+110); 
    */
  }
  
  
  private:
  ofxCvHaarFinder faceTracker; 


};


