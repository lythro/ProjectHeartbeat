#include "EffectManager.h"
#include <SPI.h>

// max len of incoming message
#define INCOMING_MAX_LEN 100


// global message buffer
char incoming[INCOMING_MAX_LEN];
int cnt = 0;
EffectManager effectManager;
int numLEDs;

// timer
HardwareTimer timer(1);

// incoming data flag to pause led updates!
volatile bool receiving;

void setup() {
  receiving = false;
  numLEDs = effectManager.getNumLEDs();
  
  // init serial connection (bluetooth)
  Serial3.begin(9600);

  // init SPI for LED-strip
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));

  // setup timer interrupt for periodic LED update
  timer.pause();
  //timer.setPeriod( 10000 ); // 10 ms --> 100 Hz
  // currently setting only one led per period
  // --> at 120 LEDs: ~83 microseconds per LED for 100 Hz
  timer.setPeriod( 100 ); 
  //
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
    receiving = true;
    timer.pause();
    while(true) {
      char c = Serial3.read();
      if (c == '\n') {
        incoming[cnt] = '\0';
        cnt = 0;
        processMessage();
        timer.resume();
        receiving = false;
        break;
      } else {
        incoming[cnt++] = c;
        if (cnt >= INCOMING_MAX_LEN - 1) {
          cnt = INCOMING_MAX_LEN - 1;
        }
      }
      while (Serial3.available() == 0) {} // wait for data
    }// end while
    
  }
}



// apply given configuration
void processMessage() {
  // TODO
  //Serial3.print( "I got this: " );
  //Serial3.print( incoming );
  effectManager.setConfig( incoming );
}


// update one LED per ISR
// plus a bit of counting to be done
// should be fast enough to notice transmissions between two LEDs!
void handler_led() {
  static byte currentLED = 0;
  if (currentLED == 0) {
    // send start frame
    SPI.transfer( 0 );
    SPI.transfer( 0 );
    SPI.transfer( 0 );
    SPI.transfer( 0 );
  }

  byte r, g, b;
  effectManager.getRGB( currentLED, &r, &g, &b );
  SPI.transfer( 0xff );
  SPI.transfer( b );
  SPI.transfer( g );
  SPI.transfer( r );

  currentLED++;
  if (currentLED >= numLEDs) {
    currentLED = 0;
    effectManager.nextStep();
  }
}

/* // all LEDs updated in ONE ISR!
 // THIS TAKES LONG, dropped UART bytes!
void handler_led() {
  if (receiving) return;
  byte numLEDs = effectManager.getNumLEDs();
  effectManager.nextStep();

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
  
  //SPI.endTransaction();
}
*/
