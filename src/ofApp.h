#pragma once

#include "ofMain.h"
#include "ofxATK.hpp"
#include "ofxMidi.h"
#include "ofXGui.h"

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
    
    void exit();
    void audioOut( float* buffer, int bufferSize, int nChannels);
    void newMidiMessage(ofxMidiMessage& message);
    
    ofxMidiIn midiIn;
    WTSine* modulator;
    Reverb* reverb;

    WTTriangle triangle;
    WTSawtooth sawtooth;
    WTSquare square;
    CTEnvelope envelope;
    int mostRecentNote;
    
    SoundFile* soundFile;
    SoundPlayer* player;
    Recorder* recorder;
    SoundFile* soundFile2;
    SoundPlayer* player2;
    
    float playbackSpeed;
    
    int wave;
    bool isPlaying;
    
    //gui
    ofxPanel gui;
    ofxFloatSlider absorptionFreq;
    ofxFloatSlider absorption;
    ofxFloatSlider dryWet;
    ofxFloatSlider preDelay;
};
