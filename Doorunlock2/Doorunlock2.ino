// Define the pin for the sound sensor
#define SOUND_SENSOR_PIN D1
#include <Servo.h>

Servo myServo;
// Variables to store knock pattern and timing
unsigned long knockTimes[5]; // Stores the time of each knock
int knockCount = 0;
const unsigned long knockThreshold = 200; // Max time between knocks for a valid pattern
bool lastSensorState = LOW; // Last state of the sound sensor
int count =0;
unsigned long lastKnockTime =0;
unsigned long Threshold=10000; //10 sec
void setup() {
  Serial.begin(115200);
  pinMode(SOUND_SENSOR_PIN, INPUT);
  myServo.attach(D4,500,2400);  // Attach the servo on pin D4 to the servo object
myServo.write(165);

}

void servoAction(){

myServo.write(120);
delay(1000);
myServo.write(165);
delay(1000);
}

void loop() {
  
  //get current time
  unsigned long currentTime = millis();

  if(digitalRead(SOUND_SENSOR_PIN)){
    count+=1;
    delay(100);
    if (knockCount < 5) {
      knockTimes[knockCount] = currentTime;
      //Serial.println(knockTimes[knockCount]);
      //delay(2000);
      lastKnockTime =currentTime;
      knockCount++;
    }
  }

  if((currentTime - lastKnockTime) >Threshold){
    //reset counter
    knockCount =0;
    count =0;
  }
  else
  if(knockCount ==5){

    //check for pattern first 
    if ((knockTimes[1] - knockTimes[0] < 700) &&
        (knockTimes[2] - knockTimes[1] >2000 ) &&
        (knockTimes[3] - knockTimes[2] < 700) &&
        (knockTimes[4] - knockTimes[3] < 700)) {
          
          Serial.println("Pattern matched!");
          //call Servo action function
          servoAction();
        }
    else{
          Serial.println("Pattern not matched!");
      
    }
    //reset
    knockCount =0;
    count =0;
  }

}
