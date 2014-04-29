#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofHideCursor();
    
    fontSize = 32;
    noWebcamMessage = "No webcam detected.";
    font.loadFont("Lato-Lig.ttf", fontSize);
    noWebcamMessageBounds = font.getStringBoundingBox(noWebcamMessage, 0, 0);
    
    mask.loadImage("oculus_mask.png");
    
    camWidth = 1138;
    camHeight = 640;
    streaming = false;

    std::vector<ofVideoDevice> devices(videoGrabber.listDevices());
    deviceFound = (devices.size() > 0);
    
    if (deviceFound) {
        videoGrabber.setDeviceID(0);
        videoGrabber.setDesiredFrameRate(60);
        videoGrabber.initGrabber(camWidth, camHeight);
        videoMirror = new unsigned char[camWidth*camHeight*3];
        mirrorTexture.allocate(camWidth, camHeight, GL_RGB);
        webcamY = ofGetHeight()/2 - videoGrabber.getHeight()/2 + 10;
        xOffset = ofGetWidth()/2 - 800/2;
        cout<<"videoGrabber: "<<videoGrabber.getHeight()/2<<endl;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (deviceFound) {
        videoGrabber.update();
        if (videoGrabber.isInitialized() &&
            videoGrabber.isFrameNew()) {
            if (!streaming) streaming = true;
            unsigned char * pixels = videoGrabber.getPixels();
            for (int i = 0; i < camHeight; i++) {
                for (int j = 0; j < camWidth*3; j+=3) {
                    // pixel number
                    int pix1 = (i*camWidth*3) + j;
                    int pix2 = (i*camWidth*3) + (j+1);
                    int pix3 = (i*camWidth*3) + (j+2);
                    // mirror pixel number
                    int mir1 = (i*camWidth*3)+1 * (camWidth*3 - j-3);
                    int mir2 = (i*camWidth*3)+1 * (camWidth*3 - j-2);
                    int mir3 = (i*camWidth*3)+1 * (camWidth*3 - j-1);
                    // swap pixels
                    videoMirror[pix1] = pixels[mir1];
                    videoMirror[pix2] = pixels[mir2];
                    videoMirror[pix3] = pixels[mir3];
                }
            }
            mirrorTexture.loadData(videoMirror, camWidth, camHeight, GL_RGB);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (deviceFound) {
        if (videoGrabber.isInitialized() &&
            streaming) {
            
            unsigned char * pixels = videoGrabber.getPixels();
            mirrorTexture.drawSubsection(40,
                                         webcamY,
                                         ofGetWidth()/2,
                                         camHeight,
                                         xOffset,
                                         0,
                                         mirrorTexture.getWidth()/2,
                                         camHeight);

            mirrorTexture.drawSubsection(ofGetWidth()/2,
                                         webcamY,
                                         ofGetWidth()/2,
                                         camHeight,
                                         xOffset + 80,
                                         0,
                                         mirrorTexture.getWidth()/2,
                                         camHeight);
        }
        mask.draw(0, 0, ofGetWidth(), ofGetHeight());
        
    } else {
        ofSetColor(0);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(255);
        font.drawString(noWebcamMessage, ofGetWidth()/2 - noWebcamMessageBounds.width/2, ofGetHeight()/2 + fontSize/2);
    }
    
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
