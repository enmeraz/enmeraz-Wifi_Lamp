#include <ESP8266WiFi.h>  
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
  
 #define BLUE_LED  12  
 #define GREEN_LED  13  
 #define RED_LED   14  
   
 // Create the objects for server and client  
 WiFiServer server(80);  
 WiFiClient client;  
   
//Will create its own wifi
 const char* ssid   = "Test_1";         // This is the SSID that ESP32 will broadcast  
 const char* password = "12345678";     // password should be atleast 8 characters to make it work  
  
 String http;  
 String bluLedState = "off";  
 String grnLedState = "off";  
 String redLedState = "off";  
   
 void setup() {  
  Serial.begin(115200);  
  pinMode(BLUE_LED, OUTPUT);  
  pinMode(GREEN_LED, OUTPUT);  
  pinMode(RED_LED, OUTPUT);  
  digitalWrite(BLUE_LED, LOW);  
  digitalWrite(GREEN_LED, LOW);  
  digitalWrite(RED_LED, LOW);  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
   
  // Create the ESP32 access point  
  /*  
   * Alternative:  
   * softAP(const char* ssid,  
   *     const char* password,  
   *     int channel,  
   *     int ssid_hidden,   
   *     int max_connection  
   *       
   *     where:  
   *      ssid - this is the SSID that will be broadcast by ESP32  
   *          maximum of 63 characters  
   *      password - this is the password to connect to ESP32  
   *          minimum of 8 characters to function  
   *          Put NULL to make it open to public  
   *      channel - wifi channels (ranging from 1 to 13)  
   *      ssid_hidden - sets the SSID as broadcast or hidden  
   *          0: broadcast SSID  
   *          1: hidden SSID,   
   *           you need to type the exact SSID name in order to connect  
   *      max_connection - maximum number of connected clients  
   *          accepts 1 to 4 only  
   *            
   */  
  WiFi.softAP(ssid, password);  
   
  Serial.println( "" );  
  Serial.println( "WiFi AP is now running" );  
  Serial.println( "IP address: " );  
  Serial.println( WiFi.softAPIP() );  
   
  // Start our ESP32 server  
  server.begin();  
 }

 void loop(){

     if (client = server.available()) {     // Checks if a new client tries to connect to our server
         Serial.println("New Client.");
         
         String clientData = "";
         while (client.connected()) {       // Wait until the client finish sending HTTP request
             if (client.available()) {      // If there is a data,
                 char c = client.read();    //  read one character since c cant do string
                 http += c;                 //  then parse it
                 Serial.write(c);
                 if (c == '\n') {                       // If the character is carriage return, it means end of http request from client
                     if (clientData.length() == 0) {    //  Checks if the clientData is cleared,
                         sendResponse();                
                         updateLED();
                         updateWebpage();
                         break;
                     }
                     else {
                         clientData = "";               //  First, clear the clientData
                     }
                 }
                 else if (c != '\r') {                    // Or if the character is NOT new line
                     clientData += c;                   //  store the character to the clientData variable
                 }
             }
         }
         http = "";

         // Disconnect the client.
         client.stop();         
         Serial.println("Client disconnected.");
         Serial.println("");
     }
 }

  // Send the HTTP response headers  
 void sendResponse() {  
  client.println("HTTP/1.1 200 OK");  
  client.println("Content-type:text/html");  
  client.println("Connection: close");  
  client.println();   
 }  

/*
// In here we will display / update the webpage by sending the HTML   
//  to the connected client  
// In order for us to use the HTTP GET functionality,  
//  the HTML hyperlinks or href is use in the buttons.   
//  So that, when you press the buttons, it will send a request to the   
//  web server with the href links by which our ESP32 web server will  
//  be check using HTTP GET and execute the equivalent action  
*/

 void updateWebpage() {  
  // Send the whole HTML to create web page  
  client.println("<!DOCTYPE html><html>");  
  client.println("<head>");  
  client.println("<title>ESP32 WiFi Station</title>");  
  client.println("</head>");  
      
  client.println("<body><h1>Simple ESP32 Web Server</h1>");  
   
  // Display buttons for Blue LED  
  client.println("<p>1. Blue LED is " + bluLedState + "</p>");    
  if (bluLedState == "off") {  
   client.println("<p><a href=\"/BLUE_LED/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/BLUE_LED/off\"><button>Turn OFF</button></a></p>");  
  }   
   
  client.print("<hr>");  
    
  // Display buttons for Green LED  
  client.println("<p>2. Green LED is " + grnLedState + "</p>");    
  if (grnLedState == "off") {  
   client.println("<p><a href=\"/GREEN_LED/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/GREEN_LED/off\"><button>Turn OFF</button></a></p>");  
  }   
   
  client.print("<hr>");  
      
  // Display buttons for Red LED  
  client.println("<p>3. Red LED is " + redLedState + "</p>");    
  if (redLedState == "off") {  
   client.println("<p><a href=\"/RED_LED/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/RED_LED/off\"><button>Turn OFF</button></a></p>");  
  }  
   
  client.println("</body></html>");  
  client.println();  
 }  
   
// In here we will check the HTTP request of the connected client using the HTTP GET function,  
//  Then turns the LED on / off according to the HTTP request
 void updateLED(){
     if (http.indexOf("GET /BLUE_LED/on") >= 0) {
         Serial.println("Blue LED on");
         bluLedState = "on";
         digitalWrite(BLUE_LED, HIGH);
     } else if (http.indexOf("GET /BLUE_LED/off") >= 0) {
         Serial.println("Blue LED off");
         bluLedState = "off";
         digitalWrite(BLUE_LED, LOW);
     } else if (http.indexOf("GET /GREEN_LED/on") >= 0) {
         Serial.println("Green LED on");
         grnLedState = "on";
         digitalWrite(GREEN_LED, HIGH);
     } else if (http.indexOf("GET /GREEN_LED/off") >= 0) {
         Serial.println("Green LED off");
         grnLedState = "off";
         digitalWrite(GREEN_LED, LOW);
     } else if (http.indexOf("GET /RED_LED/on") >= 0) {
         Serial.println("Red LED on");
         redLedState = "on";
         digitalWrite(RED_LED, HIGH);
     } else if (http.indexOf("GET /RED_LED/off") >= 0) {
         Serial.println("Red LED off");
         redLedState = "off";
         digitalWrite(RED_LED, LOW);
     }
 }