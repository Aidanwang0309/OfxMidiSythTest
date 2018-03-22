#pragma once

#include "ofMain.h"
#include "ofxATK.hpp"
#include "ofxMidi.h"

#define SAMPLE_LENGTH 441000  // ten seconds

//multiple inheritance
class ofApp : public ofBaseApp, public ofxMidiListener{

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
//        ofSoundStream soundStreamInput;
    
    void exit();
//    void audioIn(float * input, int bufferSize, int nChannels);
    void audioOut( float* buffer, int bufferSize, int nChannels);
    void newMidiMessage(ofxMidiMessage& message);
    ofxMidiIn midiIn;
    WTSine* modulator;

    WTTriangle triangle;
    WTSquare square;
    CTEnvelope envelope;
    int mostRecentNote;
    
    SoundFile* soundFile;
    SoundPlayer* player;
    SoundFile* soundFile2;
    SoundPlayer* player2;
    
    float playbackSpeed;
    
//    float recording[SAMPLE_LENGTH];
//    int recordingBufferOffset;
//    int playingBufferOffset;
//
//    bool isRecording;
    bool isPlaying;

};
