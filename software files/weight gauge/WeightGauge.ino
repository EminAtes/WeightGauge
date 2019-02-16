#include "HX711.h"
#include "TimerOne.h"
#include "SevSeg.h"
#define DOUT  11
#define CLK  12
SevSeg sevseg; 

HX711 scale(DOUT, CLK);

#define MAX_NUMBER_STRINGS 1
#define MAX_STRING_SIZE 3
char testStrings[MAX_NUMBER_STRINGS][MAX_STRING_SIZE];

int start=1;
float calibration_factor = -5900; 
float ort,sumOfData=0,fl=0,tat=0,rawReading=5;
long int startTime,finishTime,loopTime;
int tam=0,ns,n1,n2;
int i,settup=1;
String string="";
void setup() {
  byte numDigits = 3;
  byte digitPins[] = {8,9,10};
  byte segmentPins[] = {1, 0, 2, 3, 4, 5, 6, 7};
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
  
  Timer1.initialize(200000);
  Timer1.attachInterrupt(display_weight);
  scale.set_scale();
  scale.set_scale(calibration_factor); 
  scale.tare();  //Reset the scale to 0
  long zero_factor = scale.read_average(); 
  
  PORTD=0x00;
  sevseg.setNumber(fl,1);
  sevseg.refreshDisplay();
}

char charArray[4];
void loop() {
  if(fl<0)
  fl=0;
  if(fl>50)
  fl=50;
  
  if(fl<10)
  {
  dtostrf(fl, 4, 1, charArray);
  charArray[0]='0';
    
  sevseg.setChars(charArray);
  sevseg.refreshDisplay();
  }else
  {
  sevseg.setNumber(fl,1);
  sevseg.refreshDisplay();
  }
  Serial.println(fl);
}


void display_weight()
{
  fl=scale.get_units();
  
  fl=(fl*(71.75))/1000-0.5;

  
}




