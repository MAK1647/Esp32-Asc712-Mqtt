  /*************************************************** 
  NodeMCU
****************************************************/ 
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "mqtt.h"
//#include <DHT.h>
//#include <ACS712.h>
#include <Adafruit_MQTT.h> 
#include <Adafruit_MQTT_Client.h> 



 
WiFiClient client; 

Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD); 
Adafruit_MQTT_Client mqttid(&client, MQTT_SERVER, MQTT_PORT, MQTT_ID, MQTT_USERNAME, MQTT_PASSWORD); 
/****************************** Feeds ***************************************/ 

Adafruit_MQTT_Publish pi_asc = Adafruit_MQTT_Publish(&mqttid, MQTT_USERNAME "/strigger/asc"); 

/************************* WiFi Access Point *********************************/ 


int dem = 0;


/*************************** Sketch Code ************************************/ 
void MQTT_connect(); 
//double getVPP();

void setup() { 
 Serial.begin(115200); 
 delay(10); 
 pinMode(LED_PIN, OUTPUT); 
// pinMode(button1.PIN, INPUT_PULLUP);
 //attachInterrupt(button1.PIN, isr, FALLING);
 pinMode(RELAY1, OUTPUT); 
  pinMode(RELAY2, OUTPUT);
   pinMode(RELAY3, OUTPUT);
   pinMode(RELAY4, OUTPUT);
   pinMode(RELAY5, OUTPUT);
   pinMode(RELAY6, OUTPUT);
   pinMode(RELAY7, OUTPUT);
 digitalWrite(RELAY1, HIGH);
 digitalWrite(RELAY2, HIGH);
 digitalWrite(RELAY3, HIGH);
 digitalWrite(RELAY4, HIGH);
 digitalWrite(RELAY5, HIGH);
 digitalWrite(RELAY6, HIGH);
 digitalWrite(RELAY7, HIGH);
 digitalWrite(LED_PIN, LOW); 

 
 pinMode(button_status, INPUT);

 
 //cam bien nhiet do
pinMode(ASC_PIN, INPUT);

 ///////////

 
 Serial.println(F("RPi-ESP-MQTT")); 
 // Connect to WiFi access point. 
 Serial.println(); Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(WLAN_SSID); 
 WiFi.begin(WLAN_SSID, WLAN_PASS); 
 while (WiFi.status() != WL_CONNECTED) { 
   delay(500); 
   Serial.print("."); 
 } 
 Serial.println(); 
 Serial.println("WiFi connected"); 
 Serial.println("IP address: "); Serial.println(WiFi.localIP()); 
 // Setup MQTT subscription for esp8266_led feed. 
// mqtt.subscribe(&esp32_led); 
} 

void loop() { 
  
 int buttonStatus = digitalRead(button_status);
 
 MQTT_connect(); 

 
//////dong dien
float currentt= 0;

for(int i = 0; i < 1000; i++){

  currentt =  currentt + ((3.9 / 4095.0)* (4095-analogRead(ASC_PIN))-0.955)/ 0.066;

 }

 
 Serial.println(4095-analogRead(ASC_PIN));

 Serial.print("Current :");
 Serial.print(String(currentt/1000).c_str());
 Serial.println("A");
 //sprintf(buff_msg, "%d", average/1000);
pi_asc.publish( String(currentt/1000).c_str());

Serial.println(dem);
if(buttonStatus==LOW)
{
  delay(20);
if(buttonStatus==LOW)
{
dem=dem+1;

if(dem==5)
{
 // dem=0;
  digitalWrite(RELAY1, LOW);
 digitalWrite(RELAY2, LOW);
 digitalWrite(RELAY3, LOW);
 digitalWrite(RELAY4, LOW);
 digitalWrite(RELAY5, LOW);
 digitalWrite(RELAY6, HIGH);
 digitalWrite(RELAY7, HIGH);
}
else if(dem==4)
{
   digitalWrite(RELAY1, LOW);
 digitalWrite(RELAY2, LOW);
 digitalWrite(RELAY3, LOW);
 digitalWrite(RELAY4, LOW);
 digitalWrite(RELAY5, HIGH);
 digitalWrite(RELAY6, HIGH);
digitalWrite(RELAY7, HIGH);
}
else if(dem==3)
{
   digitalWrite(RELAY1, LOW);
 digitalWrite(RELAY2, LOW);
 digitalWrite(RELAY3, LOW);
 digitalWrite(RELAY4, HIGH);
 digitalWrite(RELAY5, HIGH);
digitalWrite(RELAY6, HIGH);
digitalWrite(RELAY7, HIGH);
}
else if(dem==2){
  digitalWrite(RELAY1, LOW);
 digitalWrite(RELAY2, LOW);
 digitalWrite(RELAY3, HIGH);
 digitalWrite(RELAY4, HIGH);
 digitalWrite(RELAY5, HIGH);
 digitalWrite(RELAY6, HIGH);
 digitalWrite(RELAY7, HIGH);
}
else if(dem==1){
   digitalWrite(RELAY1, LOW);
 digitalWrite(RELAY2, HIGH);
 digitalWrite(RELAY3, HIGH);
 digitalWrite(RELAY4, HIGH);
 digitalWrite(RELAY5, HIGH);
 digitalWrite(RELAY6, HIGH);
 digitalWrite(RELAY7, HIGH);
}
else if(dem==6){
  digitalWrite(RELAY1, LOW);
 digitalWrite(RELAY2, LOW);
 digitalWrite(RELAY3, LOW);
 digitalWrite(RELAY4, LOW);
 digitalWrite(RELAY5, LOW);
 digitalWrite(RELAY6, LOW);
 digitalWrite(RELAY7, HIGH);
}
else if(dem>=7){
  dem=0;
 digitalWrite(RELAY1, LOW);
 digitalWrite(RELAY2, LOW);
 digitalWrite(RELAY3, LOW);
 digitalWrite(RELAY4, LOW);
 digitalWrite(RELAY5, LOW);
 digitalWrite(RELAY6, LOW);
 digitalWrite(RELAY7, LOW);
}
}
}
delay(2000);


} 
// Function to connect and reconnect as necessary to the MQTT server. 

void MQTT_connect() { 
 uint8_t ret; 
 // Stop if already connected. 
 if (mqtt.connected()) { 
   return; 
 } 
 Serial.print("Connecting to MQTT... "); 
 uint8_t retries = 3; 
 while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected 
      Serial.println(mqtt.connectErrorString(ret)); 
      Serial.println("Retrying MQTT connection in 5 seconds..."); 
      mqtt.disconnect(); 
      delay(5000);  // wait 5 seconds 
      retries--; 
      if (retries == 0) { 
        // basically die and wait for WDT to reset me 
        while (1); 
      } 
 } 
 Serial.println("MQTT Connected!"); 
}




