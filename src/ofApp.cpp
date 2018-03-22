#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    soundFile = new SoundFile(ofToDataPath("1.wav"));
    player = new SoundPlayer(soundFile, 0, true);
    
    playbackSpeed = 1.0;
    player->setSpeed(playbackSpeed);
    
    
    
    triangle = WTTriangle(200.0);//start the triangle at the current freq
    envelope = CTEnvelope();//create the new envelope
    
    midiIn.listPorts();//list all MIDI ports in console
    midiIn.openPort(0);//my device was on port 3, check your console to see which port you need
    midiIn.addListener(this);//add the listener for the MIDI call
    
//    soundStreamInput.printDeviceList();
//    soundStreamInput.setup(this, 0, 1, 44100, ATKSettings::bufferSize, 4);

    ofSoundStreamSetup(2, 0, ATKSettings::sampleRate, ATKSettings::bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    soundFile->draw(20, 20, 400, 180);
    player->draw();//draw the currentPosition
    
    
}

//--------------------------------------------------------------
//void ofApp::audioIn(float * input, int bufferSize, int nChannels){
//    if(isRecording){
//        for (int i = 0; i < bufferSize; i++){
//            recording[i+recordingBufferOffset*bufferSize] = input[i];
//        }
//        recordingBufferOffset++;
//    }
//}
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    
    if (isPlaying) {
    
        for(int i = 0; i < bufferSize; i++){
            
            player->process();
            triangle.process();envelope.process();
            //progress the oscillator and env by one sample
            float currentSample = triangle.getSample() * envelope.getValue()+player->getSample();
            //        +recording[i + playingBufferOffset*bufferSize];
            
            buffer[i*nChannels+0] = currentSample;
            buffer[i*nChannels+1] = currentSample;
        }
        //        playingBufferOffset++;
    }

}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& message){
    
    if(message.status == MIDI_NOTE_ON){
        mostRecentNote = message.pitch;
        triangle.setFreq(mtof(message.pitch));
        envelope.setGate(1);
    }else if(message.status == MIDI_NOTE_OFF){
        if(message.pitch == mostRecentNote){
            envelope.setGate(0);
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case OF_KEY_DOWN:
            playbackSpeed -= 0.1;
            player->setSpeed(playbackSpeed);
            break;
        case OF_KEY_UP:
            playbackSpeed += 0.1;
            player->setSpeed(playbackSpeed);
            break;
        case ' ':
            player->setLocation(0);
            player->play();
            isPlaying = !isPlaying;
            break;
//        case 'r':
//            if(isRecording) {
//                isRecording = false;
//                soundStreamInput.stop();
//            }
//            else{
//                isRecording = true;
//                soundStreamInput.start();
//                recordingBufferOffset = 0;
//            }
//            break;
//        case 'p':
//            if( key == 'p' ){
//                if(isPlaying) {
//                    isPlaying = false;
//                    soundStreamOutput.stop();
//                }
//                else{
//                    isPlaying = true;
//                    soundStreamOutput.start();
//                    playingBufferOffset = 0;
//                }
//            }
//            break;
    }
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
