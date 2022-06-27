#define BUTTON_PIN 21
#define BUTTON_PIN1 15

const int trigPin = 12;
const int echoPin = 14;
// GIOP21 pin connected to button
#include "BluetoothSerial.h";
BluetoothSerial ESP_BT;
#define DELAY 1000
// Variables will change:
int lastState = HIGH; 
int currentState;   
int lastState1 = HIGH; 
int currentState1;   


//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define DISTANCE_THRESHOLD 10
#define BUZZER_PIN 4
long duration;
float distanceCm;

void setup() {
  Serial.begin(9600);
  ESP_BT.begin("ESP32_Control");
  // initialize the pushbutton pin as an pull-up input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
   pinMode(BUTTON_PIN1, INPUT_PULLUP);
   
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);
  currentState1 = digitalRead(BUTTON_PIN1);
 


  if(lastState == LOW && currentState == HIGH)
  {
    Serial.println("The state changed from LOW to HIGH");
    ESP_BT.write(10);
  }
  if(lastState1 == LOW && currentState1 == HIGH)
  {
    Serial.println("button 2 sett");
    ESP_BT.write(20);
  }
 

  // save the last state
  lastState = currentState;
  lastState1 = currentState1;
  

   //Ultrasonic sensor part

   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
if (distanceCm < DISTANCE_THRESHOLD)
    digitalWrite(BUZZER_PIN, HIGH); // turn on Piezo Buzzer
  else
    digitalWrite(BUZZER_PIN, LOW);  // turn off Piezo Buzzer
 
  
  // Prints the distance in the Serial Monitor
Serial.print("Distance (cm): ");
Serial.println(distanceCm);
  

  
  //delay(1000);
}
