#pragma once

#include "ofMain.h"

#define WAVEFORM_HISTORY 800
#define TAIL_LENGTH 300

class ofApp : public ofBaseApp{

public:
    
    void setup();
    void update();
	void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofVec3f waveHistory [TAIL_LENGTH];
    
    float horWaveHistory [WAVEFORM_HISTORY];
    float vertWaveHistory [WAVEFORM_HISTORY];
    
    ofPoint centre;
    float scale;
    
    float hWaveMult;
    float vWaveMult;
    
    ofSoundPlayer player;
    
    
    //The settings for out x and y oscilators. Vectors used. Not actually sure we need these
    
    /*
    ofVec2f freq [2];
    ofVec2f waveSin[2];
    ofVec2f waveCos[2];
    ofVec2f amplitude[2];
    ofVec2f phase[2];
    ofVec2f counter[2];
    */
    float freq [2];
    float waveSin [2];
    float waveCos [2];
    float amplitude [2];
    float phase [2];
    double counter [2];
    
    
    bool upPressed;
    bool downPressed;
    bool leftPressed;
    bool rightPressed;
    bool aPressed;
    bool sPressed;
    bool wPressed;
    bool dPressed;
		
};
