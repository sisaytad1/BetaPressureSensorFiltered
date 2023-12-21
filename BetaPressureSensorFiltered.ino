#include "QuickMedianLib.h"

//**********CONSTANTS TO SET*************
const int pressuresensorpin = 36;
unsigned long DataForMS = 1000; //Collect data for this duration (in ms) before determining val
int NumMedianSamples = 50;
int NumMeanSamples = 20;
//***************************************

//**********Variables used by function**************
float rawdata = 0;
unsigned long LoopStartTime = 0; //Collect data for this duration (in ms) before determining val
unsigned long LoopEndTime = 0; //Collect data for this duration (in ms) before determining val
unsigned long TimeDiff = 0; //Collect data for this duration (in ms) before determining val
int Median = 0;
int Sum = 0;
int Mean = 0;
//**************************************************


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  pinMode(pressuresensorpin, OUTPUT);
}

void loop() {
  //Initialize Arrays
  int MedArray[NumMedianSamples] = {0};

  //Record current time
  LoopStartTime = millis();

  //Collect NumMeanSamples medians and find average
  for (int j = 0; j < NumMeanSamples; j++){
    //Collect NumMedianSamples data points and find median
    for (int i = 0; i < NumMedianSamples; i++){
      rawdata = analogRead(pressuresensorpin);
      MedArray[i] = rawdata;
    }
    Median = QuickMedian<int>::GetMedian(MedArray, NumMedianSamples);
    Sum += Median;
  }
  Mean = Sum/NumMeanSamples;

  //Send Value
  Serial.println(Mean);
  Sum = 0;
  //Delay Appropriate time
  TimeDiff = LoopStartTime - millis();
  delay(DataForMS - TimeDiff);
}

//*************** HELPER FUNCTIONS ******************

