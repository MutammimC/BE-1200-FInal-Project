#include <Servo.h>
Servo myservo;

const int SERVO_PIN = 12;

//const int trigPin = placeHolder; Determine what pin these should be
//const int echoPin = placeHolder;

const int BUTTON_PIN_2 = 2;
const int BUTTON_PIN_3 = 3;
const int BUTTON_PIN_4 = 4;
const int BUTTON_PIN_5 = 5;
const int LED_PIN_8 = 8;
const int LED_PIN_9 = 9;
const int LED_PIN_10 = 10;
const int LED_PIN_11 = 11;

int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;

int ledPins[4] = {LED_PIN_8, LED_PIN_9, LED_PIN_10, LED_PIN_11};
int currentLed = -1;

int currentLevel = 1;
int levelSpeeds[5] = {1000, 800, 600, 400, 200};
int levelScores[5] = {0, 0, 0, 0, 0};

unsigned long lastLedChange = 0;
unsigned long winTime = 0;

void setup() {
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
  
  pinMode(trigPin, OUTPUT); // <---trig
  pinMode(echoPin, INPUT);  // <---echo
	
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  myservo.attach(SERVO_PIN);
  
  randomSeed(analogRead(0));
  
  Serial.begin(9600);
  Serial.println("Press any button to start.");
}

bool elevatorReset(int distanceCM){ //If the sensor is protruding from the bottom then level 0 is 8
  bool isElevatorReset = false;
  do{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);   // Reads the echoPin, returns the sound wave travel time in microseconds
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    //Serial.print("Distance: "); 		Don't need the console to spam this
    //Serial.println(distance);
    myServo.writeMicroseconds(1700); 		//Not sure what value would reverse the motor to to go down	
    if (distance == userCM){
      myServo.writeMicroseconds(1500);
      Serial.println("You reached ");
      Serial.print(distanceCM);
      Serial.print(" CM");
      isElevatorReset = true;
      return isElevatoReset;
    } while(distance != distanceCM);
}

void loop() {
  if (currentLevel > 5) {
    Serial.println("Game over!");
    Serial.print("Final score: ");
    Serial.println(levelScores[4]);
    if (levelScores[4] == 5) {
      myservo.writeMicroseconds(1700); // rotate in one direction
      delay(1000);
      myservo.writeMicroseconds(1500); // stop the motor
    } else {
       // rotate in the opposite direction
      delay(1000);
      myservo.writeMicroseconds(1500); // stop the motor
    }
    
    while (true) {
      // Wait forever
    }
  }
  
  if (currentLed == -1) {
    currentLed = random(0, 4);
    digitalWrite(ledPins[currentLed], HIGH);
    lastLedChange = millis();
  }
  
  buttonState2 = digitalRead(BUTTON_PIN_2);
  buttonState3 = digitalRead(BUTTON_PIN_3);
  buttonState4 = digitalRead(BUTTON_PIN_4);
  buttonState5 = digitalRead(BUTTON_PIN_5);
  
  if (buttonState2 == LOW && currentLed == 0) {
    digitalWrite(ledPins[currentLed], LOW);
    currentLed = -1;
    levelScores[currentLevel-1]++;
  }
  if (buttonState3 == LOW && currentLed == 1) {
    digitalWrite(ledPins[currentLed], LOW);
    currentLed = -1;
    levelScores[currentLevel-1]++;
  }
  if (buttonState4 == LOW && currentLed == 2) {
    digitalWrite(ledPins[currentLed], LOW);
    currentLed = -1;
    levelScores[currentLevel-1]++;
  }
  if (buttonState5 == LOW && currentLed == 3) {
    digitalWrite(ledPins[currentLed], LOW);
    currentLed = -1;
    levelScores[currentLevel-1]++;
  }
  
  if (levelScores[currentLevel-1] == 5) {
    Serial.print("Level ");
    Serial.print(currentLevel);
    Serial.println(" complete!");
    currentLevel++;
    delay(1000);
  }
  
  if (currentLed != -1) {
  digitalWrite(ledPins[currentLed], HIGH);
	}
  lastLedChange = millis();}

