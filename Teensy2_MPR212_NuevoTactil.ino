/*********************************************************
  This is a library for the MPR121 12-channel Capacitive touch sensor

  Designed specifically to work with the MPR121 Breakout in the Adafruit shop
  ----> https://www.adafruit.com/products/

  These sensors use I2C communicate, at least 2 pins are required
  to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

#ifndef _BV2
#define _BV2(bit) (1 << (bit))
#endif

#ifndef _BV3
#define _BV3(bit) (1 << (bit))
#endif

#ifndef _BV4
#define _BV4(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!

Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Adafruit_MPR121 cap3 = Adafruit_MPR121();
Adafruit_MPR121 cap4 = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;

uint16_t lasttouched3 = 0;
uint16_t currtouched3 = 0;

uint16_t lasttouched4 = 0;
uint16_t currtouched4 = 0;

int notes[48] = {76-12, 74-12, 72-12, 71-12, 69-12, 67-12, 65-12, 64-12, 62-12, 60-12, 59-12, 57-12, // Orden correcto en filas.
                 77-12, 75-12, 73-12, 72-12, 70-12, 68-12, 66-12, 65-12, 63-12, 61-12, 60-12, 58-12,  // OK
                 83-12, 81-12, 79-12, 78-12, 76-12, 74-12, 72-12, 71-12, 69-12, 67-12, 66-12, 64-12,  // 79, 80, 82, 84, 73, 74, 75, 76, 77, 78, 79, 80,
                 84-12, 82-12, 80-12, 79-12, 77-12, 75-12, 73-12, 72-12, 70-12, 68-12, 67-12, 65-12}; // OK

int channel = 4;
               
/// POTS

const int N_POTS = 1;                                    //* total numbers of pots (slide & rotary)
const int POT_ARDUINO_PIN[N_POTS] = {A6};  //* pins of each pot connected straight to the Arduino

int potCState[N_POTS] = { 0 };  // Current state of the pot
int potPState[N_POTS] = { 0 };  // Previous state of the pot
int potVar = 0;                 // Difference between the current and previous state of the pot

int pbCState = 352;
int pbPState = 352;
int pbVar = 0;

int midiCState[N_POTS] = { 0 };  // Current state of the midi value
int midiPState[N_POTS] = { 0 };  // Previous state of the midi value

const int TIMEOUT = 300;       //* Amount of time the potentiometer will be read after it exceeds the varThreshold
const int varThreshold = 100;  //* Threshold for the potentiometer signal variation
boolean potMoving = true;      // If the potentiometer is moving
boolean pbMoving = true;
unsigned long PTime[N_POTS] = { 0 };  // Previously stored time
unsigned long timer[N_POTS] = { 0 };  // Stores the time that has elapsed since the timer was reset
unsigned long PbTime = 0;             // Previously stored time pitch bend
unsigned long pbtimer = 0;            // Stores the time that has elapsed since the timer was reset pitch bend

byte cc[N_POTS] = {1};  // 1 para MODWHEEL 7 volumen
byte midiCh[N_POTS] = {channel};          // 0x10, 1

void setup() {
  //Serial.begin(115200);

  //MIDI.begin(MIDI_CHANNEL_OMNI);
/*
  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
*/
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 1 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  if (!cap2.begin(0x5B)) {
    Serial.println("MPR121 2 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 2 found!");

  if (!cap3.begin(0x5C)) {
    Serial.println("MPR121 3 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 3 found!");

  if (!cap4.begin(0x5D)) {
    Serial.println("MPR121 4 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 4 found!");
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  currtouched2 = cap2.touched();
  currtouched3 = cap3.touched();
  currtouched4 = cap4.touched();

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i + 12); Serial.println(" touched");
      usbMIDI.sendNoteOn(notes[i], 127, channel);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i + 12); Serial.println(" released");
      usbMIDI.sendNoteOn(notes[i], 0, channel);
    }
  }

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched2 & _BV2(i)) && !(lasttouched2 & _BV2(i)) ) {
      Serial.print(i + 23); Serial.println(" touched");
      usbMIDI.sendNoteOn(notes[i+12], 127, channel);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched2 & _BV2(i)) && (lasttouched2 & _BV2(i)) ) {
      Serial.print(i + 23); Serial.println(" released");
      usbMIDI.sendNoteOn(notes[i+12], 0, channel);
    }
  }

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched3 & _BV3(i)) && !(lasttouched3 & _BV3(i)) ) {
      Serial.print(i + 35); Serial.println(" touched");
      usbMIDI.sendNoteOn(notes[i+24], 127, channel);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched3 & _BV3(i)) && (lasttouched3 & _BV3(i)) ) {
      Serial.print(i + 35); Serial.println(" released");
      usbMIDI.sendNoteOn(notes[i+24], 0, channel);
    }
  }

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched4 & _BV4(i)) && !(lasttouched4 & _BV4(i)) ) {
      Serial.print(i + 47); Serial.println(" touched");
      usbMIDI.sendNoteOn(notes[i+36], 127, channel);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched4 & _BV4(i)) && (lasttouched4 & _BV4(i)) ) {
      Serial.print(i + 47); Serial.println(" released");
      usbMIDI.sendNoteOn(notes[i+36], 0, channel);
    }
  }
  // reset our state
  lasttouched = currtouched;
  lasttouched2 = currtouched2;
  lasttouched3 = currtouched3;
  lasttouched4 = currtouched4;

  //potentiometers();

  // comment out this line for detailed data from the sensor!
  return;

  // debugging info, whatddddd
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();

  // put a delay so it isn't overwhelming
  delay(100);
}


void potentiometers() {


  for (int i = 0; i < N_POTS; i++) {  // Loops through all the potentiometers

    potCState[i] = analogRead(POT_ARDUINO_PIN[i]);  // reads the pins from arduino

    midiCState[i] = map(potCState[i], 0, 1023/4, 127, 0);  //4095 Maps the reading of the potCState to a value usable in midi

    potVar = abs(potCState[i] - potPState[i]);  // Calculates the absolute value between the difference between the current and previous state of the pot

    if (potVar > varThreshold) {  // Opens the gate if the potentiometer variation is greater than the threshold
      PTime[i] = millis();        // Stores the previous time
    }

    timer[i] = millis() - PTime[i];  // Resets the timer 11000 - 11000 = 0ms

    if (timer[i] < TIMEOUT) {  // If the timer is less than the maximum allowed time it means that the potentiometer is still moving
      potMoving = true;
    } else {
      potMoving = false;
    }

    if (potMoving == true) {  // If the potentiometer is still moving, send the change control
      if (midiPState[i] != midiCState[i]) {
        if (midiCState[i] < 0) {
          midiCState[i] = 0;
        }
        if (midiCState[i] > 127) {
          midiCState[i] = 127;
        }
        usbMIDI.sendControlChange(cc[i], midiCState[i], midiCh[i]);
        potPState[i] = potCState[i];  // Stores the current reading of the potentiometer to compare with the next
        midiPState[i] = midiCState[i];
        Serial.print(midiCState[i]);
        Serial.print(" - ");
        Serial.println(potCState[i]);
      }
    }
  }
}
