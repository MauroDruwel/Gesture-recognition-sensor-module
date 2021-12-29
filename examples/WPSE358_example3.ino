/*
  @@@@@@@@@@@@@@@@@@@@@@                                                                                                                               
  @@@@@@@@@@@@@@@@@@@@@@             @@@.    @@@    @@@.     @@@@    @@@@        @@@@@@@@@        @@@@@@@@@@@@@.     .@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@%%@@@%%@@@%%@@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@@@@@@@        @@@@@@@@@@@@@@     @@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@  @@@  @@@  @@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@            @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@   @    @   @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@@@@@@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@@@@@@@@ 
  @@@@@            @@@@@             @@@@###@@@@@##@@@@@     @@@@    @@@@      @@@@@@@@@@@@       #@@@@@###@@@@@     ##@@@@@###@@@@       @@@@@@@@@@@
  @@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@     @@@@    @@@@      @@@@    @@@@@      @@@@@@@@@@@@@@     @@@@@@@@@@@@@@      @@@@     @@@@
  @@@@@@@@@@@@@@@@@@@@@@
  
  Whadda GESTURE RECOGNITION SENSOR MODULE
 */


// Includes enum definition of GES_* return values from readGesture()
#include "RevEng_PAJ7620.h"
uint8_t buf[8] = {
  0
};  // Keyboard Report Buffer: 8 bytes
//#define SERIAL_DEBUG  // for serial debug: remove //
                        // for actual HID: put //

// Create gesture sensor driver object
RevEng_PAJ7620 sensor = RevEng_PAJ7620();


// *********************************************************************
void setup()
{
  Serial.begin(9600);

  ////Serial.println("PAJ7620 sensor demo: Recognizing all 9 gestures.");

  if( !sensor.begin() )           // return value of 0 == success
  {
    //Serial.print("PAJ7620 I2C error - halting");
    while(true) { }
  }

  ////Serial.println("PAJ7620 init: OK");
  //Serial.println("Please input your gestures:");
}


// *********************************************************************
void loop()
{
  Gesture gesture;                  // Gesture is an enum type from RevEng_PAJ7620.h
  gesture = sensor.readGesture();   // Read back current gesture (if any) of type Gesture

  switch (gesture)
  {
    case GES_FORWARD:
      {
        //Serial.print("GES_FORWARD");
        break;
      }

    case GES_BACKWARD:
      {
        //Serial.print("GES_BACKWARD");
        break;
      }

    case GES_LEFT:
      {
        //Serial.print("GES_UP");
        break;
      }

    case GES_RIGHT:
      {
        //Serial.print("GES_DOWN");
        break;
      }

    case GES_UP:
      {
        //Serial.print("GES_RIGHT");
        // Send the code
        buf[2] = 79;    // HID: RightArrow
        #ifdef SERIAL_DEBUG
        buf[2] = 'R';     // Serial: R key
        #endif
        break;
      }

    case GES_DOWN:
      {
        //Serial.print("GES_LEFT");
        // Send the code
        buf[2] = 80;    // HID: LeftArrow
        #ifdef SERIAL_DEBUG
        buf[2] = 'L';     // Serial: L key
        #endif
        break;
      }

    case GES_CLOCKWISE:
      {
        //Serial.print("GES_CLOCKWISE");
        break;
      }

    case GES_ANTICLOCKWISE:
      {
        //Serial.print("GES_ANTICLOCKWISE");
        break;
      }

    case GES_WAVE:
      {
        //Serial.print("GES_WAVE");
        break;
      }

    case GES_NONE:
      {
        break;
      }
  }

  if( gesture != GES_NONE )
  {
    //Serial.print(", Code: ");
    //Serial.println(gesture);
  }
  Serial.write(buf, 8); // Send keypress
  delay(100);
  releaseKey();
  delay(100);
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
}
