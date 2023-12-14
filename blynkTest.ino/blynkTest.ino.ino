

#define BLYNK_TEMPLATE_ID "TMPL66M6fkBpA"
#define BLYNK_TEMPLATE_NAME "TheftDetect"
#define BLYNK_AUTH_TOKEN "13lGpTis2XDdAcf73hboNFrNHLyiW5ST"
#define BLYNK_PRINT Serial  //idk sure

#include <Adafruit_Fingerprint.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

Servo myservo;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int finger_status = -1;

int rightPin = D6;
int wrongPin = D7;
int relayPin = D5;
int buzzerPin = D8;

SoftwareSerial mySerial(D2, D1); // TX/RX on fingerprint sensor 2,3

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Thar Htet Aung";  // type your wifi name
char pass[] = "tharhtetaung524123";  // type your wifi password

int lockCheck = 0;

BlynkTimer timer;

void notifyOnTheft() {
  
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(100);

  pinMode(rightPin, OUTPUT);
  pinMode(wrongPin, OUTPUT);
   pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for a valid finger...");

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, notifyOnTheft);

  Wire.begin(D3, D4);  //SDA D3 --- SCL D4
  lcd.init();         // initialize the lcd
  lcd.backlight();  
  lcd.setCursor(5, 0);
  lcd.print("Hello");
  delay(1000);
  lcd.clear();
  
}

void loop() {
  finger_status = getFingerprintIDez();

  if (finger_status != -1 && finger_status != -2) {
    Serial.print("Match");
    
    digitalWrite(rightPin, HIGH);

    if (lockCheck == 0) {
     
      lockCheck = 1;
     
      digitalWrite(relayPin, LOW);
      lcd.clear();
       lcd.setCursor(3, 0);
      lcd.print("Welcome");
       delay(1000);
       lcd.clear();
    } else if (lockCheck == 1) {
      
      lockCheck = 0;
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Door Locked ");
      digitalWrite(relayPin, HIGH);
      delay(1000);
      lcd.clear();
    }

    digitalWrite(wrongPin, LOW);
    delay(1000);
    digitalWrite(rightPin, LOW);
  } else {
    if (finger_status == -2) {
      Serial.print("Not Match");
      digitalWrite(wrongPin, HIGH);
      // digitalWrite(relayPin, HIGH);
      digitalWrite(rightPin, LOW);
      lcd.clear();
       lcd.setCursor(3, 0);
      lcd.print("Try Again ");
        digitalWrite(buzzerPin, HIGH);
        delay(1000);

  // Turn off the buzzer for 1 second
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      // digitalWrite(relayPin, HIGH);
     
      
      delay(1000);
      lcd.clear();
      digitalWrite(wrongPin, LOW);

      // Log the event for theft detection
      Blynk.logEvent("theftdetect", "Failed Attempts At Locker");
      
    }
    else if (lockCheck==1){
       lcd.clear();
       lcd.setCursor(2, 0);
    lcd.print("Please Lock ");
      
       lcd.setCursor(3, 1);
    lcd.print("The Door");
      
    }
    else{
      lcd.clear();
       lcd.setCursor(3, 0);
    lcd.print("Place Your");
       lcd.setCursor(0, 1);
    lcd.print("Finger On Sensor");
      
    }
  }

  Blynk.run();
  timer.run();
  delay(50);
}



int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != 2) {
    Serial.println(p);
  }
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != 2) {
    Serial.println(p);
  }
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -2;

  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
