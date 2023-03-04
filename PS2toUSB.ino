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
Cytron_PS2Shield ps2(8, 9); // SoftwareSerial: Rx and Tx pin
// Cytron_PS2Shield ps2; // HardwareSerial

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
                   12, 1,                // Button Count, Hat Switch Count
                   true, true, true,     // X, Y, Z
                   false, false, true,   // Rx, Ry, Rz
                   false, false,         // Rudder, Throttle
                   false, false, false); // Accelerator, Brake, Steering
const int16_t minimum = 0, maximum = 255;
void setup()
{
  Joystick.setXAxisRange(minimum, maximum);
  Joystick.setYAxisRange(minimum, maximum);
  Joystick.setZAxisRange(minimum, maximum);
  Joystick.setRzAxisRange(minimum, maximum);

  Joystick.begin();

  ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(9600);
}
void loop()
{
  // 0 = pressed, 1 = released
  !ps2.readButton(PS2_TRIANGLE) ? Joystick.pressButton(0) : Joystick.releaseButton(0);
  !ps2.readButton(PS2_CIRCLE) ? Joystick.pressButton(1) : Joystick.releaseButton(1);
  !ps2.readButton(PS2_CROSS) ? Joystick.pressButton(2) : Joystick.releaseButton(2);
  !ps2.readButton(PS2_SQUARE) ? Joystick.pressButton(3) : Joystick.releaseButton(3);
  !ps2.readButton(PS2_LEFT_2) ? Joystick.pressButton(4) : Joystick.releaseButton(4);
  !ps2.readButton(PS2_RIGHT_2) ? Joystick.pressButton(5) : Joystick.releaseButton(5);
  !ps2.readButton(PS2_LEFT_1) ? Joystick.pressButton(6) : Joystick.releaseButton(6);
  !ps2.readButton(PS2_RIGHT_1) ? Joystick.pressButton(7) : Joystick.releaseButton(7);
  !ps2.readButton(PS2_START) ? Joystick.pressButton(8) : Joystick.releaseButton(8);
  !ps2.readButton(PS2_SELECT) ? Joystick.pressButton(9) : Joystick.releaseButton(9);
  !ps2.readButton(PS2_JOYSTICK_LEFT) ? Joystick.pressButton(10) : Joystick.releaseButton(10);
  !ps2.readButton(PS2_JOYSTICK_RIGHT) ? Joystick.pressButton(11) : Joystick.releaseButton(11);

  if (!ps2.readButton(PS2_UP))
  {
    Joystick.setYAxis(0);
  }
  else if (!ps2.readButton(PS2_DOWN))
  {
    Joystick.setYAxis(255);
  }
  else
  {
    Joystick.setYAxis(127);
  }

  if (!ps2.readButton(PS2_LEFT))
  {
    Joystick.setXAxis(0);
  }
  else if (!ps2.readButton(PS2_RIGHT))
  {
    Joystick.setXAxis(255);
  }
  else
  {
    Joystick.setXAxis(127);
  }

  Joystick.setRzAxis(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS));
  Joystick.setZAxis(ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS));

  // Serial.println(ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS));
}
