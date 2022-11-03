/*
  EXAMPLE - MUX Sensing

  With this sample code, you can make 16 single piezo pads with a 4067.
  https://github.com/RyoKosaka/HelloDrum-arduino-Library
*/

///////////////////////////////   SETTING VALUE   ///////////////////////////////////

//Determine the setting value.
//By changing the number in this array you can set sensitivity, threshold and so on.

#define Drum_map 0 //0-ADD2, 1-EZD2

short countdown[32] = {0};
short pos[32] = {0};
short mincount = 500;
short maxcount = 1500;

short channel = 2;

// Potenciómetros. Uno para la octava.

short potpins[2] = {A14, A2};
short potvalue[2] = {0};
short potposnow[2] = {0};
short potposlast[2] = {0};
short fired[2] = {0};
short changed[2] = {0};
short oct = -24;
short monomode = 0;

byte Note[2][16] = {
  /* _ Hihat tip
    |     _ Kick
    |    |    _ Snare Open hit
    |    |   |    _ Snare SideStick
    |    |   |   |    _ Tom1
    |    |   |   |   |    _ Tom2
    |    |   |   |   |   |    _ Tom3
    |    |   |   |   |   |   |    _ Tom4
    |    |   |   |   |   |   |   |    _ Extra1
    |    |   |   |   |   |   |   |   |    _ Extra2
    |    |   |   |   |   |   |   |   |   |    _ Cym1
    |    |   |   |   |   |   |   |   |   |   |    _ Cym2
    |    |   |   |   |   |   |   |   |   |   |   |    _ Cym3
    |    |   |   |   |   |   |   |   |   |   |   |   |    _ Cym4
    |    |   |   |   |   |   |   |   |   |   |   |   |   |   _ Ride tip
    |    |   |   |   |   |   |   |   |   |   |   |   |   |  |    _ Ride bell
    |    |   |   |   |   |   |   |   |   |   |   |   |   |  |   |       BANK */
  { 84 + oct, 83 + oct, 81 + oct, 79 + oct, 77 + oct, 76 + oct, 74 + oct,
    72 + oct, 71 + oct, 69 + oct, 67 + oct, 65 + oct, 64 + oct, 62 + oct,
    60 + oct, 59 + oct
  },
  { 82 + oct, 80 + oct, 78 + oct, 75 + oct, 73 + oct, 70 + oct, 68 + oct,
    66 + oct, 63 + oct, 61 + oct, 86 + oct, 88 + oct, 85 + oct, 87 + oct,
    51 + oct, 23 + oct
  }
};

int PAD1[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][0]
};

int PAD2[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][1]
};

int PAD3[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][2]
};

int PAD4[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][3]
};

int PAD5[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][4]
};

int PAD6[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][5]
};

int PAD7[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][6]
};

int PAD8[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][7]
};

int PAD9[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][8]
};

int PAD10[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][9]
};

int PAD11[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][10]
};

int PAD12[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][11]
};

int PAD13[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][12]
};

int PAD14[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][13]
};

int PAD15[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][14]
};

int PAD16[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[Drum_map][15]
};

int PAD17[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][0]
};

int PAD18[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][1]
};
int PAD19[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][2]
};
int PAD20[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][3]
};
int PAD21[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][4]
};
int PAD22[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][5]
};
int PAD23[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][6]
};
int PAD24[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][7]
};
int PAD25[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][8]
};
int PAD26[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][9]
};
int PAD27[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][10]
};
int PAD28[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][11]
};
int PAD29[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][12]
};
int PAD30[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][13]
};
int PAD31[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][14]
};
int PAD32[5] = {
  130, //sensitivity
  50,  //threshold
  10,  //scan time
  30,  //mask time
  Note[1][15]
};

/////////////////////////////////////////////////////////////////////////////////////

#include "hellodrum.h"

//Using MIDI Library. If you want to use USB-MIDI, comment out the next two lines.
#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

//Uncomment the next two lines for using USB-MIDI with atmega32u4 or Teensy
//#include <USB-MIDI.h>
//USBMIDI_CREATE_DEFAULT_INSTANCE();

/*
  Mux Breakout ----------- Arduino
  S0 ------------------- 2
  S1 ------------------- 3
  S2 ------------------- 4
  S2 ------------------- 5
  Z -------------------- A0
*/
//Define MUX Pins
HelloDrumMUX_4067 mux(20, 21, 22, 23, 0); //D2, D3, D4, D5, A0, 20, 21, 22, 23, 0
HelloDrumMUX_4067 mux2(12, 17, 18, 19, 1); //D2, D3, D4, D5, A1

//or use two 4501s
//HelloDrumMUX_4051 mux1(2,3,4,0); //D2, D3, D4, A0
//HelloDrumMUX_4051 mux2(5,6,7,1); //D5, D6, D7, A1

