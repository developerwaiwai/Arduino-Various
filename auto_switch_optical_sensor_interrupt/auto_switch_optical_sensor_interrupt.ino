#include <MsTimer2.h>
#include <Servo.h>

//definition of pin assgin
#define SERVO_PIN           5
#define VCC_PIN            13

//definition of servo direction for dgree
#define SERVO_DEGREE_ON   180
#define SERVO_DEGREE_OFF   90

//definition of timer millis
#define SERVO_ON_DELAY   5000
#define SERVO_OFF_DELAY   500
#define CHATTER_DELAY       1

//servo instance
Servo myservo;

void setup() {

  //servo initilize
  myservo.attach(SERVO_PIN);
  servoOutputNeutral();

  //optical sensor's power
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH);
  
  //interrupt port settings
  DDRD = 0;
  PORTD = 0;
  
  PCICR |= _BV(PCIE2);
  PCMSK2 = _BV(PCINT20) ;
  sei();
  
}

ISR(PCINT2_vect)
{
  
  //call if optical sensor value is changed  
  //prevent fault behabior for chatterring
  //wait 1 msec
  MsTimer2::set(CHATTER_DELAY, wakeup);
  MsTimer2::start();
  
}

void wakeup () {
  
  //pin condition
  if(bit_is_set(PIND, 4)) {
    MsTimer2::set(SERVO_ON_DELAY, servoOutput);
    MsTimer2::start();
  } else {
    MsTimer2::stop();
  }

}

void servoOutput() {
  
  myservo.write( SERVO_DEGREE_ON );
  MsTimer2::set(SERVO_OFF_DELAY, servoOutputNeutral);
  MsTimer2::start();
  
}

void servoOutputNeutral() {

  myservo.write( SERVO_DEGREE_OFF );   

}

void loop() {

  
}
