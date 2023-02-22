/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/arduino-melody-repeat-example
   Library References: https://arduinogetstarted.com/tutorials/arduino-buzzer-library

   This example uses a piezo buzzer:
   + play a melody on background
   + repeat the melody when it is ended
   + without using delay() function, this is a non-blocking example
*/

#include <ezBuzzer.h> // ezBuzzer library

const int BUZZER_PIN = 3;
int melody[] = {NOTE_E5};
int tempo[] = {1};
int noteLength = 1;

ezBuzzer buzzer(BUZZER_PIN); // create ezBuzzer object that attach to a pin;


void setup() {
  Serial.begin(9600);
}

void loop() {
  buzzer.loop(); // MUST call the buzzer.loop() function in loop()

  if (buzzer.getState() == BUZZER_IDLE) { // if stopped
    buzzer.playMelody(melody, tempo, noteLength); // playing
  }
}