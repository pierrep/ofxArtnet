#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //at first you must specify the Ip address of this machine
    artnet.setup("192.168.0.5"); //make sure the firewall is deactivated at this point
    
    ofSetFrameRate(40);
    fbo.allocate(512, 1, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::exit()
{
    unsigned char buf[512];
    memset(&buf,0,512);

    //turn off lights
    artnet.sendDmx("192.168.0.101", buf, 512);
    artnet.sendDmx("192.168.0.102", buf, 512);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
    //create send buffer by ofFbo
    fbo.begin();
    ofClear(0);
    float colorR = (sin(ofGetElapsedTimeMillis() / 1000.f) / 2.f + 0.5f) * 255.f;
    float colorG = (sin((ofGetElapsedTimeMillis() / 1000.f) + PI / 3.f) / 2.f + 0.5f) * 255.f;
    float colorB = (sin((ofGetElapsedTimeMillis() / 1000.f)  + PI * 2.f / 3.f) / 2.f + 0.5f) * 255.f;
    ofSetColor((int)colorR, (int)colorG, (int)colorB);
    ofDrawRectangle(0, 0, 512, 1);
    fbo.end();
    fbo.readToPixels(testImage.getPixels());

    //with subnet / universe
    //artnet.sendDmx("10.0.0.149", 0xf, 0xf, testImage.getPixels(), 512);
    artnet.sendDmx("192.168.0.101", testImage.getPixels().getData(), 512);

    //write directly into send buffer
    unsigned char buf[512];
    memset(&buf,0,512);
    buf[0] = 255;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    buf[4] = 0;
    buf[5] = 0;
    buf[6] = 0;

    artnet.sendDmx("192.168.0.102", buf, 512);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    float scalex = ofGetWidth() / fbo.getWidth();
    float scaley = ofGetHeight() / fbo.getHeight();
    ofScale(scalex, scaley);
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
