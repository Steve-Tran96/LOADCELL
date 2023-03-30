/*
 *        LOADCELL1              Arduino
 *           VCC                  5V
 *           SCK                  3
 *           DT                   2
 *           GND                  GND 
 *           
 *        LOADCELL2              Arduino
 *           VCC                  5V
 *           SCK                  5
 *           DT                   4
 *           GND                  GND 
 *             
 *         SRF05                Arduino
 *          VCC                   5V
 *          Trig                  8
 *          Echo                  7
 *          GND                   GND
 */

#include "HX711.h"
#include <NewPing.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const int LOADCELL_DOUT_PIN2 = 4;
const int LOADCELL_SCK_PIN2 = 5;


#define TRIGGER_PIN  8 
#define ECHO_PIN     7 
#define MAX_DISTANCE 230 
#define distance_offset 200

HX711 scale;
HX711 scale2;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int kl;
int Weight;
float height;

void setup()
{       		
  Serial.begin(9600);
  Setup_Loadcell();
  Setup_Loadcell2();
	delay(100);	
}

void loop()
{       
  height = sonar.ping_cm();
  ReadWeight();
  //Serial.println(height);
  height = distance_offset - sonar.ping_cm();
  Serial.print("H:");
  Serial.print(height);
  Serial.println("cm");
  delay(500);
}

void Setup_Loadcell(){
  Serial.println("Initializing the scale");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());     
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20)); 
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);
  scale.set_scale(2280.f);                    
  scale.tare();           // reset the scale to 0
  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());                 
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));      
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  
}

void Setup_Loadcell2(){
  Serial.println("Initializing the scale 2");
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale2.read());     
  Serial.print("read average 2: \t\t");
  Serial.println(scale2.read_average(20)); 
  Serial.print("get value 2: \t\t");
  Serial.println(scale2.get_value(5));   
  Serial.print("get units 2: \t\t");
  Serial.println(scale2.get_units(5), 1);
  scale2.set_scale(2280.f);                    
  scale2.tare();           // reset the scale to 0
  Serial.println("After setting up the scale:");
  Serial.print("read 2: \t\t");
  Serial.println(scale2.read());                 
  Serial.print("read average 2: \t\t");
  Serial.println(scale2.read_average(20));      
  Serial.print("get value 2: \t\t");
  Serial.println(scale2.get_value(5));   
  Serial.print("get units 2: \t\t");
  Serial.println(scale2.get_units(5), 1);  
}

float ReadWeight1(){
  float w1;
  w1 = scale.get_units(10);
//  Serial.print("W1:");
//  Serial.print(w1);
//  Serial.print("kg |");
  delay(10);

  scale.power_down();              // put the ADC in sleep mode
  delay(30);
  scale.power_up();

  return w1;
}

float ReadWeight2(){
  float w2;
  w2 = scale2.get_units(10);
//  Serial.print(" W2:");
//  Serial.print(w2);
//  Serial.println("kg");
  delay(10);
  scale2.power_down();              // put the ADC in sleep mode
  delay(30);
  scale2.power_up();

  return w2;
}

void ReadWeight(){
  float weight ,w1 ,w2;

  w1 = ReadWeight1();
  w2 = ReadWeight2();
  weight = (float)(w1 + w2);
  Serial.print("W:");
  Serial.print(weight);
  Serial.println("kg");
}
