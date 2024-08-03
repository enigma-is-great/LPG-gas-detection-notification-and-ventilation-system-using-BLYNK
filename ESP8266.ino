
//Change Blynk Authenticaation Details
#define BLYNK_TEMPLATE_ID "TMPL31rDef9D_"
#define BLYNK_TEMPLATE_NAME "GAS detection"
#define BLYNK_AUTH_TOKEN "__BLYK__API_TOKEN__"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "__wifi__";  // Enter your wifi name
char pass[] = "123456789";  // Enter your wifi password
int smokeA0 = A0;
int data = 0;
int sensorThres = 100;


BlynkTimer timer;

void sendSensor(){
 
 int data = analogRead(smokeA0);
 Blynk.virtualWrite(V0, data);
  Serial.print("Pin A0: ");
  Serial.println(data);


  if(data > 200)     // Change the Trashold value
  {

    Blynk.logEvent("gas_alert","Gas Leakage Detected");
  }
}

void setup(){
  pinMode(smokeA0, INPUT);
   Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  //dht.begin();
  timer.setInterval(250L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
