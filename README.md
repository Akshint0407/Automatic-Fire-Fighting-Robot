# Arduino Firefighting Robot with Obstacle Detection

## Project Overview
This project is an Arduino-based firefighting robot designed to detect and respond to flames, navigate around obstacles, and follow a path. The robot uses various sensors to detect fires, measure distances, and determine the presence of obstacles. When a flame is detected, it activates a water pump and nozzle system to extinguish the fire. The robot is equipped with servo motors to scan surroundings and make movement decisions based on sensor input.

## Features
- **Flame Detection**: Uses a flame sensor to detect the presence of fire. Upon detection, the robot stops moving and activates the water pump and nozzle to attempt to extinguish the fire.
- **Obstacle Avoidance**: Utilizes an ultrasonic sensor to measure distances and avoid obstacles in the surroundings. The robot can move forward, turn left, turn right, or reverse based on obstacle detection.
- **Line Following**: Includes line-following sensors to help the robot stay on a designated path, allowing it to move along a pre-defined route.
- **Servo Motor Scanning**: Uses a servo motor to scan the surroundings (0°, 90°, and 180°) for obstacles, enabling intelligent navigation decisions.

## Components Used
- **Arduino**: The core controller for managing sensor data, motor movements, and decision-making.
- **Servo Motor**: Used to rotate the ultrasonic sensor to scan the surroundings.
- **Ultrasonic Sensor**: Measures distance to obstacles to avoid collisions and choose the correct path.
- **Flame Sensor**: Detects the presence of a flame.
- **Line Following Sensors**: Guides the robot along a specified path.
- **DC Motors**: Controls movement of the robot for forward, backward, left, and right navigation.
- **Water Pump and Nozzle**: Activated when a flame is detected to extinguish the fire.

## Code Structure
- **Setup**: Initializes all components and sensors, setting up pins and starting serial communication for debugging.
- **Loop**: Continuously scans the surroundings, checks for fire, and controls the robot's movements based on sensor input.
- **Functions**:
  - `ScanSurrounding()`: Uses the servo to move the ultrasonic sensor to different angles (0°, 90°, 180°) and measures distances.
  - `Read_Ultrasonic_sensor_Value()`: Reads the ultrasonic sensor to measure distance to obstacles.
  - `Forward()`, `Reverse()`, `Right()`, `Left()`: Controls the robot’s movement in respective directions.
  - `Enable_Motor()`, `Disable_Motor()`: Controls the DC motors for movement.
  - `Read_Flame_Sensor_Value()`: Reads the flame sensor and triggers the fire suppression system if a flame is detected.

## How It Works
1. **Initialization**: The robot initializes its components and positions the servo motor at a 90° angle.
2. **Scanning and Obstacle Detection**: The robot continuously scans its surroundings at three angles (0°, 90°, 180°) using the ultrasonic sensor to detect obstacles.
3. **Flame Detection and Suppression**: If a flame is detected, the robot stops, activates the water pump, and sprays water to extinguish the fire.
4. **Navigation**: Based on the distance readings from the ultrasonic sensor, the robot makes navigation decisions to avoid obstacles, choosing the most open path.
5. **Line Following**: Line-following sensors keep the robot on a designated path, guiding it to follow a pre-defined route if needed.

## Circuit Diagram
(https://github.com/Akshint0407/Automatic-Fire-Fighting-Robot/blob/main/fire-fighting%20diagram.jpg)
## Installation

1. **Arduino IDE**: Download and install the [Arduino IDE](https://www.arduino.cc/en/software) if you haven't already.
2. **Download the Code**: Download or clone this repository to your local machine.
3. **Open the Project**: Open the `.ino` file (preferably named `Firefighting_Robot.ino`) in the Arduino IDE.
4. **Library Setup**: This project requires the `Servo.h` library, which comes pre-installed with the Arduino IDE. Ensure it is available under **Sketch > Include Library**.

## Usage

1. **Upload the Code**: Connect your Arduino board to your computer via USB, select the correct **Port** and **Board** in the Arduino IDE, and upload the code.
2. **Connect Components**: Assemble the robot by connecting each component to the Arduino as specified in the code's pin definitions:
   - Motors, ultrasonic sensor, flame sensor, line sensors, pump, and nozzle as per the `pinMode()` definitions.
3. **Power On**: Power on the robot. It should start initializing and then begin scanning its surroundings, detecting obstacles, and searching for flames.
4. **Operation**: Place the robot in an environment with potential obstacles and/or flames (simulated with a lighter or small flame, under safe supervision). The robot will avoid obstacles, detect fire, and attempt to extinguish it by spraying water.

## Troubleshooting

- **Servo Motor Not Scanning**: 
   - Check if the servo motor is correctly connected to the defined pin (Pin 2 by default). Ensure power and ground connections are secure.
   - Make sure the servo is not obstructed physically and has enough voltage.
   
- **No Flame Detection**: 
   - Ensure that the flame sensor is connected correctly and operational.
   - Test the flame sensor separately to confirm that it can detect flames. Adjust its sensitivity if possible.

- **Obstacle Detection Not Working**:
   - Verify the ultrasonic sensor connections. Ensure the `echo` and `trigger` pins match those in the code.
   - Test the ultrasonic sensor separately to ensure it’s reading distances accurately.
   
- **Motors Not Moving**:
   - Check motor driver connections and ensure the enable pins have sufficient voltage.
   - Test the motors separately to confirm they are operational.
   - Verify that the battery or power source has enough power to drive the motors.

## Code
The code for this project is provided in the [main `.ino` file](./Firefighting_Robot.ino).

## License
This project is open-source and available for modification and reuse under the MIT License.

