/*

 FreezerGuard
 
 */
#include "pitches.h"

// notes in the melody:
int warning[] = {
  NOTE_G3, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_AS3, NOTE_A3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_FS3, NOTE_G3};
//NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

int openDoor[] = { 
  NOTE_GS3, NOTE_F3, NOTE_A2
};

int shutDoor[] = { 
  NOTE_A2, NOTE_F3, NOTE_GS3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int warningDurations[] = {
  //2,3,4,2,3,4,4,4,4,4,1
    4,6,8,4,6,8,8,8,8,8,2
  };

int openDurations[] = {
  //2,3,4,2,3,4,4,4,4,4,1
    2,4,4
  };

int shutDurations[] = {
  //2,3,4,2,3,4,4,4,4,4,1
    4,4,2
  };

void setup() {
  pinMode(1,INPUT);
  pinMode(8,OUTPUT);
  play(shutDoor, shutDurations, 3);
}

void loop(){
  if (doorIsOpen()){
    delay(500);

    if (doorIsOpen()){
      play(openDoor, openDurations, 3);

      for (int i = 0; doorIsOpen() && i < 240; i++){
        delay(500);
      }
    
      while (doorIsOpen()){
        play(warning, warningDurations, 11);
        delay(1000);
      }

      play(shutDoor, shutDurations, 3);
    }
    
  } 
}

int doorIsOpen(){
  return digitalRead(1) == HIGH;
}

void play(int notes[], int durations[], int num) {

   for (int thisNote = 0; thisNote < num; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/durations[thisNote];
    tone(8, notes[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
