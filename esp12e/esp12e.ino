#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

// Network parameters
const char* ssid     = "SMateo49"; //name of wifi
const char* password = "0123456789ab";

// ThingSpeak information
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1330656;
char* readAPIKey = "0123456789abcdef";
char* writeAPIKey = "fedcba9876543210";
const unsigned long postingInterval = 20000;    //20seconds interval to prevent blocking from www service

// Global variables
// These constants are device specific.  You need to get them from the manufacturer or determine them yourself.
float Temp = 10;
float order;

unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0; 
WiFiClient client;


void setup() {
  
  Serial.begin(9600);
  Serial.println();
  Serial.println("Start");

  pinMode(16, OUTPUT);  //on driver
  pinMode(13, OUTPUT);  //working ~1Hz
  pinMode(4, OUTPUT);   //on-line
  pinMode(5, OUTPUT);   //heater

  digitalWrite(16, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);  

  connectWiFi();

  digitalWrite(4, HIGH);
}
//LOOP
void loop() {
    digitalWrite(13, HIGH);
    if(WiFi.status() != WL_CONNECTED){
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      connectWiFi();
      digitalWrite(4, HIGH);
      }

    order = readTSData( channelID, 3);
    
    Temp = regulator(order, Temp);
  
    if (millis() - lastUpdateTime >=  postingInterval) { 
        lastUpdateTime = millis();
        Serial.println(" Temp = " + String(Temp));
        write2TSData( channelID, Temp, float(WiFi.RSSI()));
    }
    else
    {
      delay(500);
    }
    digitalWrite(13, LOW);
    delay(500);
}

void connectWiFi(){
  int n = 0, j= -1;
    while(j<0){
      do{
        j = -1;
        n = 0;
        n = WiFi.scanNetworks();
        Serial.println("Wifi scan ended");
    
        if (n == 0) {
          Serial.println("no networks found");
          WiFi.scanDelete();
        }
        delay(500);
      }while(n == 0);
    
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i) {
        if(WiFi.SSID(i) == ssid) {
          j=i;
          }
        Serial.print(i + 1);
        Serial.print(") ");
        Serial.print(WiFi.SSID(i) + "  ");// SSID
           
        Serial.print(WiFi.RSSI(i));//Signal strength in dBm  
        Serial.print("dBm    ");

        Serial.print(" MAC:");
        Serial.print(WiFi.BSSIDstr(i)  );

        Serial.print("     Encryption:");      
        Serial.print(encType(i));

        if(WiFi.isHidden(i) ){
          Serial.print("     <<Hidden>> ");           
        }

        Serial.println();
        delay(10);
        }
  
    Serial.println("");

    if (j < 0) {
      Serial.println("any known host found");
     }
    WiFi.scanDelete();
    
  }
  
  WiFi.begin(ssid, password);

  Serial.print("Connecting to: "+ String(ssid));
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
  
  ThingSpeak.begin(client);
}


float readTSData( long TSChannel,unsigned int TSField ){
    
  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println( " - Order from TS: " + String(data) + " °C");
  return data;

}

int write2TSData( long TSChannel, long field1Data, long field2Data ){

  ThingSpeak.setField( 1, field1Data );
  ThingSpeak.setField( 2, field2Data );
   
  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}

String encType(int id){

String type;
  if(WiFi.encryptionType(id) == ENC_TYPE_WEP){
    type=" WEP";
  }else if(WiFi.encryptionType(id) == ENC_TYPE_TKIP){
    type="WPA / PSK";    
  }else if(WiFi.encryptionType(id) == ENC_TYPE_CCMP){
    type="WPA2 / PSK";    
  }else if(WiFi.encryptionType(id) == ENC_TYPE_AUTO){
    type="WPA / WPA2 / PSK";    
  }else if(WiFi.encryptionType(id) == ENC_TYPE_NONE){
    type="<<OPEN>>";    
  }
  return type;
}

float regulator(float order, float Temp){


  if(order < Temp)
  {
      digitalWrite(5, LOW);
      Temp = Temp - 0.5;
  }
  else
  {
      digitalWrite(5, HIGH);
      Temp = Temp + 2;
  }
  return Temp;
}
