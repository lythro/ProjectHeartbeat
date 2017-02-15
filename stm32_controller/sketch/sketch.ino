#include "common/include/EffectManager.hpp"

// max len of incoming message
#define INCOMING_MAX_LEN 100


// global message buffer
char incoming[INCOMING_MAX_LEN];
int cnt = 0;


void setup() {
  // init serial connection (bluetooth)
  Serial3.begin(9600);

  // setup timer interrupt for periodic LED update
  // TODO
}

void loop() {
  // handle serial communication
  int unread = Serial3.available();
  if (unread > 0) {  
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
  }
}


void processMessage() {
  // TODO
  Serial3.print( "I got this: " );
  Serial3.print( incoming );
}

