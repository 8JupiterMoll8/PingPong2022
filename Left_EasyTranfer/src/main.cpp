#include <Arduino.h>
#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t pz;
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;

void setup(){
  Serial.begin(9600);

  // while(!Serial)
  // {

  // }
  Serial8.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Serial8);
  
  pinMode(24, OUTPUT);
  digitalWrite(24,LOW);
  
 
  
}

void loop(){

  delay(100);
  mydata.pz = 333;
  ET.sendData();
  digitalWrite(24,HIGH);
  delay(100);
  mydata.pz = 0;
  ET.sendData();
  digitalWrite(24,LOW);
}
