#include <CapacitiveSensor.h>

CapacitiveSensor   c1 = CapacitiveSensor(2, 3);   //each capacitive sensor object
CapacitiveSensor   c2 = CapacitiveSensor(2, 4); 
CapacitiveSensor   c3 = CapacitiveSensor(2, 5); 
CapacitiveSensor   c4 = CapacitiveSensor(2, 6); 

CapacitiveSensor   c5 = CapacitiveSensor(2, 8);
CapacitiveSensor   c6 = CapacitiveSensor(2, 9); 
CapacitiveSensor   c7 = CapacitiveSensor(2, 10); 
CapacitiveSensor   c8 = CapacitiveSensor(2, 11); 

CapacitiveSensor   play = CapacitiveSensor(2, 33);
CapacitiveSensor   pause = CapacitiveSensor(2, 35);
CapacitiveSensor   record = CapacitiveSensor(2, 30);
CapacitiveSensor   channel = CapacitiveSensor(2, 31);

int c1Val, c2Val, c3Val, c4Val, c5Val, c6Val, c7Val, c8Val;
int playVal, pauseVal, recordVal, channelVal;

int recordChannel;
int channelCount = 1;

const int interval1 = 400;    //bliking intervals for each channel
const int interval2 = 200;
const int interval3 = 100;

int minute = 0;    //for recording the values that the hands return and the values prior to the recorded values
int second = 0;
int minutePrev = 0;
int secondPrev = 0;

int randomHigh, randomLow;
int randomLowSecond;

int note1, note2, note3, note4, note5;    //used for the vocal samples

int on = 0x90;      //typical midi on and off values
int off  = 0x80;

long lastTimeMillis = 0;

boolean currentState1 = LOW;    //to record the state of each sensor and the previous state that it was at
boolean lastState1 = LOW;
boolean currentState2 = LOW;
boolean lastState2 = LOW;
boolean currentState3 = LOW;
boolean lastState3 = LOW;
boolean currentState4 = LOW;
boolean lastState4 = LOW;
boolean currentState5 = LOW;
boolean lastState5 = LOW;
boolean currentState6 = LOW;
boolean lastState6 = LOW;
boolean currentState7 = LOW;
boolean lastState7 = LOW;
boolean currentState8 = LOW;
boolean lastState8 = LOW;

boolean currentStatePlay = LOW;
boolean lastStatePlay = LOW;
boolean currentStatePause = LOW;
boolean lastStatePause = LOW;
boolean currentStateRecord = LOW;
boolean lastStateRecord = LOW;
boolean currentStateChannel = LOW;
boolean lastStateChannel = LOW;

boolean currentStateTwelve = LOW;
boolean lastStateTwelve = LOW;
boolean currentStateOne = LOW;
boolean lastStateOne = LOW;
boolean currentStateTwo = LOW;
boolean lastStateTwo = LOW;
boolean currentStateThree = LOW;
boolean lastStateThree = LOW;
boolean currentStateFour = LOW;
boolean lastStateFour = LOW;
boolean currentStateFive = LOW;
boolean lastStateFive = LOW;
boolean currentStateSix = LOW;
boolean lastStateSix = LOW;
boolean currentStateSeven = LOW;
boolean lastStateSeven = LOW;

boolean currentStateMinuteHigh = LOW;
boolean lastStateMinuteHigh = LOW;
boolean currentStateMinuteLow = LOW;
boolean lastStateMinuteLow = LOW;

boolean currentStateSecond = LOW;
boolean lastStateSecond = LOW;

boolean currentSuperSample = LOW;
boolean lastSuperSample = LOW;

long cm;

void setup() {
  Serial.begin(115200);
    pinMode(51, OUTPUT);  //the two LEDs
    pinMode(53, OUTPUT);
}

