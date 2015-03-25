
#include <Servo.h>

Servo myservo;


void setup() {
  myservo.attach( 3 );
}

void loop() {
  
  int randomDelay = random(100,300);
  int randomValue = random(10, 50);
  myservo.write( randomValue );
  delay(randomDelay);  
}
