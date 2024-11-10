#include <Servo.h>    // Header file for Servo Motor.

Servo myservo;        // Creating object for servo motor

// Motor pins
#define motor11 9             // Right Motor pins
#define motor12 8
#define motor21 12            // Left Motor pins
#define motor22 13
#define enable11 10           // Right Motor enable pin 
#define enable22 11           // Left Motor enable pin 

// Sensor pins
#define echo  6               // Ultrasonic's echo pin
#define Trigg 5               // Ultrasonic's Trigger pin
#define flamePin A0           // Flame sensor pin
#define lineSensorPin1 A1     // Line follower sensor pin 1
#define lineSensorPin2 A2     // Line follower sensor pin 2

// Actuator pins
#define pumpPin 4             // Pump control pin
#define nozzlePin 3           // Nozzle control pin

// Variables for obstacle distances at different angles
long obstacle_0, obstacle_90, obstacle_180;  // Obstacles at 0°, 90°, and 180° respectively.

// Function prototypes
void Reverse(void);             // Reverse()
void Right(void);               // Right() Direction
void Left(void);                // Left() Direction
void Forward(void);             // Forward() Direction
void Disable_Motor(void);       // Stop motors   
void Enable_Motor(void);        // Start motors
long Read_Ultrasonic_sensor_Value(void); // Get distance from ultrasonic sensor
void ScanSurrounding(void);     // Look for obstacles
int Read_Flame_Sensor_Value(void); // Read flame sensor value
int Read_Line_Sensor_Value1(void); // Read line follower sensor value 1
int Read_Line_Sensor_Value2(void); // Read line follower sensor value 2

void setup() {
  Serial.begin(115200);         // Serial communication
  pinMode(motor11, OUTPUT);     // L298 Pin mode assigning
  pinMode(motor12, OUTPUT);
  pinMode(motor21, OUTPUT);
  pinMode(motor22, OUTPUT);
  pinMode(enable11, OUTPUT);
  pinMode(enable22, OUTPUT);

  pinMode(echo, INPUT);         // Ultrasonic sensor pins
  pinMode(Trigg, OUTPUT);

  pinMode(flamePin, INPUT);     // Flame sensor pin

  pinMode(lineSensorPin1, INPUT);   // Line follower sensor pins
  pinMode(lineSensorPin2, INPUT);

  pinMode(pumpPin, OUTPUT);     // Pump and nozzle control pins
  pinMode(nozzlePin, OUTPUT);

  Serial.println("Obstacle detector Robot is about to start");
  myservo.attach(2);            // Servo motor's signal Pin
  delay(50);                    // Signal processing delay
  myservo.write(90);            // Move servo to 90 degrees
  delay(2000);
}

void loop() {
  ScanSurrounding();
  while (true) {
    int flameValue = Read_Flame_Sensor_Value();
    if (flameValue == HIGH) {  // Flame detected, stop and take action
      Serial.println("Flame detected! Taking action.");
      Disable_Motor();
      digitalWrite(pumpPin, HIGH);    // Start the pump
      digitalWrite(nozzlePin, HIGH);  // Activate the nozzle
      delay(5000);                    // Delay for fire suppression
      digitalWrite(pumpPin, LOW);     // Stop the pump
    } 
    else if (obstacle_90 > 70) {      // No obstacle detected, move straight
      Serial.println("No obstacle detected at 90 degrees");
      myservo.write(90);
      delay(500);
      Forward();
      Enable_Motor();
      while (obstacle_90 > 30) {      // Keep moving until an obstacle is detected
        obstacle_90 = Read_Ultrasonic_sensor_Value();
        Enable_Motor();
      }
      Disable_Motor();               // Stop motors on obstacle detection
    } 
    else if ((obstacle_0 > obstacle_180) && (obstacle_0 > 100)) { // Turn right if right side is clear
      Serial.println("No obstacle detected at the right side, so turning right");
      Right();
      Enable_Motor();
      delay(500);
      Disable_Motor();
    } 
    else if ((obstacle_0 < obstacle_180) && (obstacle_0 > 100)) { // Turn right if right side is clear
      Serial.println("No obstacle detected at the right side, so turning right");
      Right();
      Enable_Motor();
      delay(500);
      Disable_Motor();
    } 
    else if ((obstacle_0 < obstacle_180) && (obstacle_180 > 100)) { // Turn left if left side is clear
      Serial.println("No obstacle detected at the left side, so turning left");
      Left();
      Enable_Motor();
      delay(500);
      Disable_Motor();
    } 
    else {                               // If obstacles are on both sides, move backward
      Serial.println("Obstacle detected on both sides, moving backward");
      while ((obstacle_0 < 100) || (obstacle_180 < 100)) { // Keep moving back until space is found
        Reverse();
        Enable_Motor();
        delay(500);
        Disable_Motor();
        ScanSurrounding();
      }
      if (obstacle_0 > 70) {
        Right();
      } else if (obstacle_180 > 70) {
        Left();
      }
      Enable_Motor();
      delay(500);
      Disable_Motor();
    }
    ScanSurrounding();
  }
}

void ScanSurrounding(void) {
  Serial.println("Scanning surrounding");
  myservo.write(0);
  delay(800);
  obstacle_0 = Read_Ultrasonic_sensor_Value();

  myservo.write(90);
  delay(800);
  obstacle_90 = Read_Ultrasonic_sensor_Value();

  myservo.write(180);
  delay(800);
  obstacle_180 = Read_Ultrasonic_sensor_Value();
}

long Read_Ultrasonic_sensor_Value(void) {     // Distance calculation
  long dist = 0;
  digitalWrite(Trigg, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigg, LOW);
  dist = pulseIn(echo, HIGH) / 10;
  if (dist > 170) {           // Avoid garbage values
    dist = 170;
  }
  Serial.print("Distance is --> ");
  Serial.println(dist);
  return dist;
}

void Enable_Motor(void) {
  analogWrite(enable11, 255);
  analogWrite(enable22, 255);
}

void Disable_Motor(void) {
  analogWrite(enable11, 0);
  analogWrite(enable22, 0);
}

void Forward(void) {               // Forward() Direction
  digitalWrite(motor11, HIGH);
  digitalWrite(motor12, LOW);
  digitalWrite(motor21, LOW);
  digitalWrite(motor22, HIGH);
}

void Right(void) {                 // Right() Direction
  digitalWrite(motor11, LOW);
  digitalWrite(motor12, HIGH);
  digitalWrite(motor21, LOW);
  digitalWrite(motor22, HIGH);
}

void Left(void) {                  // Left() Direction
  digitalWrite(motor11, HIGH);
  digitalWrite(motor12, LOW);
  digitalWrite(motor21, HIGH);
  digitalWrite(motor22, LOW);
}

void Reverse(void) {               // Reverse()
  digitalWrite(motor11, LOW);
  digitalWrite(motor12, HIGH);
  digitalWrite(motor21, HIGH);
  digitalWrite(motor22, LOW);
}
