/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */

#include "WiFi.h"

//replace with network credentials
const char* ssid = "MySpectrumWiFi6C-2G";
const char* password = "turtleengine104";

//get esp32 ip address
//Serial.println(WiFi.localIP());

//set a Static esp32 IP address
//IPAddress local_IP(192, 168, 1, 184);
//
////set your gateway IP address
//IPAddress gateway(192, 168, 1, 1);
//
//IPAddress subnet(255, 255, 0, 0);
//IPAddress primaryDNS(8, 8, 8, 8);   //optional
//IPAddress secondaryDNS(8, 8, 4, 4); //optional

unsigned long previousMillis = 0;
unsigned long interval = 30000;


void setup()
{
    Serial.begin(115200);
    initWiFi();
    Serial.print("RRSI: ");
    Serial.println(WiFi.RSSI());
    Serial.println("Setup done");

    //config static IP address
    // can remove primary and secondary if needed
//    if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)){
//      Serial.println("STA Failed to config");
//    }
}

void loop()
{
    unsigned long currentMillis = millis();

//    Serial.println("scan start");
//
//    // WiFi.scanNetworks will return the number of networks found
//    int n = WiFi.scanNetworks();
//    
//    Serial.println("scan done");
//    if (n == 0) {
//        Serial.println("no networks found");
//    } else {
//        Serial.print(n);
//        Serial.println(" networks found");
//        for (int i = 0; i < n; ++i) {
//            // Print SSID and RSSI for each network found
//            Serial.print(i + 1);
//            Serial.print(": ");
//            Serial.print(WiFi.SSID(i));
//            Serial.print(" (");
//            Serial.print(WiFi.RSSI(i));
//            Serial.print(")");
//            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
//            delay(10);
//        }
//    }

    //if wifi down, try reconnecting every CHECK_WIFI_TIME secs
    if((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)) {
       Serial.print(millis());
       Serial.println("Reconnecting to WiFi ... ");
       WiFi.disconnect();
       WiFi.reconnect();
       previousMillis = currentMillis;      
    }
    
//    Serial.println("");

//    // Wait a bit before scanning again
//    delay(5000);
}

void initWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
