# ProjectHeartbeat
This projects aims at connecting a smartphone-app with a stm32-microcontroller and an APA102c led
strip to configure and display different colour-patterns/animations. It is split into 3 parts:

## common
The source and header files in the root directory specify different LED effects/patterns. To 
implement a new pattern, create a new class that inherits from "Effect" and overwrites the virtual 
methods "getRGB" and "setConfig". Also, you will need to extend the EffectManager class to create the
new effect from a given config string. For a few notes on what to do and what to avoid, see below:

- extend "Effect"
- implement getRGB( unsigned char id, unsigned char\* r, unsigned char\* g, unsigned char\* b )
  - id selects the current LED to get a colour for
  - r, g, b are to be given values from 0 to 255
  - this->maxSteps defines the number of steps for a full animation cycle
  - this->step defines the current step, it is updated externally and can/should be used to create
	different patterns
  - the LEDs update frequency is 100Hz (may change in the future)
  - this->getNumLEDs() returns the currently set number of LEDs to use
- implement setConfig( char\* config )
  - config is a c-string: "par1 par2 par3 ...\0"
  - use strtok to split parameters, atoi to convert them to numbers (see examples)
- *avoid* using any bigger libraries, do as much as possible manually! This code will be run on a
  microcontroller with 120kB flash memory and 20kB RAM.
- for the same reason, *avoid* printf at all costs!
- pray that flash and RAM will be enough for our code ...

### implemented effects
To change the displayed effect, call EffectManager.setConfig( char\* config ) with a string:

- "{name}:{param1} {param2} [...]"
- the string may be preceded by "split:" create an effect that spans only half the LED-strip and
  appears mirrored on the other half, e.g.:
  - "rainbow:200 1" goes all way round, while
  - `"split:rainbow:200 1"` starts on one end of the "circle" and meets at the other end

- Effect
  - default effect, fades from black to r, g or b to black
  - config string: "fillcolour:[r|g|b]"
- FullRainbow
  - rainbow effect
  - config string: "rainbow:{duration} {circles}"
    - {duration} defines the speed of the animation: lower is faster, "100" equals 1 second
	- {circles} defines the number of HSV-circles to display simultanously:
	  - 0 displays all LEDs in the same (but changing) colour
	  - 1 creates a ring (b->g->r->b) (1 blue)
	  - 2 creates a ring (b->g->r->b->g->r->b) (2 blue)
	  - ...
- Meteor
  - single colour meteor (or rather comet? shiny thing moving along the night's sky)
  - config string: "meteor:{duration} {length}"

- more to be announced


## effect\_tests
This part is just a debug environment to test the different effects.
- cd effect\_tests/
- mkdir build
- cd build
- cmake ..
- make
- ./viewer
- type the config string (including the name of the effect) into the line edit at the top, press
  enter to apply the change

## ProjectHeartbeat.ino
This is the arduino ide project file.
Specific code for the microcontroller: A maple mini board, STM32F103CBT6. For instructions on how to
program it, see https://github.com/rogerclarkmelbourne/Arduino\_STM32/wiki/Installation
