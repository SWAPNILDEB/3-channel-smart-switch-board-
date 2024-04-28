

#include <DHT.h>
#include<DHT_U.h>
// #include<SoftwareSerial.h>
// Digital pin connected to the DHT sensor
  // DHT 11

#define MotPWM 9
#define LEDpinOn 10
#define SocketOn 11
#define ModeSelector A3
#define LDR A2
#define DHTPIN A1
#define FanRegulator A0


#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

int threshold =10;
int cntrld=0;
void mode1(){

  
   int Regulator=analogRead(FanRegulator);
    cntrld=map(Regulator,0,1023,0,255);
    analogWrite(MotPWM,cntrld);
    digitalWrite(LEDpinOn,HIGH);
    digitalWrite(SocketOn,HIGH);
   
   
}

void mode2(){

  
    delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.println("");
if(t>30 && t<31)
  {
     analogWrite(MotPWM,11*t);
  }
 if(t>15 && t<=20)
   {
      analogWrite(MotPWM,5*t);
   }
else
   {
     analogWrite(MotPWM,5*t);
   }
////////////////////////////////////////
 int luminosity=analogRead(LDR);

  if(luminosity<threshold)
    {
      digitalWrite(LEDpinOn,HIGH); //10
    }
  else
    {
      digitalWrite(LEDpinOn,LOW);  //10
    }

   digitalWrite(SocketOn,LOW);
   

  
}

void mode3(){

 // #include<SoftwareSerial.h>
// SoftwareSerial mySerial (2, 3);  //RX , TX
// #define led1 9
// #define led2 10
// #define led3 11

String val;
int i =500; 

while(i > 0) {
  // put your main code here, to run repeatedly:
  // if(mySerial.available() == 1)
digitalWrite(LEDpinOn,LOW);
  if(Serial.available() == 1)
  {
    // val = mySerial.readString();
    val = Serial.readString();

    val.trim();
    Serial.println(val);
    if(val.length() > 3)
    {
      val.remove(0, val.length()-3);
      if(val.indexOf(',') == 0)
      {
        val.remove(0, 1);
      }
    }
    else
    {
      if(val.indexOf(',') == 0)
      {
        val.remove(0, 1);
      }
    }
    int num = val.toInt();
    if(num <= 100)
    {
      int pwm_val = map(num, 0, 100, 0, 255);
      analogWrite(9, pwm_val);
    }
    if(num >= 200 && num <= 300)
    {
      int pwm_val = map(num, 200, 300, 0, 255);
      analogWrite(10, pwm_val);
    }
    if(num >= 400 && num <= 500)
    {
      int pwm_val = map(num, 400, 500, 0, 255);
      analogWrite(11, pwm_val);
    }   
  }
   i = i-1;
 }
 
}


void setup()
   {
     dht.begin();
     
    
   
       pinMode(MotPWM, OUTPUT);
       pinMode(LEDpinOn, OUTPUT);
       pinMode(SocketOn, OUTPUT);
 
    Serial.begin(9600);
    Serial.println("GROUP 5 IE LAB");
}
void loop(){
  int Mode=analogRead(ModeSelector);  //A3
  if(Mode<341){
    Serial.println("mode1");
    mode1();
  }
  if(Mode>=341 && Mode<682){
    Serial.println("mode2");
    mode2();
  }
  if(Mode>682){
    Serial.println("mode3");
    mode3();
  }
delay(500);

}
