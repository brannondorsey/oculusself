#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    ofHideCursor();
    mask.loadImage("oculus_mask.png");
    
    camWidth = 1138;
    camHeight = 640;
    streaming = false;

    std::vector<ofVideoDevice> devices(videoGrabber.listDevices());
    deviceFound = (devices.size() > 0);
    
    if (deviceFound) {
        
//        for (int i = 0; i < devices.size(); i++) {
//            
//            ofVideoDevice device = devices[i];
//            cout<<"Device name: "<<device.deviceName<<endl;
//            cout<<"Device ID: "<<device.id<<endl;
//            cout<<"Device Hardware: "<<device.hardwareName<<endl;
//            cout<<"Device Available: "<<device.bAvailable<<endl;
//            cout<<"device.formats.size(): "<<device.formats.size()<<endl;
//            for (int j = 0; j < device.formats.size(); j++) {
//                cout<<"Width "<<i+1<<":"<<device.formats[i].width<<endl;
//                cout<<"Height "<<i+1<<":"<<device.formats[i].height<<endl;
//            }
//        }
        
        videoGrabber.setDeviceID(0);
        videoGrabber.setDesiredFrameRate(60);
        videoGrabber.initGrabber(camWidth, camHeight);
        videoMirror = new unsigned char[camWidth*camHeight*3];
        mirrorTexture.allocate(camWidth, camHeight, GL_RGB);
        webcamY = ofGetHeight()/2 - videoGrabber.getHeight()/2 + 10;
        xOffset = ofGetWidth()/2 - 600/2;
        cout<<"videoGrabber: "<<videoGrabber.getHeight()/2<<endl;
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
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
void testApp::draw(){
    
    
    ofTranslate(0, -30);
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
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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
