int data;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27,16,2);
#include <ESP32Servo.h>
Servo s1;
#include <DHT.h>
#include "thingProperties.h"
DHT dht(13,DHT11);
void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(1500); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  pinMode(35,INPUT);
  pinMode(19,OUTPUT);
  s1.attach(12);
  lcd.init();
  lcd.backlight();
  
}

void loop() {
  ArduinoCloud.update();
  // Your code here
  
  data=analogRead(35);
  temp=dht.readTemperature();           //temp
  humidity=map(data,4095,0,0,100);      //humidity
  if(pump==0){
    digitalWrite(19,HIGH);
  }
  else if(pump==1){
    digitalWrite(19,LOW);
  }
  if(servo==1){
    s1.write(180);
  }
  else{
    s1.write(0);
  }
  lcd.setCursor(0,0);
  lcd.print("humidity");
  lcd.setCursor(0,1);
  lcd.print("temp");
  lcd.setCursor(10,0);
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(10,1);
  lcd.print(temp);
  lcd.print("%");
  delay(100);
  lcd.clear();
}
/*
  Since Temp is READ_WRITE variable, onTempChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTempChange()  {
  // Add your code here to act upon Temp change
}
/*
  Since Servo is READ_WRITE variable, onServoChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onServoChange()  {
  // Add your code here to act upon Servo change
}
/*
  Since Pump is READ_WRITE variable, onPumpChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPumpChange()  {
  // Add your code here to act upon Pump change
}
