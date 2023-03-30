/*
 *        LOADCELL              Arduino
 *           VCC                  5V
 *           SCK                  3
 *           DT                   2
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

#define TRIGGER_PIN  8 
#define ECHO_PIN     7 
#define MAX_DISTANCE 230 
#define distance_offset 200

HX711 scale;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int kl;
int Weight;
float height;

void setup()
{       		
  Serial.begin(9600);
  Setup_Loadcell();
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
  delay(20);
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


void ReadWeight(){
  Serial.print("W:");
  Serial.print(scale.get_units(10), 1);
  Serial.print("kg,");

  scale.power_down();              // put the ADC in sleep mode
  delay(20);
  scale.power_up();
}