//name your pad and define mux pin
HelloDrum pad1(0);
HelloDrum pad2(1);
HelloDrum pad3(2);
HelloDrum pad4(3);
HelloDrum pad5(4);
HelloDrum pad6(5);
HelloDrum pad7(6);
HelloDrum pad8(7);
HelloDrum pad9(8);
HelloDrum pad10(9);
HelloDrum pad11(10);
HelloDrum pad12(11);
HelloDrum pad13(12);
HelloDrum pad14(13);
HelloDrum pad15(14);
HelloDrum pad16(15);
HelloDrum pad17(16); //0
HelloDrum pad18(17);
HelloDrum pad19(18);
HelloDrum pad20(19);
HelloDrum pad21(20);
HelloDrum pad22(21);
HelloDrum pad23(22);
HelloDrum pad24(23);
HelloDrum pad25(24);
HelloDrum pad26(25); //9
HelloDrum pad27(26);
HelloDrum pad28(27);
HelloDrum pad29(28);
HelloDrum pad30(29);
HelloDrum pad31(30); //14
HelloDrum pad32(31); //15

void setup()
{
  // Por lo menos 3 potenciómetros : Forma de onda, filtro, y morph.
  MIDI.begin(1);
  //Serial.begin(9600);
  delay(2000);
  if (monomode == 0) {
    MIDI.sendControlChange(0x53, 127, 1); // mono
    monomode = 1;
  }
}
void loop()
{
  mux.scan();
  mux2.scan();

  pad1.singlePiezoMUX(PAD1[0], PAD1[1], PAD1[2], PAD1[3]);
  pad2.singlePiezoMUX(PAD2[0], PAD2[1], PAD2[2], PAD2[3]);
  pad3.singlePiezoMUX(PAD3[0], PAD3[1], PAD3[2], PAD3[3]);
  pad4.singlePiezoMUX(PAD4[0], PAD4[1], PAD4[2], PAD4[3]);
  pad5.singlePiezoMUX(PAD5[0], PAD5[1], PAD5[2], PAD5[3]);
  pad6.singlePiezoMUX(PAD6[0], PAD6[1], PAD6[2], PAD6[3]);
  pad7.singlePiezoMUX(PAD7[0], PAD7[1], PAD7[2], PAD7[3]);
  pad8.singlePiezoMUX(PAD8[0], PAD8[1], PAD8[2], PAD8[3]);
  pad9.singlePiezoMUX(PAD9[0], PAD9[1], PAD9[2], PAD9[3]);
  pad10.singlePiezoMUX(PAD10[0], PAD10[1], PAD10[2], PAD10[3]);
  pad11.singlePiezoMUX(PAD11[0], PAD11[1], PAD11[2], PAD11[3]);
  pad12.singlePiezoMUX(PAD12[0], PAD12[1], PAD12[2], PAD12[3]);
  pad13.singlePiezoMUX(PAD13[0], PAD13[1], PAD13[2], PAD13[3]);
  pad14.singlePiezoMUX(PAD14[0], PAD14[1], PAD14[2], PAD14[3]);
  pad15.singlePiezoMUX(PAD15[0], PAD15[1], PAD15[2], PAD15[3]);
  pad16.singlePiezoMUX(PAD16[0], PAD16[1], PAD16[2], PAD16[3]);
  pad17.singlePiezoMUX(PAD17[0], PAD17[1], PAD17[2], PAD17[3]);
  pad18.singlePiezoMUX(PAD18[0], PAD18[1], PAD18[2], PAD18[3]);
  pad19.singlePiezoMUX(PAD19[0], PAD19[1], PAD19[2], PAD19[3]);
  pad20.singlePiezoMUX(PAD20[0], PAD20[1], PAD20[2], PAD20[3]);
  pad21.singlePiezoMUX(PAD21[0], PAD21[1], PAD21[2], PAD21[3]);
  pad22.singlePiezoMUX(PAD22[0], PAD22[1], PAD22[2], PAD22[3]);
  pad23.singlePiezoMUX(PAD23[0], PAD23[1], PAD23[2], PAD23[3]);
  pad24.singlePiezoMUX(PAD24[0], PAD24[1], PAD24[2], PAD24[3]);
  pad25.singlePiezoMUX(PAD25[0], PAD25[1], PAD25[2], PAD25[3]);
  pad26.singlePiezoMUX(PAD26[0], PAD26[1], PAD26[2], PAD26[3]);
  pad27.singlePiezoMUX(PAD27[0], PAD27[1], PAD27[2], PAD27[3]);
  pad28.singlePiezoMUX(PAD28[0], PAD28[1], PAD28[2], PAD28[3]);
  pad29.singlePiezoMUX(PAD29[0], PAD29[1], PAD29[2], PAD29[3]);
  pad30.singlePiezoMUX(PAD30[0], PAD30[1], PAD30[2], PAD30[3]);
  //pad31.singlePiezoMUX(PAD31[0], PAD31[1], PAD31[2], PAD31[3]);
  //pad32.singlePiezoMUX(PAD32[0], PAD32[1], PAD32[2], PAD32[3]);

  if (pad1.hit == true && pos[0] == 1)
  {
    MIDI.sendNoteOn(PAD1[4], 0, 1);
    MIDI.sendNoteOn(PAD1[4], pad1.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD1[4], 0, channel);
    usbMIDI.sendNoteOn(PAD1[4], pad1.velocity, channel); //(note, velocity, channel)
    countdown[0] = map(pad1.velocity, 0, 127, mincount, maxcount);
  }

  if (pad1.hit == true && pos[0] == 0)
  {
    MIDI.sendNoteOn(PAD1[4], pad1.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD1[4], pad1.velocity, channel); //(note, velocity, channel)
    countdown[0] = map(pad1.velocity, 0, 127, mincount, maxcount);
    pos[0] = 1;
  }

  if (pad2.hit == true && pos[1] == 1)
  {
    MIDI.sendNoteOn(PAD2[4], 0, 1);
    MIDI.sendNoteOn(PAD2[4], pad2.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD2[4], 0, channel);
    usbMIDI.sendNoteOn(PAD2[4], pad2.velocity, channel); //(note, velocity, channel)
    countdown[1] = map(pad2.velocity, 0, 127, mincount, maxcount);
  }

  if (pad2.hit == true && pos[1] == 0)
  {
    MIDI.sendNoteOn(PAD2[4], pad2.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD2[4], pad2.velocity, channel); //(note, velocity, channel)
    countdown[1] = map(pad2.velocity, 0, 127, mincount, maxcount);
    pos[1] = 1;
  }

  if (pad3.hit == true && pos[2] == 1)
  {
    MIDI.sendNoteOn(PAD3[4], 0, 1);
    MIDI.sendNoteOn(PAD3[4], pad3.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD3[4], 0, channel);
    usbMIDI.sendNoteOn(PAD3[4], pad3.velocity, channel); //(note, velocity, channel)
    countdown[2] = map(pad3.velocity, 0, 127, mincount, maxcount);
  }

  if (pad3.hit == true && pos[2] == 0)
  {
    MIDI.sendNoteOn(PAD3[4], pad3.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD3[4], pad3.velocity, channel); //(note, velocity, channel)
    countdown[2] = map(pad3.velocity, 0, 127, mincount, maxcount);
    pos[2] = 1;
  }

  if (pad4.hit == true && pos[3] == 1)
  {
    MIDI.sendNoteOn(PAD4[4], 0, 1);
    MIDI.sendNoteOn(PAD4[4], pad4.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD4[4], 0, channel);
    usbMIDI.sendNoteOn(PAD4[4], pad4.velocity, channel); //(note, velocity, channel)
    countdown[3] = map(pad4.velocity, 0, 127, mincount, maxcount);
  }

  if (pad4.hit == true && pos[3] == 0)
  {
    MIDI.sendNoteOn(PAD4[4], pad4.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD4[4], pad4.velocity, channel); //(note, velocity, channel)
    countdown[3] = map(pad4.velocity, 0, 127, mincount, maxcount);
    pos[3] = 1;
  }

  if (pad5.hit == true && pos[4] == 1)
  {
    MIDI.sendNoteOn(PAD5[4], 0, 1);
    MIDI.sendNoteOn(PAD5[4], pad5.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD5[4], 0, channel);
    usbMIDI.sendNoteOn(PAD5[4], pad5.velocity, channel); //(note, velocity, channel)
    countdown[4] = map(pad5.velocity, 0, 127, mincount, maxcount);
  }

  if (pad5.hit == true && pos[4] == 0)
  {
    MIDI.sendNoteOn(PAD5[4], pad5.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD5[4], pad5.velocity, channel); //(note, velocity, channel)
    countdown[4] = map(pad5.velocity, 0, 127, mincount, maxcount);
    pos[4] = 1;
  }

  if (pad6.hit == true && pos[5] == 1)
  {
    MIDI.sendNoteOn(PAD6[4], 0, 1);
    MIDI.sendNoteOn(PAD6[4], pad6.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD6[4], 0, channel);
    usbMIDI.sendNoteOn(PAD6[4], pad6.velocity, channel); //(note, velocity, channel)
    countdown[5] = map(pad6.velocity, 0, 127, mincount, maxcount);
  }

  if (pad6.hit == true && pos[5] == 0)
  {
    MIDI.sendNoteOn(PAD6[4], pad6.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD6[4], pad6.velocity, channel); //(note, velocity, channel)
    countdown[5] = map(pad6.velocity, 0, 127, mincount, maxcount);
    pos[5] = 1;
  }

  if (pad7.hit == true && pos[6] == 1)
  {
    MIDI.sendNoteOn(PAD7[4], 0, 1);
    MIDI.sendNoteOn(PAD7[4], pad7.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD7[4], 0, channel);
    usbMIDI.sendNoteOn(PAD7[4], pad7.velocity, channel); //(note, velocity, channel)
    countdown[6] = map(pad7.velocity, 0, 127, mincount, maxcount);
  }
  if (pad7.hit == true && pos[6] == 0)
  {
    MIDI.sendNoteOn(PAD7[4], pad7.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD7[4], pad7.velocity, channel); //(note, velocity, channel)
    countdown[6] = map(pad7.velocity, 0, 127, mincount, maxcount);
    pos[6] = 1;
  }
  if (pad8.hit == true && pos[7] == 1)
  {
    MIDI.sendNoteOn(PAD8[4], 0, 1);
    MIDI.sendNoteOn(PAD8[4], pad8.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD8[4], 0, channel);
    usbMIDI.sendNoteOn(PAD8[4], pad8.velocity, channel); //(note, velocity, channel)
    countdown[7] = map(pad8.velocity, 0, 127, mincount, maxcount);
  }
  if (pad8.hit == true && pos[7] == 0)
  {
    MIDI.sendNoteOn(PAD8[4], pad8.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD8[4], pad8.velocity, channel); //(note, velocity, channel)
    countdown[7] = map(pad8.velocity, 0, 127, mincount, maxcount);
    pos[7] = 1;
  }

  if (pad9.hit == true && pos[8] == 1)
  {
    MIDI.sendNoteOn(PAD9[4], 0, 1);
    MIDI.sendNoteOn(PAD9[4], pad9.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD9[4], 0, channel);
    usbMIDI.sendNoteOn(PAD9[4], pad9.velocity, channel); //(note, velocity, channel)
    countdown[8] = map(pad9.velocity, 0, 127, mincount, maxcount);
  }
  if (pad9.hit == true && pos[8] == 0)
  {
    MIDI.sendNoteOn(PAD9[4], pad9.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD9[4], pad9.velocity, channel); //(note, velocity, channel)
    countdown[8] = map(pad9.velocity, 0, 127, mincount, maxcount);
    pos[8] = 1;
  }
  if (pad10.hit == true && pos[9] == 1)
  {
    MIDI.sendNoteOn(PAD10[4], 0, 1);
    MIDI.sendNoteOn(PAD10[4], pad10.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD10[4], 0, channel);
    usbMIDI.sendNoteOn(PAD10[4], pad10.velocity, channel); //(note, velocity, channel)
    countdown[9] = map(pad10.velocity, 0, 127, mincount, maxcount);

  }
  if (pad10.hit == true && pos[9] == 0)
  {
    MIDI.sendNoteOn(PAD10[4], pad10.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD10[4], pad10.velocity, channel); //(note, velocity, channel)
    countdown[9] = map(pad10.velocity, 0, 127, mincount, maxcount);
    pos[9] = 1;

  }
  if (pad11.hit == true && pos[10] == 1)
  {
    MIDI.sendNoteOn(PAD11[4], 0, 1);
    MIDI.sendNoteOn(PAD11[4], pad11.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD11[4], 0, channel);
    usbMIDI.sendNoteOn(PAD11[4], pad11.velocity, channel); //(note, velocity, channel)
    countdown[10] = map(pad11.velocity, 0, 127, mincount, maxcount);
  }
  if (pad11.hit == true && pos[10] == 0)
  {
    MIDI.sendNoteOn(PAD11[4], pad11.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD11[4], pad11.velocity, channel); //(note, velocity, channel)
    countdown[10] = map(pad11.velocity, 0, 127, mincount, maxcount);
    pos[10] = 1;
  }
  if (pad12.hit == true && pos[11] == 1)
  {
    MIDI.sendNoteOn(PAD12[4], 0, 1);
    MIDI.sendNoteOn(PAD12[4], pad12.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD12[4], 0, channel);
    usbMIDI.sendNoteOn(PAD12[4], pad12.velocity, channel); //(note, velocity, channel)
    countdown[11] = map(pad12.velocity, 0, 127, mincount, maxcount);
  }
  if (pad12.hit == true && pos[11] == 0)
  {
    MIDI.sendNoteOn(PAD12[4], pad12.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD12[4], pad12.velocity, channel); //(note, velocity, channel)
    countdown[11] = map(pad12.velocity, 0, 127, mincount, maxcount);
    pos[11] = 1;
  }
  if (pad13.hit == true && pos[12] == 1)
  {
    MIDI.sendNoteOn(PAD13[4], 0, 1);
    MIDI.sendNoteOn(PAD13[4], pad13.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD13[4], 0, channel);
    usbMIDI.sendNoteOn(PAD13[4], pad13.velocity, channel); //(note, velocity, channel)
    countdown[12] = map(pad13.velocity, 0, 127, mincount, maxcount);
  }

  if (pad13.hit == true && pos[12] == 0)
  {
    MIDI.sendNoteOn(PAD13[4], pad13.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD13[4], pad13.velocity, channel); //(note, velocity, channel)
    countdown[12] = map(pad13.velocity, 0, 127, mincount, maxcount);
    pos[12] = 1;
  }

  if (pad14.hit == true && pos[13] == 1)
  {
    MIDI.sendNoteOn(PAD14[4], 0, 1);
    MIDI.sendNoteOn(PAD14[4], pad14.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD14[4], 0, channel);
    usbMIDI.sendNoteOn(PAD14[4], pad14.velocity, channel); //(note, velocity, channel)
    countdown[13] = map(pad14.velocity, 0, 127, mincount, maxcount);
  }

  if (pad14.hit == true && pos[13] == 0)
  {
    MIDI.sendNoteOn(PAD14[4], pad14.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD14[4], pad14.velocity, channel); //(note, velocity, channel)
    countdown[13] = map(pad14.velocity, 0, 127, mincount, maxcount);
    pos[13] = 1;
  }

  if (pad15.hit == true && pos[14] == 1)
  {
    MIDI.sendNoteOn(PAD15[4], 0, 1);
    MIDI.sendNoteOn(PAD15[4], pad15.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD15[4], 0, channel);
    usbMIDI.sendNoteOn(PAD15[4], pad15.velocity, channel); //(note, velocity, channel)
    countdown[14] = map(pad15.velocity, 0, 127, mincount, maxcount);
  }

  if (pad15.hit == true && pos[14] == 0)
  {
    MIDI.sendNoteOn(PAD15[4], pad15.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD15[4], pad15.velocity, channel); //(note, velocity, channel)
    countdown[14] = map(pad15.velocity, 0, 127, mincount, maxcount);
    pos[14] = 1;
  }

  if (pad16.hit == true && pos[15] == 1)
  {
    MIDI.sendNoteOn(PAD16[4], 0, 1);
    MIDI.sendNoteOn(PAD16[4], pad16.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD16[4], 0, channel);
    usbMIDI.sendNoteOn(PAD16[4], pad16.velocity, channel); //(note, velocity, channel)
    countdown[15] = map(pad16.velocity, 0, 127, mincount, maxcount);
  }

  if (pad16.hit == true && pos[15] == 0)
  {
    MIDI.sendNoteOn(PAD16[4], pad16.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD16[4], pad16.velocity, channel); //(note, velocity, channel)
    countdown[15] = map(pad16.velocity, 0, 127, mincount, maxcount);
    pos[15] = 1;
  }

  if (pad17.hit == true && pos[16] == 1)
  {
    MIDI.sendNoteOn(PAD17[4], 0, 1);
    MIDI.sendNoteOn(PAD17[4], pad17.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD17[4], 0, channel);
    usbMIDI.sendNoteOn(PAD17[4], pad17.velocity, channel); //(note, velocity, channel)
    countdown[16] = map(pad17.velocity, 0, 127, mincount, maxcount);
  }

  if (pad17.hit == true && pos[16] == 0)
  {
    MIDI.sendNoteOn(PAD17[4], pad17.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD17[4], pad17.velocity, channel); //(note, velocity, channel)
    countdown[16] = map(pad17.velocity, 0, 127, mincount, maxcount);
    pos[16] = 1;
  }

  if (pad18.hit == true && pos[17] == 1)
  {
    MIDI.sendNoteOn(PAD18[4], 0, 1);
    MIDI.sendNoteOn(PAD18[4], pad18.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD18[4], 0, channel);
    usbMIDI.sendNoteOn(PAD18[4], pad18.velocity, channel); //(note, velocity, channel)
    countdown[17] = map(pad18.velocity, 0, 127, mincount, maxcount);
  }

  if (pad18.hit == true && pos[17] == 0)
  {
    MIDI.sendNoteOn(PAD18[4], pad18.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD18[4], pad18.velocity, channel); //(note, velocity, channel)
    countdown[17] = map(pad18.velocity, 0, 127, mincount, maxcount);
    pos[17] = 1;
  }

  if (pad19.hit == true && pos[18] == 1)
  {
    MIDI.sendNoteOn(PAD19[4], 0, 1);
    MIDI.sendNoteOn(PAD19[4], pad19.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD19[4], 0, channel);
    usbMIDI.sendNoteOn(PAD19[4], pad19.velocity, channel); //(note, velocity, channel)
    countdown[18] = map(pad19.velocity, 0, 127, mincount, maxcount);
  }

  if (pad19.hit == true && pos[18] == 0)
  {
    MIDI.sendNoteOn(PAD19[4], pad19.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD19[4], pad19.velocity, channel); //(note, velocity, channel)
    countdown[18] = map(pad19.velocity, 0, 127, mincount, maxcount);
    pos[18] = 1;
  }

  if (pad20.hit == true && pos[19] == 1)
  {
    MIDI.sendNoteOn(PAD20[4], 0, 1);
    MIDI.sendNoteOn(PAD20[4], pad20.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD20[4], 0, channel);
    usbMIDI.sendNoteOn(PAD20[4], pad20.velocity, channel); //(note, velocity, channel)
    countdown[19] = map(pad20.velocity, 0, 127, mincount, maxcount);
  }

  if (pad20.hit == true && pos[19] == 0)
  {
    MIDI.sendNoteOn(PAD20[4], pad20.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD20[4], pad20.velocity, channel); //(note, velocity, channel)
    countdown[19] = map(pad20.velocity, 0, 127, mincount, maxcount);
    pos[19] = 1;
  }

  if (pad21.hit == true && pos[20] == 1)
  {
    MIDI.sendNoteOn(PAD21[4], 0, 1);
    MIDI.sendNoteOn(PAD21[4], pad21.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD21[4], 0, channel);
    usbMIDI.sendNoteOn(PAD21[4], pad21.velocity, channel); //(note, velocity, channel)
    countdown[20] = map(pad21.velocity, 0, 127, mincount, maxcount);
  }

  if (pad21.hit == true && pos[20] == 0)
  {
    MIDI.sendNoteOn(PAD21[4], pad21.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD21[4], pad21.velocity, channel); //(note, velocity, channel)
    countdown[20] = map(pad21.velocity, 0, 127, mincount, maxcount);
    pos[20] = 1;
  }

  if (pad22.hit == true && pos[21] == 1)
  {
    MIDI.sendNoteOn(PAD22[4], 0, 1);
    MIDI.sendNoteOn(PAD22[4], pad22.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD22[4], 0, channel);
    usbMIDI.sendNoteOn(PAD22[4], pad22.velocity, channel); //(note, velocity, channel)
    countdown[21] = map(pad22.velocity, 0, 127, mincount, maxcount);
  }

  if (pad22.hit == true && pos[21] == 0)
  {
    MIDI.sendNoteOn(PAD22[4], pad22.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD22[4], pad22.velocity, channel); //(note, velocity, channel)
    countdown[21] = map(pad22.velocity, 0, 127, mincount, maxcount);
    pos[21] = 1;
  }

  if (pad23.hit == true && pos[22] == 1)
  {
    MIDI.sendNoteOn(PAD23[4], 0, 1);
    MIDI.sendNoteOn(PAD23[4], pad23.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD23[4], 0, channel);
    usbMIDI.sendNoteOn(PAD23[4], pad23.velocity, channel); //(note, velocity, channel)
    countdown[22] = map(pad23.velocity, 0, 127, mincount, maxcount);
  }

  if (pad23.hit == true && pos[22] == 0)
  {
    MIDI.sendNoteOn(PAD23[4], pad23.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD23[4], pad23.velocity, channel); //(note, velocity, channel)
    countdown[22] = map(pad23.velocity, 0, 127, mincount, maxcount);
    pos[22] = 1;
  }

  if (pad24.hit == true && pos[23] == 1)
  {
    MIDI.sendNoteOn(PAD24[4], 0, 1);
    MIDI.sendNoteOn(PAD24[4], pad24.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD24[4], 0, channel);
    usbMIDI.sendNoteOn(PAD24[4], pad24.velocity, channel); //(note, velocity, channel)
    countdown[23] = map(pad24.velocity, 0, 127, mincount, maxcount);
  }

  if (pad24.hit == true && pos[23] == 0)
  {
    MIDI.sendNoteOn(PAD24[4], pad24.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD24[4], pad24.velocity, channel); //(note, velocity, channel)
    countdown[23] = map(pad24.velocity, 0, 127, mincount, maxcount);
    pos[23] = 1;
  }

  if (pad25.hit == true && pos[24] == 1)
  {
    MIDI.sendNoteOn(PAD25[4], 0, 1);
    MIDI.sendNoteOn(PAD25[4], pad25.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD25[4], 0, channel);
    usbMIDI.sendNoteOn(PAD25[4], pad25.velocity, channel); //(note, velocity, channel)
    countdown[24] = map(pad25.velocity, 0, 127, mincount, maxcount);
  }

  if (pad25.hit == true && pos[24] == 0)
  {
    MIDI.sendNoteOn(PAD25[4], pad25.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD25[4], pad25.velocity, channel); //(note, velocity, channel)
    countdown[24] = map(pad25.velocity, 0, 127, mincount, maxcount);
    pos[24] = 1;
  }

  if (pad26.hit == true && pos[25] == 1)
  {
    MIDI.sendNoteOn(PAD26[4], 0, 1);
    MIDI.sendNoteOn(PAD26[4], pad26.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD26[4], 0, channel);
    usbMIDI.sendNoteOn(PAD26[4], pad26.velocity, channel); //(note, velocity, channel)
    countdown[25] = map(pad26.velocity, 0, 127, mincount, maxcount);
  }

  if (pad26.hit == true && pos[25] == 0)
  {
    MIDI.sendNoteOn(PAD26[4], pad26.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD26[4], pad26.velocity, channel); //(note, velocity, channel)
    countdown[25] = map(pad26.velocity, 0, 127, mincount, maxcount);
    pos[25] = 1;
  }
  if (pad27.hit == true && pos[26] == 1)
  {
    MIDI.sendNoteOn(PAD27[4], 0, 1);
    MIDI.sendNoteOn(PAD27[4], pad27.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD27[4], 0, channel);
    usbMIDI.sendNoteOn(PAD27[4], pad27.velocity, channel); //(note, velocity, channel)
    countdown[26] = map(pad27.velocity, 0, 127, mincount, maxcount);
  }

  if (pad27.hit == true && pos[26] == 0)
  {
    MIDI.sendNoteOn(PAD27[4], pad27.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD27[4], pad27.velocity, channel); //(note, velocity, channel)
    countdown[26] = map(pad27.velocity, 0, 127, mincount, maxcount);
    pos[26] = 1;
  }
  if (pad28.hit == true && pos[27] == 1)
  {
    MIDI.sendNoteOn(PAD28[4], 0, 1);
    MIDI.sendNoteOn(PAD28[4], pad28.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD28[4], 0, channel);
    usbMIDI.sendNoteOn(PAD28[4], pad28.velocity, channel); //(note, velocity, channel)
    countdown[27] = map(pad28.velocity, 0, 127, mincount, maxcount);
  }

  if (pad28.hit == true && pos[27] == 0)
  {
    MIDI.sendNoteOn(PAD28[4], pad28.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD28[4], pad28.velocity, channel); //(note, velocity, channel)
    countdown[27] = map(pad28.velocity, 0, 127, mincount, maxcount);
    pos[27] = 1;
  }
  if (pad29.hit == true && pos[28] == 1)
  {
    MIDI.sendNoteOn(PAD29[4], 0, 1);
    MIDI.sendNoteOn(PAD29[4], pad29.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD29[4], 0, channel);
    usbMIDI.sendNoteOn(PAD29[4], pad29.velocity, channel); //(note, velocity, channel)
    countdown[28] = map(pad29.velocity, 0, 127, mincount, maxcount);
  }

  if (pad29.hit == true && pos[28] == 0)
  {
    MIDI.sendNoteOn(PAD29[4], pad29.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD29[4], pad29.velocity, channel); //(note, velocity, channel)
    countdown[28] = map(pad29.velocity, 0, 127, mincount, maxcount);
    pos[28] = 1;
  }
  if (pad30.hit == true && pos[29] == 1)
  {
    MIDI.sendNoteOn(PAD30[4], 0, 1);
    MIDI.sendNoteOn(PAD30[4], pad30.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD30[4], 0, channel);
    usbMIDI.sendNoteOn(PAD30[4], pad30.velocity, channel); //(note, velocity, channel)
    countdown[29] = map(pad30.velocity, 0, 127, mincount, maxcount);
  }

  if (pad30.hit == true && pos[29] == 0)
  {
    MIDI.sendNoteOn(PAD30[4], pad30.velocity, 1); //(note, velocity, channel)
    usbMIDI.sendNoteOn(PAD30[4], pad30.velocity, channel); //(note, velocity, channel)
    countdown[29] = map(pad30.velocity, 0, 127, mincount, maxcount);
    pos[29] = 1;
  }

  for (int i = 0; i < 30; i++) {
    if (countdown[i] > 1) {
      countdown[i]--;
    } else if (countdown[i] == 1) {
      countdown[i] = 0;
      if (i >= 16) {
        MIDI.sendNoteOn(Note[1][i - 16], 0, 1);
        usbMIDI.sendNoteOn(Note[1][i - 16], 0, channel);
      } else {
        MIDI.sendNoteOn(Note[0][i], 0, 1);
        usbMIDI.sendNoteOn(Note[0][i], 0, channel);
      }
      pos[i] = 0;
    }
  }

  // Potenciómetros - lectura
  /*
    short potpins[2] = {1,2};
    short potvalue[2] = {0};
    short potposnow[2] = {0};
    short potposlast[2] = {0};
    short fired[2] = {0};
    short change[2] = {0};
  */
  for (int i = 0; i < 2; i++) {
    potvalue[i] = analogRead(potpins[i]);
    potposnow[i] = map(potvalue[i], 1023, 0, 1, 4); // Para 4 posiciones, por ejemplo.
    if (potposnow[i] != potposlast[i]) {
      if (i == 0) {
        if (potposnow[i] == 1) {  //
          MIDI.sendControlChange(0x50, 127, 5);
          MIDI.sendControlChange(0x50, 127, 1);
          MIDI.sendControlChange(0x50, 127, 6);
          MIDI.sendControlChange(0x50, 127, 1);
          MIDI.sendControlChange(0x50, 127, 7);
          MIDI.sendControlChange(0x50, 127, 1);
          potposlast[i] = potposnow[i];
        } else if (potposnow[i] == 2) {
          MIDI.sendControlChange(0x50, 127, 5);
          MIDI.sendControlChange(0x50, 127, 2);
          MIDI.sendControlChange(0x50, 127, 6);
          MIDI.sendControlChange(0x50, 127, 2);
          MIDI.sendControlChange(0x50, 127, 7);
          MIDI.sendControlChange(0x50, 127, 2);
          potposlast[i] = potposnow[i];
        } else if (potposnow[i] == 3) {
          MIDI.sendControlChange(0x50, 127, 5);
          MIDI.sendControlChange(0x50, 127, 3);
          MIDI.sendControlChange(0x50, 127, 6);
          MIDI.sendControlChange(0x50, 127, 3);
          MIDI.sendControlChange(0x50, 127, 7);
          MIDI.sendControlChange(0x50, 127, 3);
          potposlast[i] = potposnow[i];
        } else if (potposnow[i] == 4) {
          MIDI.sendControlChange(0x50, 127, 5);
          MIDI.sendControlChange(0x50, 127, 4);
          MIDI.sendControlChange(0x50, 127, 6);
          MIDI.sendControlChange(0x50, 127, 4);
          MIDI.sendControlChange(0x50, 127, 7);
          MIDI.sendControlChange(0x50, 127, 4);
          potposlast[i] = potposnow[i];
        }
      } else if (i == 1) {
        if (potposnow[i] == 1) {
          if (monomode == 0) {
            MIDI.sendControlChange(0x53, 127, 1); // mono
            monomode = 1;
          }
          MIDI.sendControlChange(0x50, 127, 5);// Seleccionamos osc 1.
          MIDI.sendControlChange(0x10, 0, 1); // Sonido 1 SENO
          MIDI.sendControlChange(0x10, 45, 4); // MORPH.
          MIDI.sendControlChange(0x50, 127, 6); // Seleccionamos segundo osc.
          MIDI.sendControlChange(0x10, 0, 2); // Volumen 81 para segundo.
          MIDI.sendControlChange(0x50, 127, 4); // Octava.
          MIDI.sendControlChange(0x10, 127, 3); // Afinamos en el agudo.
          MIDI.sendControlChange(0x50, 127, 7); // Seleccionamos tercer osc.
          MIDI.sendControlChange(0x10, 0, 2); // Volumen para tercero.
          MIDI.sendControlChange(0x50, 101, 4); // Afinación para tercero.
          //MIDI.sendControlChange(0x53,127,1); // mono
          //monomode = !monomode;
          potposlast[i] = potposnow[i];
        } else if (potposnow[i] == 2) {
          if (monomode == 0) {
            MIDI.sendControlChange(0x53, 127, 1); // mono
            monomode = 1;
          }
          MIDI.sendControlChange(0x10, 25, 1); // Sonido 2 SAW
          MIDI.sendControlChange(0x50, 127, 6); // Seleccionamos segundo osc.
          MIDI.sendControlChange(0x10, 81, 2); // Volumen 81 para segundo.
          MIDI.sendControlChange(0x50, 127, 4);
          MIDI.sendControlChange(0x10, 127, 3); // Afinamos a una octava en el agudo.
          MIDI.sendControlChange(0x50, 127, 7); // Seleccionamos tercer osc.
          MIDI.sendControlChange(0x10, 89, 2); // Volumen para tercero.
          MIDI.sendControlChange(0x50, 101, 4); // Afinación para tercero.
          potposlast[i] = potposnow[i];
        } else if (potposnow[i] == 3) {
          if (monomode == 0) {
            MIDI.sendControlChange(0x53, 127, 1); // mono
            monomode = 1;
          }
          MIDI.sendControlChange(0x50, 127, 5);// Seleccionamos osc 1.
          MIDI.sendControlChange(0x10, 50, 1); // Sonido 3 SQUARE
          MIDI.sendControlChange(0x50, 127, 6); // Seleccionamos segundo osc.
          MIDI.sendControlChange(0x10, 0, 2); // Volumen 81 para segundo.
          MIDI.sendControlChange(0x50, 127, 7); // Seleccionamos tercer osc.
          MIDI.sendControlChange(0x10, 0, 2); // Volumen para tercero.
          MIDI.sendControlChange(0x11, 0, 1); // ATTACK
          MIDI.sendControlChange(0x11, 0, 2); // DECAY
          MIDI.sendControlChange(0x11, 60, 3); // ATTACK
          MIDI.sendControlChange(0x11, 60, 4); // ATTACK
          potposlast[i] = potposnow[i];
        } else if (potposnow[i] == 4) {
          if (monomode == 0) {
            MIDI.sendControlChange(0x53, 127, 1); // mono
            monomode = 1;
          }
          MIDI.sendControlChange(0x50, 127, 5);// Seleccionamos osc 1.
          MIDI.sendControlChange(0x10, 90, 1); // Sonido 4 TRI
          MIDI.sendControlChange(0x10, 100, 4); // Morph 100
          MIDI.sendControlChange(0x50, 127, 6); // Seleccionamos segundo osc.
          MIDI.sendControlChange(0x10, 0, 2); // Volumen 81 para segundo.
          MIDI.sendControlChange(0x50, 127, 7); // Seleccionamos tercer osc.
          MIDI.sendControlChange(0x10, 0, 2); // Volumen para tercero.
          MIDI.sendControlChange(0x11, 0, 1); // ATTACK
          MIDI.sendControlChange(0x11, 0, 2); // DECAY
          MIDI.sendControlChange(0x11, 60, 3); // ATTACK
          MIDI.sendControlChange(0x11, 60, 4); // ATTACK
          potposlast[i] = potposnow[i];

        }
      }
    }
  }
}
/*
  MIDI.sendControlChange(0x10,40,1); // Forma de onda. Rotativo.

  SINE = 0, SAW = 25, SQUARE = 50, PULSE = 75, TRI, NOISE.

  Parámetros básicos:

    { 0x0, 0x10, "R1", NULL, Synth_SetOscParam, SYNTH_OSC_PARAM_WAVEFORM},
    { 0x1, 0x10, "R2", NULL, Synth_SetOscParam, SYNTH_OSC_PARAM_VOLUME},
    { 0x2, 0x10, "R3", NULL, Synth_SetOscParam, SYNTH_OSC_PARAM_PITCH},
    { 0x3, 0x10, "R4", NULL, Synth_SetParam, SYNTH_PARAM_VOICE_MORPH},

  Sin tocar nada, todos los cambios se aplican al oscilador 1.

  Para seleccionar cada oscilador:

  CON ESTE SELECCIONAMOS CADA OSCILADOR.

  { 0x4, 0x50, "A5", NULL, Synth_SetCfgOsc, 0},
  { 0x5, 0x50, "A6", NULL, Synth_SetCfgOsc, 1},
  { 0x6, 0x50, "A7", NULL, Synth_SetCfgOsc, 2},

  Después con el voice morphing, podemos ir cambiando el efecto. También podremos modificar el filtro de corte
  y la resonancia global del sintetizador.


  //  { 0x5, 0x10, "R6", NULL, Synth_SetParam, SYNTH_PARAM_MAIN_FILT_CUTOFF},
  //  { 0x6, 0x10, "R7", NULL, Synth_SetParam, SYNTH_PARAM_MAIN_FILT_RESO},

  Attack, Delay, Sustain, Release.



  //sendControlChange(inNumber, inValue, inChannel)
  //MIDI.sendControlChange(0x50,127,1); // Octava 0
  //MIDI.sendControlChange(0x53,127,1); // Modo Mono



  //MIDI.sendControlChange(0x50,0,4); // Filtro extraño - No usar
  //MIDI.sendControlChange(0x10,80,4);
*/
