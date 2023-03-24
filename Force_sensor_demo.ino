
float cf = 19.5; // caliberation factor
 
int ffs1 = A0; // FlexiForce sensor is connected analog pin A0 of arduino or mega. 
int airSensor  = A1; 
int pump = 4; //sets digital pin 1 as force output
int valve = 2; 
int ffsdata = 0; 
float voutFFS = 0;
float vout; 
void setup()
{
  Serial.begin(9600); 
  pinMode(ffs1, INPUT); 
  pinMode(airSensor, INPUT); 
  pinMode(pump, OUTPUT);   
  pinMode(valve, OUTPUT); 
  
}

void loop()
{
 
 
ffsdata = analogRead(ffs1);
voutFFS = (ffsdata * 5.0) / 1023.0; 
voutFFS = voutFFS * cf ;

/*airSensorData = analogRead(airSensor);
voutAS = airSensorData; // will change this later
//other logic to turn it to voltage

if (voutFFS == 0  && voutAS == 0){
  digitalWrite(pump, 0);
  digitalWrite(valve, 0);
}

if (voutFFS == 1  && voutAS == 1){  
  digitalWrite(valve, 1);
  digitalWrite(pump, 0);
}
 */
  Serial.print("Flexi Force sensor: "); 
 Serial.print(voutFFS,3); 
Serial.println("");
digitalWrite(pump, LOW);
if (voutFFS >= 70){ // if force is detected from sensor then turn pump on
  digitalWrite(pump, HIGH);
delay(500);

//digitalWrite(pump, LOW);
Serial.print("HIgh Flexi Force sensor: "); 
Serial.print(voutFFS,3); 
Serial.println(""); 
}
/* else if (voutFFS < 70) {
    digitalWrite(pump, LOW);
     Serial.print("Low Flexi Force sensor: "); 
Serial.print(voutFFS,3); 
Serial.println(""); 
//delay(500);
  }*/
 
  



/*if(voutAS > 0) {
  digitalWrite(valve, 1); 
}*/

delay(1); 
  
}
