#include <ESP8266WiFi.h>  
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
  
 #define BLUE_LED  12  
 #define GREEN_LED  13  
 #define RED_LED   14  
   
 // Create the objects for server and client  
 WiFiServer server(80);  
 WiFiClient client;  
   
 const char* ssid   = "Test_1";         // This is the SSID that ESP32 will broadcast  
 const char* password = "12345678";     // password should be atleast 8 characters to make it work  
 
 String http;
 String temp;  
 String bluLedState = "off";  
 String grnLedState = "off";  
 String redLedState = "off"; 
 String sequence1 = "off";
 String sequence2 = "off";
 String sequence3 = "off"; 

 int count;
 
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
  WiFi.softAP(ssid, password);  
   
  Serial.println( "" );  
  Serial.println( "WiFi AP is now running" );  
  Serial.println( "IP address: " );  
  Serial.println( WiFi.softAPIP() );  
   
  // Start our ESP32 server  
  server.begin();  
 }

 void loop(){
       // Checks if a new client tries to connect to our server
       if (client = server.available()) { 
               Serial.println("New Client.");
               String clientData = "";

              // Wait until the client finish sending HTTP request
               while (client.connected()){ 
                      if (client.available()) {           // If there is a data,
                             char c = client.read();      //  read one character
                             http += c;                   
                             Serial.write(c);
                                    
                            // If the character is carriage return,
                            //  it means end of http request from client
                             if (c == '\n') { 
                                   if (clientData.length() == 0) {       //  Now that the clientData is cleared,
                                          sendResponse();                //perform the necessary action
                                          //updateLED();
                                          updateState();
                                          updateWebpage();
                                          break;
                                   } else {
                                          clientData = ""; //  First, clear the clientData
                                   }
                             } else if (c != '\r') {       // Or if the character is NOT new line
                                    clientData += c;       //store the character to the clientData variable
                             }
                      }
               }

               temp = http;
               http = "";

              // Disconnect the client.
               client.stop(); 
               Serial.println("Client disconnected.");
               Serial.println("");
        }
        updateLED();
 }

 void sendResponse() {  
  // Send the HTTP response headers  
  client.println("HTTP/1.1 200 OK");  
  client.println("Content-type:text/html");  
  client.println("Connection: close");  
  client.println();   
 }  
   
// In here we will display / update the webpage by sending the HTML   
//  to the connected client  
// In order for us to use the HTTP GET functionality,  
//  the HTML hyperlinks or href is use in the buttons.   
//  So that, when you press the buttons, it will send a request to the   
//  web server with the href links by which our ESP32 web server will  
//  be check using HTTP GET and execute the equivalent action  
 void updateWebpage() {  
    
  // Send the whole HTML  
  client.println("<!DOCTYPE html><html>");  
  client.println("<head>");  
  client.println("<title>ESP32 WiFi Station</title>");  
  client.println("</head>");  
    
  // Web Page Heading  
  client.println("<body><h1>Simple ESP32 Web Server</h1>");  
   
  // Display buttons for Sequence 1  
  client.println("<p>1. Sequence 1 is " + sequence1 + "</p>");    
  if (sequence1 == "off") {  
   client.println("<p><a href=\"/Sequence_1/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/Sequence_1/off\"><button>Turn OFF</button></a></p>");  
  }   
   
  client.print("<hr>");  
    
  // Display buttons for sequence 2  
  client.println("<p>2. Sequence 2 is " + sequence2 + "</p>");    
  if (sequence2 == "off") {  
   client.println("<p><a href=\"/Sequence_2/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/Sequence_2/off\"><button>Turn OFF</button></a></p>");  
  }   
   
  client.print("<hr>");  
      
  // Display buttons for Red LED  
  client.println("<p>3. Sequence 3 is " + (sequence3) + "</p>");    
  if (sequence3 == "off") {  
   client.println("<p><a href=\"/Sequence_3/on\"><button>Turn ON</button></a></p>");  
  } else {  
   client.println("<p><a href=\"/Sequence_3/off\"><button>Turn OFF</button></a></p>");  
  }  
   
  client.println("</body></html>");  
  client.println();  
 }  
   
// In here we will check the HTTP request of the connected client  
//  using the HTTP GET function, and will turn on/off according to HTTP request
 void updateLED() {  
  if(temp.indexOf("GET /Sequence_1/on") >= 0) {  
   Serial.println("Blue LED on");    
   digitalWrite(BLUE_LED, HIGH);  
  } else if (temp.indexOf("GET /Sequence_1/off") >= 0) {  
   Serial.println("Blue LED off");  
   digitalWrite(BLUE_LED, LOW);  
  } else if (temp.indexOf("GET /Sequence_2/on") >= 0) {  
   Serial.println("Green LED on");  
   digitalWrite(GREEN_LED, HIGH);  
  } else if (temp.indexOf("GET /Sequence_2/off") >= 0) {  
   Serial.println("Green LED off");   
   digitalWrite(GREEN_LED, LOW);  
  } else if (temp.indexOf("GET /Sequence_3/on") >= 0) {  
   Serial.println("Red LED on");   
   digitalWrite(RED_LED, HIGH);  
  } else if (temp.indexOf("GET /Sequence_3/off") >= 0) {  
   Serial.println("Red LED off");    
   digitalWrite(RED_LED, LOW);  
  }  
 }

//updates states of LED
void updateState(){
   if    (http.indexOf("GET /Sequence_1/on") >= 0) {  
   sequence1 = "on";
   count = 0;  
  } else if (http.indexOf("GET /Sequence_1/off") >= 0) {    
   sequence1 = "off";   
  } else if (http.indexOf("GET /Sequence_2/on") >= 0) {    
   sequence2 = "on";
   count = 0;  
  } else if (http.indexOf("GET /Sequence_2/off") >= 0) {   
   sequence2 = "off";  
  } else if (http.indexOf("GET /Sequence_3/on") >= 0) {  
   sequence3 = "on";
   count = 0;    
  } else if (http.indexOf("GET /Sequence_3/off") >= 0) {  
   sequence3 = "off";  
  }  
}
