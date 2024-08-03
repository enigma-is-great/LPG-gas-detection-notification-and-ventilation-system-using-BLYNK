#include <Servo.h>
#include <LiquidCrystal.h>

// LCD Pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// MQ2 Pin
const int gasSensorPin = A0;

// Fan Pin (Gate of MOSFET)
const int fanPin = 9;

// Servo Pin
Servo myservo;
const int servoPin = 10;

// Buzzer Pin
const int buzzerPin1 = 7;
const int ledpin2 = 6;

// LED Pins
const int ledPin1 = 8;
const int irSensorPin = A1;
// Variables for gas level and threshold
int gasLevel = 0;
const int gasThreshold = 100;
int i=0;
void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Gas Monitor");

  // Initialize Serial
  Serial.begin(9600);

  // Initialize Pins
  pinMode(gasSensorPin, INPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(buzzerPin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(irSensorPin, INPUT);

  // Initialize Servo
  myservo.attach(servoPin);
  myservo.write(0); // Start with servo off

  // Initial state
  digitalWrite(fanPin, LOW);
  digitalWrite(buzzerPin1, LOW);
  digitalWrite(ledpin2, HIGH);
  digitalWrite(ledPin1, LOW);

}

void loop() {
  // Read gas sensor
  gasLevel = analogRead(gasSensorPin);

  // Display gas level on LCD
  lcd.setCursor(0, 1);
  lcd.print("Gas Level: ");
  lcd.print(gasLevel);

  // Check if gas level exceeds threshold
  if (gasLevel > gasThreshold) {
    // Activate components
    digitalWrite(fanPin, HIGH);
    digitalWrite(buzzerPin1, HIGH);
    digitalWrite(ledpin2, LOW);

    digitalWrite(ledPin1, HIGH);

    myservo.write(140); // Turn the regulator off
    while (digitalRead(irSensorPin) == HIGH) {
      digitalWrite(buzzerPin1, HIGH);
      delay (50);
      
      
      delay(50);
      digitalWrite(buzzerPin1, LOW);
      delay (100);
   
      delay(200);
      digitalWrite(ledPin1, HIGH);
      delay(50);

      delay(50);
       digitalWrite(ledPin1, LOW);
      delay(50);


    }
    if(digitalRead(irSensorPin) == LOW){
    digitalWrite(buzzerPin1, LOW);
    digitalWrite(ledpin2, HIGH);

    digitalWrite(ledPin1, LOW);

  }
  }
 delay(1000); // Adjust delay as needed
}
