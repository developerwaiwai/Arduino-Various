#include <Servo.h>

#define SENSOR_IN_PIN       0

#define SERVO_PIN           3
#define SENSOR_THRESHOLD  500
#define SERVO_DEGREE_ON   180
#define SERVO_DEGREE_OFF   90

#define LOOP_DELAY       5000

#define SERVO_POWER         2

Servo myservo;

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(SERVO_POWER, HIGH);
  myservo.attach( SERVO_PIN );
  
  Serial.begin(9600); 
}


void loop() {
  
  //input sensor(this case, sensor is optical sensor)
  int sensorIn = analogRead(SENSOR_IN_PIN);
  Serial.println(sensorIn);

  //optocal sensor output small value, if there is in light
  //another side is large value 
  if (sensorIn >= SENSOR_THRESHOLD) {
    
    //output to servo
    myservo.write( SERVO_DEGREE_ON );
    delay(500);
    myservo.write( SERVO_DEGREE_OFF );    
  
  }

  delay(LOOP_DELAY);

}
