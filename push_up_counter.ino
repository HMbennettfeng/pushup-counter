/* PUSH UP COUNTER

An ultrasonic sensor measures the distance between you and your head, if the distance is larger than 20 cm a rgb-led will shine red,
if the distance is between 10 and 20 cm, it turns magenta
and if it is less than 10 cm it turns blue, and a point appears on a lcd screen.
Every ten pushups it makes a sound.
You can reset the score with the push of a button.
 */
 
#include <LiquidCrystal.h> // include LCD library for lcd screen

#define BLUE 6 // Define RGB-led pins
#define RED 4

const int buttonPin = A0; // Set pins for sensor and button
const int b = 13;
const int trigPin = 2; 
const int echoPin = 3;

int buttonState = 0;// set ints
int x = 1;
int y = 1;
long duration; 
int distance;
int i;
int z;


LiquidCrystal lcd(7, 8, 9, 10, 11, 12l); // Set lcd pins

void setup() {
  Serial.begin(9600); // begin in 9600 baud 
  
  pinMode(trigPin, OUTPUT); //set pin modes
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(b, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  lcd.begin(16, 2); // begin lcd and define 16 by 2
  lcd.print("Push Ups:"); //print pushups on the lcd screen
  lcd.setCursor(0,1);
  lcd.print("Cal:"); //print cal



}

void loop() {
  digitalWrite(trigPin, HIGH); // send an ultrasonic sound and measure the time it took for the sound to go from the trigpin to the echo pin
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2; //convert the time to cm

  if (distance >= 25) {digitalWrite(RED, HIGH); // changing the color of the light depending on distance
                       digitalWrite(BLUE, LOW);}
  if (distance <= 25) {digitalWrite(BLUE, HIGH);}
  if (distance <= 15) {digitalWrite(RED, LOW);}

  if (i == (10 * y) && x == (1 * y)) { 
                 tone(b, 146.8);
                 delay(50);
                 noTone(b);
                 delay(100);
                 tone(b, 146.8);
                 delay(50);
                 noTone(b);
                 delay(50);
                 tone(b, 293.7);
                 delay(100);
                 noTone(b);
                 x ++;
                 y ++;
  }
  else if (distance <= 15) {delay(350);} //this determiens that the time between pushups stays the same
  
  buttonState = digitalRead(buttonPin); //this code makes the button reset the acounter after each press
  if (buttonState == HIGH) {
    i = 0;
    z = 0;
    x = 1;
    y = 1;
    lcd.setCursor(10, 0);
    lcd.print("0      ");
    lcd.setCursor(5, 1);
    lcd.print("0      ");
    } 

  lcd.setCursor(10, 0); // set cursor on the second row
  
  if (distance <= 15 ) {i ++, z += 32;} //print a point after push up
    lcd.setCursor(10, 0);
    lcd.print(i,DEC);                 
    lcd.setCursor(5, 1);
     lcd.print(z,DEC);      
  while (distance <= 15) { //if the distance stays small make sure it only counts one pushup
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034/2;
  delay(100);}
}
