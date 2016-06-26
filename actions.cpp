#include "actions.h"

Servo servoLid, servoArm;

//Move: servo moves from start angle to end angle
void Action::moveServo (Servo thisServo, int servopin, int startAngle, int endAngle, int angSpeed) {
  bool angleIncr = false; // boolean to determine if the angle needs to increase or decrease to get to endAngle
  int pos;
  thisServo.attach(servopin);
  if(startAngle < endAngle) angleIncr = true; //if start angle is smaller than end angle then it must increase

  //set servo to start angle
  thisServo.write(startAngle);

  //Increasing servo angle
  if(angleIncr){
    for (pos = startAngle; pos <= endAngle; pos += angSpeed) { // goes from start angle to end angle in steps of angular speed variable
      thisServo.write(pos);           // tell servo to go to position in variable 'pos'
      delay(15);                      // waits 15ms for the servo to reach the position
    }
  }
  //Decreasing servo Angle
  else{
    for(pos = startAngle; pos >= endAngle; pos -= angSpeed) { // goes from end angle to start angle in steps of angular speed variable
      thisServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}

//Shake: move to closed position and shake lid
void Action::shakeServo (Servo thisServo, int servopin) {
  closeLid();//close lid before shaking
  for (int i = 0; i < 10; i++) {//oscillate up and down for 10 cycles
    moveServo(thisServo, servopin, 0, 15, 15); //open quickly (to 10 degrees)
    moveServo(thisServo, servopin, 15, 0, 15); //close quickly (to 10 degrees)
  }
}

//actuateLidLED: A= on B= delayed on C= off D= flicker

void Action::actuateLidLED (char letter) {
  switch (letter)
  {
    //OFF
    case 'A':
    case 'a':
      digitalWrite(pin_lidLight, LOW);
      break;
    //DELAYED ON
    case 'B':
    case 'b':
      delay(delayed_response_timems);
      digitalWrite(pin_lidLight, LOW);
      break;
    //ON
    case 'C':
    case 'c':
      digitalWrite(pin_lidLight, HIGH);
      break;
    //FLICKER
    case 'D':
    case 'd':
      for (int i = 0; i < 5; i++)
      {
        digitalWrite(pin_lidLight, LOW);
        delay(500);
        digitalWrite(pin_lidLight, HIGH);
        delay(300);
        digitalWrite(pin_lidLight, LOW);
        delay(100);
        digitalWrite(pin_lidLight, HIGH);
        delay(500);
      }
      break;

    default:
      //do nothing
      break;
  }
  reset();
}

void Action::actuateRedLED (char letter) {
  switch (letter)
  {
    case 'A':
    case 'a':
      //on
      digitalWrite(pin_redLight, LOW);
      break;

    case 'B':
    case 'b':
      //delayed on
      delay(delayed_response_timems);
      digitalWrite(pin_redLight, LOW);
      break;

    case 'C':
    case 'c':
      digitalWrite(pin_redLight, LOW);
      break;

    case 'D':
    case 'd':
      for (int i = 0; i < 5; i++)
      {
        digitalWrite(pin_redLight, LOW);
        delay(500);
        digitalWrite(pin_redLight, HIGH);
        delay(300);
        digitalWrite(pin_redLight, LOW);
        delay(100);
        digitalWrite(pin_redLight, HIGH);
        delay(500);
      }
      break;

    default:
      //do nothing
      break;
  }

  reset();

}

//actuateLid:  A= normal B= fast C= slow D= shake
void Action::actuateLid (char letter) {
  switch (letter)
  {
    //NORMAL
    case 'A':
    case 'a':
      moveServo(servoLid, pin_servoLid, 0, lidMax, normal);
      break;
    //FAST
    case 'B':
    case 'b':
      moveServo(servoLid, pin_servoLid, 0, lidMax, fast);
      break;
    //SLOW
    case 'C':
    case 'c':
      moveServo(servoLid, pin_servoLid, 0, lidMax, slow);
      break;
    //SHAKE
    case 'D':
    case 'd':
      shakeServo(servoLid, pin_servoLid);
      break;

    default:
      //do nothing
      break;
  }

  //wrapup
}

void Action::actuateArm (char letter) {
  switch (letter)
  {
    //NORMAL
    case 'A':
    case 'a':
      moveServo(servoArm, pin_servoArm, 0, armMax, normal);
      break;
    //FAST
    case 'B':
    case 'b':
      moveServo(servoArm, pin_servoArm, 0, armMax, fast);
      break;
      //SLOW
    case 'C':
    case 'c':
      moveServo(servoArm, pin_servoArm, 0, armMax, slow);
      break;
    //SHAKE
    case 'D':
    case 'd':
      shakeServo(servoArm, pin_servoArm);
      break;

    default:
      //do nothing
      break;
  }

  //wrapup
}

void Action::actuateGooseSound(char letter) {
  switch (letter)
  {
    case 'A':
    case 'a':

      break;

    case 'B':
    case 'b':

      break;

    default:
      //do nothing
      break;
  }

  //wrapup
}


//Close box lid
void Action::closeLid(){
  servoArm.attach(pin_servoLid);
  servoLid.write(0);  //set servo angle to 0/close lid
}

//reset lights arm and lid
void Action::reset(){
  digitalWrite(pin_lidLight, HIGH);
  digitalWrite(pin_redLight, HIGH);
  digitalWrite(pin_goosesound, HIGH);

  servoArm.attach(pin_servoArm);
  servoArm.write(armMax);

  closeLid();
}
