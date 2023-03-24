/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-button-servo-motor
 */


#include <Servo.h>
#include <ezButton.h>


#define BUTTON_PIN 21 // ESP32 pin GIOP21 connected to button's pin
#define SERVO_PIN  26 // ESP32 pin GIOP26 connected to servo motor's pin


ezButton button(BUTTON_PIN); // create ezButton object that attach to pin 7;
Servo servo;                 // create servo object to control a servo


// variables will change:
int angle = 0; // the current angle of servo motor


void setup() {
  Serial.begin(9600);         // initialize serial
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  servo.attach(SERVO_PIN);    // attaches the servo on pin 9 to the servo object


  servo.write(angle);
}


void loop() {
  button.loop(); // MUST call the loop() function first


//opens valve
  if (button.isPressed()) { 		
    // change angle of servo motor
    if (angle == 0)
      angle = 90;
    else if (angle == 90)
      angle = 0;


    // control servo motor according to the angle
    Serial.print("The button is pressed => rotate servo to ");
    Serial.print(angle);
    Serial.println("°");
    servo.write(angle);
  }
}
