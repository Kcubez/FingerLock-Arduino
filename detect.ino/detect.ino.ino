
#include <Adafruit_Fingerprint.h>
#include <Servo.h>

Servo myservo;

volatile int finger_status = -1;

int  rightPin = D6;
int wrongPin =D7;
int motorPin = D9;

SoftwareSerial mySerial(D2, D1); // TX/RX on fingerprint sensor 2,3 ////(orange,white)
// SoftwareSerial mySerial(2, 3); // TX/RX on fingerprint sensor 2,3 ////(orange,white)


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int lockCheck = 0;

void setup()  
{
  Serial.begin(115200);
  delay(500); // just for node MCU
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  pinMode(rightPin,OUTPUT);
  pinMode(wrongPin,OUTPUT);
  myservo.attach(motorPin); 
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
}

// void loop()                     // run over and over again
// {
  
//   finger_status = getFingerprintIDez();
//   if (finger_status!=-1 and finger_status!=-2){
//     Serial.print("Match");
//     digitalWrite(6,HIGH);
//     myservo.write(180);  // move the servo to 0 degrees
//     digitalWrite(7,LOW);
//     delay(1000);
//     digitalWrite(6,LOW);

//   } else{
//     if (finger_status==-2 ){
      
//         Serial.print("Not Match");
//         digitalWrite(7,HIGH);
//         // move the servo to 0 degrees
//         digitalWrite(6,LOW);
//         delay(1000);
//         digitalWrite(7,LOW);
    
//     }
//   }
//   delay(50);            //don't ned to run this at full speed.
// }

//chat kyee



void loop() {
  finger_status = getFingerprintIDez();
  
  if (finger_status != -1 and finger_status != -2) {
    Serial.print("Match");
    digitalWrite(rightPin, HIGH);

    // Check if the servo is already at 180
    if (lockCheck == 0) {
      myservo.write(180);  // move the servo to 180 degrees
      lockCheck = 1;
      Serial.print(lockCheck);
    }else if (lockCheck ==1){
      myservo.write(0);
      lockCheck = 0 ;
      Serial.print(lockCheck);
    }
    
    digitalWrite(wrongPin, LOW);
    delay(1000);
    digitalWrite(rightPin, LOW);
  } else {
    if (finger_status == -2) {
      Serial.print("Not Match");
      digitalWrite(wrongPin, HIGH);

      digitalWrite(rightPin, LOW);
      delay(1000);
      digitalWrite(wrongPin, LOW);
    }
  }

  delay(50);  // don't need to run this at full speed.
}


// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p!=2){
    Serial.println(p);
  }
  if (p != FINGERPRINT_OK)  return -1;
  
  p = finger.image2Tz();
  if (p!=2){
    Serial.println(p);
  }
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -2;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}





