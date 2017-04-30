/**
* Pedro Luis Rivera Gómez
* Undergraduate Computer Engineering Student - University of Puerto Rico at Mayagüez
* This program reads the analog input from a potentiometer and maps it as a vector in the interval [-LEDS_PER_SIDE, LEDS_PER_SIDE].
* The vector's magnitude represents the amount of LEDs to be turned on, while the +- sign represents the direction (left or right).
**/
#define POT 0
#define LEDS_PER_SIDE 3
#define MID_LED 6
int leftLEDs[LEDS_PER_SIDE] = {5, 4, 3}; // 5 -> GREEN, 4 -> YELLOW, 3 -> RED
int rightLEDs[LEDS_PER_SIDE] = {7, 8, 9}; // 7 -> GREEN, 8 -> YELLOW, 9 -> RED
int LEDsVector;

void setup() {
  for(int i = 0; i < LEDS_PER_SIDE; i++){
    pinMode(leftLEDs[i], OUTPUT);
    pinMode(rightLEDs[i], OUTPUT);
  }
  digitalWrite(MID_LED, HIGH); // Turning on the centered LED.
  Serial.begin(9600);
}

void loop() {
  LEDsVector = getVector();
  Serial.println(LEDsVector);
  if(LEDsVector > 0){
    executeVector(LEDsVector, rightLEDs);
  }
  else if(LEDsVector < 0){
    executeVector(LEDsVector, leftLEDs);
  }
  else {
    turnOffLEDs(leftLEDs);
    turnOffLEDs(rightLEDs);
  }
}

/**
* Returns an value within the range of [-3, 3].
* The returned value represents the amount of LEDs to be turned on and its direction.
**/
int getVector(){
  return (analogRead(POT) - 512)/170; 
}

/**
* Executes the incomming vector by turning off the oposite LEDs array and turns on the LEDs based on its magnitude.
**/
void executeVector(int vector, int lights[]){
  turnOffOpositeSide(vector);
  vector = abs(vector);
  for(int i = 1; i <= LEDS_PER_SIDE; i++){
    if(i <= vector){
      digitalWrite(lights[i-1], HIGH);
    }
    else{
      digitalWrite(lights[i-1], LOW);
    }
  }
}

/**
* Turns off the oposite side of the vector's direction by considering its sign.
**/
void turnOffOpositeSide(int vector){
  if(vector > 0){
    turnOffLEDs(leftLEDs);
  }
  else if(vector < 0){
    turnOffLEDs(rightLEDs);
  }
}

/**
* Turns off every LED on a given array of LEDs by considering the amount of LEDs per side.
**/
void turnOffLEDs(int LEDs[]){
  for(int i = 0; i < LEDS_PER_SIDE; i++){
    digitalWrite(LEDs[i], LOW);
  }
}
