#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    soundFile = new SoundFile(ofToDataPath("1.wav"));
    soundFile2 = new SoundFile(ofToDataPath("2.wav"));
    player = new SoundPlayer(soundFile, 0, true);
    player2 = new SoundPlayer(soundFile2, 0, true);
    recorder = new Recorder();
    
    playbackSpeed = 1.0;
    player->setSpeed(playbackSpeed);
    
    wave = 1;
    
    triangle = WTTriangle(200.0);//start the triangle at the current freq
    square = WTSquare(200.0);
    sawtooth = WTSawtooth(200.0);
    
    envelope = CTEnvelope();//create the new envelope
    
    midiIn.listPorts();//list all MIDI ports in console
    midiIn.openPort(0);//my device was on port 3, check your console to see which port you need
    midiIn.addListener(this);//add the listener for the MIDI call
    
    
    reverb = new Reverb();
    
    
    gui.setup();
    gui.add(preDelay.setup("Pre-delay", 20, 0, 200));
    gui.add(absorptionFreq.setup("Absorption Freq", 7000, 50, 10000));
    gui.add(absorption.setup("Absorption", 0.15, 0.0, 1.0));
    gui.add(dryWet.setup("Dry/Wet", 0.5, 0.0, 1.0));
    
    
    ofSoundStreamSetup(2, 0, ATKSettings::sampleRate, ATKSettings::bufferSize, 4);

    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();
    soundFile->draw(200, 20, 400, 180);
    player->draw();//draw the currentPosition
    player2->draw();//draw the currentPosition

    
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::audioOut(float* buffer, int bufferSize, int nChannels){
    
    if (isPlaying) {
    
        for(int i = 0; i < bufferSize; i++){
            float currentSample;
            player->process();
            player2->process();
            envelope.process();
            //progress the oscillator and env by one sample
//
//            square.process();
//            currentSample =
//            square.getSample() * envelope.getValue()
//            +player->getSample()
//            +player2->getSample();
            
            if(wave == 1){
                    square.process();
                    currentSample =
                square.getSample() * envelope.getValue();

            } else if(wave == 2){
                    triangle.process();
                    currentSample =
                triangle.getSample() * envelope.getValue();

            }
            else if( wave==3 ){
                    sawtooth.process();
                    currentSample =
                sawtooth.getSample() * envelope.getValue();
                
            }
    

            reverb->setAbsorption(absorption);
            reverb->setCutOff(absorptionFreq);
            reverb->setDryWet(dryWet);
            reverb->setPreDelay(preDelay);
            
            reverb->process(currentSample);
            currentSample = reverb->getSample()
            +player->getSample()
            +player2->getSample();;
            
            buffer[i*nChannels+0] = currentSample;
            buffer[i*nChannels+1] = currentSample;
        }
    }

}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& message){
    
    if(message.status == MIDI_NOTE_ON){
        mostRecentNote = message.pitch;

        triangle.setFreq(mtof(message.pitch));
        square.setFreq(mtof(message.pitch));
        sawtooth.setFreq(mtof(message.pitch));
        envelope.setGate(1);
        } else if(message.status == MIDI_NOTE_OFF){
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
            player2->setLocation(0);
            player->play();
            player2->play();
            isPlaying = !isPlaying;
            break;
            
        case '1':
            wave = 1;
            break;
        case '2':
            wave = 2;
            break;
        case '3':
            wave = 3;
            break;
            

    }
}

//--------------------------------------------------------------


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
