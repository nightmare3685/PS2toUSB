/*
This example shows how to retrieve a button status on PS2 Controller.

Function:
  readButton(button); // Read button status, it will return corresponding data
                      // Digital button: 0 = pressed, 1 = released
                      // Analog button: return a value

  Digital button:
    PS2_SELECT
    PS2_JOYSTICK_LEFT
    PS2_JOYSTICK_RIGHT
    PS2_START
    PS2_UP
    PS2_RIGHT
    PS2_DOWN
    PS2_LEFT
    PS2_LEFT_2
    PS2_RIGHT_2
    PS2_LEFT_1
    PS2_RIGHT_1
    PS2_TRIANGLE
    PS2_CIRCLE
    PS2_CROSS
    PS2_SQUARE

  Analog button:
    PS2_JOYSTICK_LEFT_X_AXIS
    PS2_JOYSTICK_LEFT_Y_AXIS
    PS2_JOYSTICK_RIGHT_X_AXIS
    PS2_JOYSTICK_RIGHT_Y_AXIS
    PS2_JOYSTICK_LEFT_UP
    PS2_JOYSTICK_LEFT_DOWN
    PS2_JOYSTICK_LEFT_LEFT
    PS2_JOYSTICK_LEFT_RIGHT
    PS2_JOYSTICK_RIGHT_UP
    PS2_JOYSTICK_RIGHT_DOWN
    PS2_JOYSTICK_RIGHT_LEFT
    PS2_JOYSTICK_RIGHT_RIGHT

Product page:
  Cytron PS2 Shield: http://www.cytron.com.my/p-shield-ps2
  PS2 Controller: http://www.cytron.com.my/p-ps-gp-1
  CT-UNO: http://www.cytron.com.my/p-ct-uno

Original written by:
            Cytron Technologies

Modified:
  29/06/15  Idris, Cytron Technologies
*/

#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
#include <Joystick.h>
Cytron_PS2Shield ps2(8, 9);  // SoftwareSerial: Rx and Tx pin
//Cytron_PS2Shield ps2; // HardwareSerial

#define LEDPIN 13
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   12, 1,                 // Button Count, Hat Switch Count
                   true, true, true,      // X, Y, Z
                   false, false, true,    // Rx, Ry, Rz
                   false, false,          // Rudder, Throttle
                   false, false, false);  // Accelerator, Brake, Steering

void setup() {
  Joystick.begin();
  ps2.begin(9600);  // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(9600);

  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
}

void loop() {
  Serial.print("PS2_TRIANGLE is ");
  Serial.println(ps2.readButton(PS2_TRIANGLE));
  // LED on main board will light up if 'Select' button is pressed
  // if (ps2.readButton(PS2_SELECT) == 0)  // 0 = pressed, 1 = released
  // {
  //   digitalWrite(LEDPIN, HIGH);
  // } else {
  //   digitalWrite(LEDPIN, LOW);
  // }
  if (ps2.readButton(PS2_TRIANGLE) == 0) {
    Joystick.pressButton(0);
  } else {
    Joystick.releaseButton(0);
  }
  if (ps2.readButton(PS2_CROSS) == 0) {}
  if (ps2.readButton(PS2_CIRCLE) == 0) {}
  if (ps2.readButton(PS2_SQUARE) == 0) {}
}
