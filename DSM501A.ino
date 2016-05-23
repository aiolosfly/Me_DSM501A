#include "MeOrion.h"
#include <SoftwareSerial.h>

const int pin = 2 ;// the input pin connect the Vout2 of Dust Sensor 
MeHumiture humiture(PORT_6);
MeSerial mySerial(PORT_5);


unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

float pm25val = 0; 
float pm25coef = 0.00207916725464941;//The coefficient of pm2.5

void setup() 
{
  //Serial.begin(9600);
  
  mySerial.begin(9600);
  pinMode(2,INPUT);
  starttime = millis();//to get the machine running time ,the unit is ms.
}

void print_temperature_humidity(void)
{
//  float tmp = 28.90;
//  float humidity = 45.7;

  
  mySerial.print("CLS(0);"); // clear the screen with c color .See the example Me_TFT. 
  mySerial.print("DR0;");    // the screen displays in upright way
  mySerial.print("DS24(0,0,'Humidity (%): ");
  mySerial.print( humiture.getHumidity() );
 //mySerial.print(humidity);
  mySerial.print(" ',2);");
  
  mySerial.print("DS24(0,32,'Temperature (oC) = ");
  mySerial.print( humiture.getTemperature() );
  //mySerial.print(tmp);
  mySerial.println(" ',2);");


  } 

  void print_DSM501A_particle(void)
{
  mySerial.print("CLS(0);"); // clear the screen with c color 
  mySerial.print("DR0;");    // the screen displays in upright way

  mySerial.print("DS24(0,0,'LPoccupy: ");//DS
  mySerial.print(lowpulseoccupancy);
  mySerial.print(" ',2);");
 // Serial.println(lowpulseoccupancy);
  
  mySerial.print("DS24(0,32,'Ratio(%): ");
  mySerial.print( ratio );
  mySerial.print(" ',2);");
//  Serial.println(ratio);

  mySerial.print("DS24(0,64,'concentration(pcs/0.01cft): ',2);");
  mySerial.print("DS24(0,96,'");
  mySerial.print(concentration );
  mySerial.print(" ',2);");
 // Serial.println(concentration);

  mySerial.print("DS24(0,128,'PM25 value(ug/m3): ");
  mySerial.print(pm25val);
  mySerial.println(" ',2);");
 // Serial.println(pm25val); 

}


void loop() 
{
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
//  Serial.println(lowpulseoccupancy);
//  Serial.println(sampletime_ms);

  if ((millis()-starttime) > sampletime_ms)
 {
   ratio = lowpulseoccupancy/(sampletime_ms*10);  // Integer percentage 0=>100. The unit for time of low pulse occupancy is us.
   concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
   pm25val = pm25coef * concentration * 10; // 10 to transform 0.01 cf to 0.1 ft

//  Serial.println(lowpulseoccupancy);
//  Serial.println(ratio);
//  Serial.println(concentration);
//  Serial.println(pm25val);
  lowpulseoccupancy = 0;
  starttime = millis();

 }
   humiture.update();
   
  print_DSM501A_particle(); 
    delay(1000);
  print_temperature_humidity();
    delay(1000);
  
}
