#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofSetCircleResolution(40);
    ofBackground(0);
    
    player.load("Wax.mp3");
    
    centre = ofPoint(ofGetWidth()*0.5f,ofGetHeight()*0.5f);
    
    scale = 1;
    
    hWaveMult=(ofGetWidth())/float(WAVEFORM_HISTORY);
    vWaveMult=(ofGetHeight())/float(WAVEFORM_HISTORY);

    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    
    freq[0]=0.1f;
    freq[1]=0.1f;
    
    phase[0]=0;
    phase[1]=0;
    
    amplitude[0]=200;
    amplitude[1]=200;
    
    counter[0]=0;
    counter[1]=0;
    
    waveSin[0]=sin(counter[0] + phase[0])*amplitude[0];
    waveSin[1]=sin(counter[1] + phase[1])*amplitude[1];
    
    waveCos[0]=cos(counter[0] + phase[0])*amplitude[0];
    waveCos[1]=cos(counter[1] + phase[1])*amplitude[1];
    
    upPressed=false;
    downPressed=false;
    leftPressed=false;
    rightPressed=false;
    aPressed=false;
    sPressed=false;
    wPressed=false;
    dPressed=false;
    
    
    for (int i=1; i<TAIL_LENGTH; i++) {
        waveHistory[i] = ofVec3f(waveCos[0], waveSin[1], 0);
    }
    for (int i=1; i<WAVEFORM_HISTORY; i++) {
        horWaveHistory[i] = 0;
        vertWaveHistory[i] = 0;
    }
    //player.setVolume(player.getVolume()*0.9f);
    //player.play();
    
    //Will need to setup the aplitudes, phases and the sines here..
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if (upPressed){
        freq[1]=freq[1]+0.005;
    }
    if(downPressed){
        freq[1]=freq[1]-0.005;
    }
    if(leftPressed){
        freq[0]=freq[0]-0.005;
    }
    if(rightPressed){
        freq[0]=freq[0]+0.005;
    }
    if(aPressed){
        phase[0]=phase[0]-0.005;
    }
    if(sPressed){
        phase[1]=phase[1]-0.005;
    }
    if(wPressed){
        phase[1]=phase[1]+0.005;
    }
    if(dPressed){
        phase[0]=phase[0]+0.005;
    }

    counter[0]+=freq[0];
    counter[1]+=freq[1];
    
    waveSin[0]=sin(counter[0] + phase[0])*amplitude[0];
    waveSin[1]=sin(counter[1] + phase[1])*amplitude[1];
    
    waveCos[0]=cos(counter[0] + phase[0])*amplitude[0];
    waveCos[1]=cos(counter[1] + phase[1])*amplitude[1];
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //NOTE HERE, INTERSTING CONCEPT COULD BE THAT WE COULD CREATE INDIVIDUAL OSCILATORS PER FFT BIN
    
    
    float horWave = 0;
    float vertWave = 0;
    
    for (int i=1; i<TAIL_LENGTH; i++){
        waveHistory[i-1]=waveHistory[i];
    }
    
    for (int i=1;i<WAVEFORM_HISTORY;i++){
        horWaveHistory[i-1] = horWaveHistory[i];
        vertWaveHistory[i-1]= vertWaveHistory[i];
    }
    
    //Treating 0 as the horizontal and 1 as vert
    
    horWave = waveCos[0];
    vertWave = waveSin[1];
    
    horWaveHistory[WAVEFORM_HISTORY-1] = horWave;
    vertWaveHistory[WAVEFORM_HISTORY-1] = vertWave;
    waveHistory[TAIL_LENGTH-1] = ofVec3f(horWave, vertWave,0);
    
    ofMesh wave; // declaring a new ofMesh object with which we're drawing the motion path created by summing the vertical and horizontal oscillators
    wave.setMode(OF_PRIMITIVE_LINE_STRIP);
    
    //float scaler = sqrt(pow(0.1f,2) + pow(0.1f,2))/sqrt(pow(freq[0],2) + pow(freq[1],2));
    
    //float scaler = ofMap(<#float value#>, <#float inputMin#>, <#float inputMax#>, <#float outputMin#>, <#float outputMax#>);
    
    //int showTails = TAIL_LENGTH*int(scaler);
    
    for (int i=0; i<TAIL_LENGTH; i++) {
        //cool implement1
        //wave.addColor(ofFloatColor(1.0f,1.0f,1.0f, 1.0f * exp(-i*5/float(TAIL_LENGTH))));//exp(i/float(TAIL_LENGTH))));
          wave.addColor(ofFloatColor(1.0f,1.0f,1.0f, 1.0f - exp(-i*5/float(TAIL_LENGTH))));
        //wave.addColor(ofFloatColor(1.0f,1.0f,1.0f, 1.0f/exp(-i*0.5/float(TAIL_LENGTH))));//exp(i/float(TAIL_LENGTH))));
        //wave.addColor(ofFloatColor(1.0f,1.0f,1.0f, 0.5f + 0.5f*i/float(TAIL_LENGTH)));
        //wave.addColor(ofColor::white);
        wave.addVertex(waveHistory[i]);
    }
    
    ofPushMatrix();
    ofTranslate(centre.x, centre.y, 0);
    ofScale(scale, scale, 0);
    wave.draw();
    //ofSetColor(ofColor::white),
    //ofDrawCircle(horWave, vertWave, 10);
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_UP){
        upPressed=true;
    }
    else if (key == OF_KEY_DOWN){
        downPressed=true;
    }
    else if (key == OF_KEY_RIGHT){
        rightPressed=true;
    }
    else if (key == OF_KEY_LEFT){
        leftPressed=true;
    }
    else if (key == 'w'){
        wPressed=true;
    }
    else if (key == 's'){
        sPressed=true;
    }
    else if (key == 'd'){
        dPressed=true;
    }
    else if (key == 'a'){
        aPressed=true;
    }
    else if (key == ' '){
        freq[1]=freq[0];
    }
    
    else if (key == 'z'){
        phase[1]=phase[0];
    }
  

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if (key == OF_KEY_UP){
        upPressed=false;
    }
    else if (key == OF_KEY_DOWN){
        downPressed=false;
    }
    else if (key == OF_KEY_RIGHT){
        rightPressed=false;
    }
    else if (key == OF_KEY_LEFT){
        leftPressed=false;
    }
    else if (key == 'w'){
        wPressed=false;
    }
    else if (key == 's'){
        sPressed=false;
    }
    else if (key == 'd'){
        dPressed=false;
    }
    else if (key == 'a'){
        aPressed=false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
