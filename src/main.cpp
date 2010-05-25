
#include "testApp.h"
#include "ofMain.h"


//========================================================================
int main( ){
  
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableArbTex();
	ofSetupOpenGL(1280, 512, OF_FULLSCREEN);


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	ofRunApp(new testApp());

}
