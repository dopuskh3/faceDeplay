//-------------------------------------------------------------------------------------
//
// \file testApp.h
// \brief
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "faceDeplay.h"
#include "ofxOpenCv.h"
#include "vidQueue.h"

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

		ofVideoGrabber vidGrabber;
        ofxCvColorImage image; 
        ofxCvGrayscaleImage gimage;


        faceDeplay deplay;
    ofVideoPlayer player;
    vidQueue vq; 
    bool bDisplayCam; 
    bool bFullScreen; 

};

#endif
