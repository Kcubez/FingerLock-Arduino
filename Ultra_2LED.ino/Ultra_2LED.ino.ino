// Define the pins for the ultrasonic sensor and LEDs

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

const int trigPin = 2; // Trigger pin of the ultrasonic sensor
const int echoPin = 3; // Echo pin of the ultrasonic sensor
const int greenLedPin = 4; // Pin for the green LED
const int redLedPin = 5;   // Pin for the red LED
const int buzzerPin = 6;  // Pin for the buzzer

// Variables for ultrasonic distance measurement
long duration;
int distance;

void setup() {
  // ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ///Led pin
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  //buzzer
  pinMode(buzzerPin, OUTPUT);

  // Serial communication for debugging
  Serial.begin(9600);

  //just testing

  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
   lcd.setCursor(0,0);
  lcd.print("hi");
  lcd.setCursor(0,1);
  lcd.print("Hello world");
  lcd.backlight();
  
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Convert the duration to distance (in centimeters)
  distance = duration * 0.034 / 2;

  // Display the distance in the serial monitor (for debugging)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Change LED colors based on distance
  if (distance > 30) {
    // Farther than 50 cm, turn on the green LED and turn off the red LED
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);

    lcd.clear();
    
  } else if(distance <30 && distance >10) {
    // Closer than or equal to 50 cm, turn on the red LED and turn off the green LED
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
      digitalWrite(buzzerPin, LOW);
     lcd.setCursor(0,0);
  lcd.print("Access Approved");
  lcd.setCursor(0,1);
  lcd.print("Welcome");
  }
    else if (distance <10){
      digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    lcd.setCursor(0,0);
  lcd.print("Access Denied");
  lcd.setCursor(0,1);
  lcd.print("Try Again");
   tone(buzzerPin, 1000, 1000); // 1000 Hz for 1 second
  delay(800); // Pause for 1 second
  noTone(buzzerPin);;
    }

  // Delay before the next measurement
  delay(500);
}
