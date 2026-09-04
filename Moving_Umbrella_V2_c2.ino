#include <Servo.h>

Servo myServo;
int servoPos = 20;


void setup() {
  
  myServo.attach(9);// this is for attach the servo to the arduino 
  myServo.write(20);// initial position 
  Serial.begin(9600);//function to define the speed 
  delay(1000);// make 1s pauses between processing
}

void loop() {
  //Read Left and Right LDR' values 
  int left = analogRead(A1); 
  int right = analogRead(A0);

  int diff = (right) - (left);
  // This is just to show the values in the monitor 
  Serial.print("يسار: "); Serial.print(left);
  Serial.print("  يمين: "); Serial.print(right);
  Serial.print("  فرق: "); Serial.print(diff);
  Serial.print("  الموضع: "); Serial.println(servoPos);

  // Condition to turn light to the greatest value of LDR between 55 and -20
if (-diff > 20 && servoPos < 40) {
    servoPos++;
  } else if (-diff < -20 && servoPos > 0) {  // غيرنا 0 إلى 15
    servoPos--;
  }
 
  // إذا الفرق بين -20 و 20 = يوقف مكانه

  myServo.write(servoPos);
  delay(20); // سرعة الحركة
}