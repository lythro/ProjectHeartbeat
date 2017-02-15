#include "EffectManager.h"
#include <SPI.h>

// max len of incoming message
#define INCOMING_MAX_LEN 100


// global message buffer
char incoming[INCOMING_MAX_LEN];
int cnt = 0;
EffectManager effectManager;

// timer
HardwareTimer timer(1);


void setup() {
  // init serial connection (bluetooth)
  Serial3.begin(9600);

  // setup timer interrupt for periodic LED update
  timer.pause();
  timer.setPeriod( 20000 ); // 20 ms --> 50 Hz
  timer.setChannelMode( TIMER_CH1, TIMER_OUTPUT_COMPARE );
  timer.setCompare( TIMER_CH1, 1 );
  timer.attachInterrupt( 1, handler_led );
  timer.refresh();
  timer.resume();
}

// full msg
void loop() {
  int unread = Serial3.available();
  if (unread > 0) {
    timer.pause();
    while(true) {
      while (Serial3.available() == 0) {} // wait for data
      char c = Serial3.read();
      if (c == '\n') {
        incoming[cnt] = '\0';
        cnt = 0;
        processMessage();
        timer.resume();
        break;
      } else {
        incoming[cnt++] = c;
        if (cnt >= INCOMING_MAX_LEN - 1) {
          cnt = INCOMING_MAX_LEN - 1;
        }
      }
    }// end while
    
  }
}

/* // byte by byte
void loop() {
  // handle serial communication
  int unread = Serial3.available();
  if (unread > 0) {
    timer.pause();
    char c = Serial3.read();
    if (c == '\n') {
      // message terminator,
      // end the string and process the message
      // (i.e. update config)
      incoming[cnt] = '\0';
      cnt = 0;
      processMessage();
      
    } else {
      incoming[cnt++] = c;
      // when overflowing, start to overwrite the last character
      if (cnt >= INCOMING_MAX_LEN - 1) {
        cnt = INCOMING_MAX_LEN - 1;
      }
    }
    // done reading one char
  } else {
    timer.resume();
  }
}
*/

// apply given configuration
void processMessage() {
  // TODO
  Serial3.print( "I got this: " );
  Serial3.print( incoming );
  effectManager.setConfig( incoming );
}




void handler_led() {
  byte numLEDs = effectManager.getNumLEDs();
  effectManager.nextStep();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));

  // start frame
  SPI.transfer( 0 );
  SPI.transfer( 0 );
  SPI.transfer( 0 );
  SPI.transfer( 0 );

  byte r, g, b;
  for (int i = 0; i < numLEDs; i++) {
    effectManager.getRGB( i, &r, &g, &b );
    SPI.transfer( 0xff ); // full brightness (global)
    SPI.transfer( b );
    SPI.transfer( g );
    SPI.transfer( r );
  }
  
  SPI.endTransaction();
}


