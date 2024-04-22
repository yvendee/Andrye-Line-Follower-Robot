#include "Keypad.h"

long duration1;
int distance1;

const int trigPin = 12;
const int echoPin = 13;

// IR Sensors
int IRSensorL = A0; //IR left
int IRSensorR = A1; //IR right

// Motor A connections
int enA = 6;
int in1 = 7;
int in2 = 8;
// Motor B connections
int enB = 10;
int in3 = 9;
int in4 = 11;


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);

  //IR sensors
  pinMode(IRSensorL, INPUT);
  pinMode(IRSensorR, INPUT); 

  //Ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

}

void moveForward() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnLeft() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
  
void loop(){

  int leftSensorValue = digitalRead(IRSensorL);
  int rightSensorValue = digitalRead(IRSensorR);

  // Check sensor values
  if (leftSensorValue == LOW && rightSensorValue == LOW) {
    // Both sensors are on the line
    // Move forward
    moveForward();
  } else if (leftSensorValue == LOW && rightSensorValue == HIGH) {
    // Left sensor is on the line
    // Turn right
    turnRight();
  } else if (leftSensorValue == HIGH && rightSensorValue == LOW) {
    // Right sensor is on the line
    // Turn left
    turnLeft();
  } else {
    // Both sensors are off the line
    // Stop
    stopMotors();
  }

  // // Clears the trigPin
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // // Sets the trigPin on HIGH state for 10 micro seconds
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  // // Reads the echoPin, returns the sound wave travel time in microseconds
  // // duration1 = pulseIn(echoPin, HIGH, 1000000);
  // duration1 = pulseIn(echoPin, HIGH, 10000);
  // // Calculating the distance
  // distance1 = duration1 * 0.034 / 2;
  // // Prints the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.println(distance1);

  char key = keypad.getKey();// Read the key
  
  // Print if key pressed
  if (key){
    Serial.print("Key Pressed : ");
    Serial.println(key);
  }

  


  
}