void loop() {
  
  c1Val = c1.capacitiveSensor(10);  //retreiving the values returned from each sensor
  c2Val = c2.capacitiveSensor(10);
  c3Val = c3.capacitiveSensor(10);
  c4Val = c4.capacitiveSensor(10);
  c5Val = c5.capacitiveSensor(10);
  c6Val = c6.capacitiveSensor(10);
  c7Val = c7.capacitiveSensor(10);
  c8Val = c8.capacitiveSensor(10);
  playVal = play.capacitiveSensor(10);
  pauseVal = pause.capacitiveSensor(10);
  recordVal = record.capacitiveSensor(10);
  channelVal = channel.capacitiveSensor(10);
  
  minutePrev = minute;  //storing the previous minute and second values
  secondPrev = second;
  minute = analogRead(A0);
  second = analogRead(A1);

//  Serial.print(c1Val); Serial.print("     c2:");   //uncomment for debugging the sensors 1 thru 8
//  Serial.print(c2Val); Serial.print("     c3:");
//  Serial.print(c3Val); Serial.print("     c4:");
//  Serial.print(c4Val); Serial.print("     c5:");
//  Serial.print(c5Val); Serial.print("     c6:");
//  Serial.print(c6Val); Serial.print("     c7:");
//  Serial.print(c7Val); Serial.print("     c8:");
//  Serial.print(c8Val); Serial.print(" --- ");
//  Serial.print(minute); Serial.print("   ");
//  Serial.print(second); Serial.println(" ");

  //-------------------------------for changing the state for each capacative sensor 
  if(c1Val > 100)
    currentState1 = HIGH;
  else
    currentState1 = LOW;
  if(c2Val > 100)
    currentState2 = HIGH;
  else
    currentState2 = LOW;
  if(c3Val > 100)
    currentState3 = HIGH;
  else
    currentState3 = LOW;
  if(c4Val > 100)
    currentState4 = HIGH;
  else
    currentState4 = LOW;
  if(c5Val > 100)
    currentState5 = HIGH;
  else
    currentState5 = LOW;
  if(c6Val > 100)
    currentState6 = HIGH;
  else
    currentState6 = LOW;
  if(c7Val > 100)
    currentState7 = HIGH;
  else
    currentState7 = LOW;
  if(c8Val > 100)
    currentState8 = HIGH;
  else
    currentState8 = LOW;
    
  //------------------------for changing the state for each of the four sub-capoacative sensors
  if(playVal > 100)
    currentStatePlay = HIGH;
  else
    currentStatePlay = LOW;
  if(pauseVal > 100)
    currentStatePause = HIGH;
  else
    currentStatePause = LOW;
  if(recordVal > 100)
    currentStateRecord = HIGH;
  else
    currentStateRecord = LOW;
  if(channelVal > 100)
    currentStateChannel = HIGH;
  else
    currentStateChannel = LOW;
  //--------------------------------to change the state of the record scratches
  if(minute > minutePrev + 10)
    currentStateMinuteHigh = HIGH;
  else
    currentStateMinuteHigh = LOW;
    
  if(minute < minutePrev - 10)
    currentStateMinuteLow = HIGH;
  else
    currentStateMinuteLow = LOW;

  //--------------------------------
  if(digitalRead(A7) == HIGH)
    currentSuperSample = HIGH;
  else
    currentSuperSample = LOW;
    
  //-----------------------------switching up the selections of each vocal sample to have more variety
  if(minute > 900){
    note1 = 52;
    note2 = 53;
    note3 = 54;
    note4 = 55;
    note5 = 56;
  }
  else if(minute > 700){
    note1 = 57;
    note2 = 58;
    note3 = 59;
    note4 = 60;
    note5 = 61;
  }
  else if(minute > 550){
    note1 = 62;
    note2 = 63;
    note3 = 64;
    note4 = 65;
    note5 = 66;
  }
  
  //----------------------------------------- to trigger each sample on the clock
  if(second >= 17 && secondPrev < 17){
    MIDIButton(on, note1);
    MIDIButton(off, note1);
  }
  if(second >= 170 && secondPrev < 170){
    MIDIButton(on, note2);
    MIDIButton(off, note2);
  }
  if(second >= 314 && secondPrev < 314){
    MIDIButton(on, note3);
    MIDIButton(off, note3);
  }
  if(second >= 444 && secondPrev < 444){
    MIDIButton(on, note4);
    MIDIButton(off, note4);
  }
  if(second >= 585 && secondPrev < 585){
    MIDIButton(on, note5);
    MIDIButton(off, note5);
  }
  //--------------------------------------fo the scratch noises going backward on the seconds
  if(second < secondPrev-10 && second > 100)
    currentStateSecond = HIGH;
  else
    currentStateSecond = LOW;

  //--------------------------------------------------- to trigger each sample on the capacative sensors
  if(lastState1 == LOW && currentState1 == HIGH)
  {
    MIDIButton(on, 36);
    lastState1 = HIGH;
  }
  if(lastState1 == HIGH && currentState1 == LOW)
  {
    MIDIButton(off, 36);
    lastState1 = LOW;
  }

  if(lastState2 == LOW && currentState2 == HIGH)
  {
    MIDIButton(on, 37);
    lastState2 = HIGH;
  }
  if(lastState2 == HIGH && currentState2 == LOW)
  {
    MIDIButton(off, 37);
    lastState2 = LOW;
  }

  if(lastState3 == LOW && currentState3 == HIGH)
  {
    MIDIButton(on, 38);
    lastState3 = HIGH;
  }
  if(lastState3 == HIGH && currentState3 == LOW)
  {
    MIDIButton(off, 38);
    lastState3 = LOW;
  }

  if(lastState4 == LOW && currentState4 == HIGH)
  {
    MIDIButton(on, 39);
    lastState4 = HIGH;
  }
  if(lastState4 == HIGH && currentState4 == LOW)
  {
    MIDIButton(off, 39);
    lastState4 = LOW;
  }

  if(lastState5 == LOW && currentState5 == HIGH)
  {
    MIDIButton(on, 40);
    lastState5 = HIGH;
  }
  if(lastState5 == HIGH && currentState5 == LOW)
  {
    MIDIButton(off, 40);
    lastState5 = LOW;
  }

  if(lastState6 == LOW && currentState6 == HIGH)
  {
    MIDIButton(on, 41);
    lastState6 = HIGH;
  }
  if(lastState6 == HIGH && currentState6 == LOW)
  {
    MIDIButton(off, 41);
    lastState6 = LOW;
  }

  if(lastState7 == LOW && currentState7 == HIGH)
  {
    MIDIButton(on, 42);
    lastState7 = HIGH;
  }
  if(lastState7 == HIGH && currentState7 == LOW)
  {
    MIDIButton(off, 42);
    lastState7 = LOW;
  }

  if(lastState8 == LOW && currentState8 == HIGH)
  {
    MIDIButton(on, 43);
    lastState8 = HIGH;
  }
  if(lastState8 == HIGH && currentState8 == LOW)
  {
    MIDIButton(off, 43);
    lastState8 = LOW;
  }

  //-------------------------------------------------------------- to trigger each button (play, pause, record) and to change the channel of the recording. 
  if(currentStatePlay == HIGH && lastStatePlay == LOW)
  {
    MIDIButton(on, 70);
    lastStatePlay = HIGH;
  }
  if(currentStatePlay == LOW && lastStatePlay == HIGH)
  {
    MIDIButton(off, 70);
    lastStatePlay = LOW;
  }

  if(currentStatePause == HIGH && lastStatePause == LOW)
  {
    MIDIButton(on, 71);
    lastStatePause = HIGH;
  }
  if(currentStatePause == LOW && lastStatePause == HIGH)
  {
    MIDIButton(off, 71);
    lastStatePause = LOW;
  }

  if(currentStateRecord == HIGH && lastStateRecord == LOW)
  {
    MIDIButton(on, recordChannel);
    lastStateRecord = HIGH;
  }
  if(currentStateRecord == LOW && lastStateRecord == HIGH)
  {
    MIDIButton(off, recordChannel);
    lastStateRecord = LOW;
  }

  if(currentStateChannel == HIGH && lastStateChannel == LOW)
  {
    channelCount++;
    if(channelCount > 4)
      channelCount = 1;
    lastStateChannel = HIGH;
  }
  if(currentStateChannel == LOW && lastStateChannel == HIGH)
  {
    lastStateChannel = LOW;
  }

  //---------------------------------------------------------------to trigger each record scratch

  if(currentStateSecond == HIGH && lastStateSecond == LOW)
  {
    int newRandomLowSecond = random(88, 92);
    while(newRandomLowSecond == randomLowSecond){
      newRandomLowSecond = random(88, 92);
    }
    randomLowSecond = newRandomLowSecond;
    
    MIDIButton(on, randomLowSecond);
    lastStateSecond = HIGH;
  }
  if(currentStateSecond == LOW && lastStateSecond == HIGH)
  {
    MIDIButton(off, randomLowSecond);
    lastStateSecond = LOW;
  }
  
  if(currentStateMinuteHigh == HIGH && lastStateMinuteHigh == LOW)
  {
    int newRandomHigh = random(92, 96);
    while(newRandomHigh == randomHigh){
      newRandomHigh = random(92, 96);
    }
      randomHigh = newRandomHigh;
   
    MIDIButton(on, randomHigh);
    lastStateMinuteHigh = HIGH;
  }
  if(currentStateMinuteHigh == LOW && lastStateMinuteHigh == HIGH)
  {
    MIDIButton(off, randomHigh);
    lastStateMinuteHigh = LOW;
  }

  if(currentStateMinuteLow == HIGH && lastStateMinuteLow == LOW)
  {
    int newRandomLow = random(88, 92);
    while(newRandomLow == randomLow){
      newRandomLow = random(88, 92);
    }
    randomLow = newRandomLow;
    
    MIDIButton(on, randomLow);
    lastStateMinuteLow = HIGH;
  }
  if(currentStateMinuteLow == LOW && lastStateMinuteLow == HIGH)
  {
    MIDIButton(off, randomLow);
    lastStateMinuteLow = LOW;
  }

  //----------------------------------------------------------------- to trigger each super sample
  if(currentSuperSample == HIGH && lastSuperSample == LOW){
     MIDIButton(on, 100);
     lastSuperSample = HIGH;
  }
  if(currentSuperSample == LOW & lastSuperSample == HIGH){
    MIDIButton(off, 100);
    lastSuperSample = LOW;
  }
    
  //-------------------------------------------------------------- for changing the recordings on everything
  long timeMillis = millis(); //make sure to put the parethesis
  
  if(channelCount == 1){    //no blinking
    digitalWrite(53, LOW);
    recordChannel = 74;
  }
  if(channelCount == 2){    //blinking occasionally
    if(timeMillis - lastTimeMillis > interval1){
      digitalWrite(53, HIGH);
      lastTimeMillis = timeMillis;
    }
    else
      digitalWrite(53, LOW);
    
    recordChannel = 75;
  }
  if(channelCount == 3){    //blinking frequently
    if(timeMillis - lastTimeMillis > interval2){
      digitalWrite(53, HIGH);
      lastTimeMillis = timeMillis;
    }
    else
    recordChannel = 76;
  }
  if(channelCount == 4){    //blinking super freqnently
    if(timeMillis - lastTimeMillis > interval3){
      digitalWrite(53, HIGH);
      lastTimeMillis = timeMillis;
    }
    else
      digitalWrite(53, LOW);
    recordChannel = 77;
  }

  //to trigger the green LED whenever something gets touched
  if(currentState1 == HIGH || currentState2 == HIGH || currentState3 == HIGH || currentState4 == HIGH || currentState5 == HIGH || currentState6 == HIGH || currentState7 == HIGH || currentState8 == HIGH || currentSuperSample == HIGH){
    digitalWrite(51, HIGH);
  }
  else
    digitalWrite(51, LOW);
    
  delay(5);

}

void MIDIButton(int command, int pitch)
  {
     Serial.write(command); Serial.write(pitch); Serial.write(0x60);
     //0x60 is a generic velocity. I wrote it here this time :)
  }

long microsecondsToCentimeters(long microseconds)
{
return microseconds / 29 / 2;
}
