// Original Roland CR-5000 Midi Sync and Midi Control Rev 02. 12-14 by Travis Thatcher
// Simplified for MIDI note to positive going triggers only using all 12 digital pins by Pieter Vochten (May-2016)
// https://www.circuitbenders.co.uk/forum/index.php?topic=2656.0


// Include the MIDI library (make sure it is installed in your Arduino IDE!
// Downloadable at: http://playground.arduino.cc/Main/MIDILibrary
#include "MIDI.h"
MIDI_CREATE_DEFAULT_INSTANCE(); // Create a default, nameless MIDI instance for handling MIDI events

#define NUMTRIGS 12 // This code will use all 12 digital output pins

#define TRIGGER_TIME 10  // this defines the trigger length in ms (edit as needed)

// This code uses 12 pins starting from Pin2 up to Pin13
// Pin 13 can be used for debugging because on most Arduino boards, it is connected to a built-in LED
int triggerPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};   // Create an array of 12 integers resembling the Pin numbers
// Create an array in which the hold times (timestamps in ms) for every trigger PIN will be stored (initially all set to zero)
int triggerTimes[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// Create an array containing the trigger state for every trigger PIN (initially all set to LOW, idle)
// Triggers will be set to HIGH (= +5v)
// Replace LOW / HIGH throughout the whole code to create inverted, negative going triggers (+5v idle, 0v triggers)
int triggerStates[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

int currentTime = 0;
int octave = 1;

byte incomingByte;
byte velocity;

void setup() {    // The following code is executed once for initialization
  //MIDI.turnThruOff();
  MIDI.turnThruOn();
  MIDI.begin(MIDI_CHANNEL_OMNI);  // this sets the midi channel, (0)= midi channel 1, (1)= midi channel 2 etc... or MIDI_CHANNEL_OMNI

  // Specify the octave; The octave can range from -2 to 8, depending on your needs.
  // Pins are assigned in ascending order per semi tone starting with C of the specified octave for Pin2
  // For example: if set to 1 --> Pin2 = C1, Pin3 = C#1, Pin4 = D1 etc. (standard for most drum sequencers)
  octave = 1;

  // Initialize the output pins. The Arduino uses + triggers (5v) so we set their initial state to Low (0v)

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // The built-in MIDI library is capable of filtering different types of MIDI events such as notes, control, sync...
  // This line specifies how to handle MIDI Note ON messages, referring to the function "void HandleNoteOn(..."
  MIDI.setHandleNoteOn(HandleNoteOn); // Set the handler for NoteOn events
}

void loop() {     // The following code is executed continuously after the setup
  MIDI.read();
  // Read in the current timestamp in ms and store it in currentTime
  currentTime = millis();

  // Check the state of the 12 triggers in a loop
  for (int i = 0; i < NUMTRIGS; i++) {  // "While i = 0 to i < 12 (number of triggers), do... for Array Position[i]" --> running through the arrays
    // For every HIGH trigger: compare its timestamp with the currentTime
    // Set the trigger state to LOW if the difference exceeds the specified TRIGGER_TIME
    if (triggerStates[i] == HIGH) {
      if (currentTime - triggerTimes[i] > TRIGGER_TIME) {
        digitalWrite(triggerPins[i], LOW);
        triggerStates[i] = LOW;
      }
    }
  }
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) {  // this code is executed when MIDI notes are received
  // triggers!
  for (int i = 0; i < NUMTRIGS; i++) {
    if (pitch - 24 - (12 * octave) == i) {  // Calculate the PIN to match the incoming Pitch and the specified octave by subtracting a plural of "12"
      digitalWrite(triggerPins[i], HIGH);   // Set the actual matching PIN to HIGH (=> trigger active)
      triggerStates[i] = HIGH;              // Save the triggerState for this PIN in the triggerStates array
      triggerTimes[i] = currentTime;        // Save the current timestamp for this PIN in the triggerTimes array
    }
  }
}
