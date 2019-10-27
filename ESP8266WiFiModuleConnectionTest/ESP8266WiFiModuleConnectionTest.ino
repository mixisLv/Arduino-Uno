/**
 * ESP9266 WiFi Module Connection test
 */

#include <SoftwareSerial.h>

#define RX 10
#define TX 11

String WIFI_SSID     = "your-wifi-ssid";      // Your WiFi ssid
String WIFI_PASSWORD = "your-wifi-password";  // Password

SoftwareSerial esp8266(RX, TX);

void setup()
{  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("ESP9266 WiFi Module Connection test");
  
  esp8266.begin(9600); //Baud rate for communicating with ESP8266. Your's might be different.
  delay(1000);
 
  esp8266Serial("AT", 1000);
  esp8266Serial("AT+GMR", 1000);
  esp8266Serial("AT+CWMODE=1", 1000); 
  esp8266Serial("AT+CIPMUX=1", 1000);
  esp8266Serial("AT+CWJAP=\"" + WIFI_SSID + "\",\"" + WIFI_PASSWORD + "\"", 10000);
  esp8266Serial("AT+CWJAP?", 1000);
  esp8266Serial("AT+CIFSR", 1000);
  esp8266Serial("AT+CIPSTATUS", 1000);
}

void loop() 
{
  Serial.println(millis());
  esp8266Serial("AT+CWJAP?", 1000);

  delay(10000);
}

String esp8266Serial(String command, const int timeout)
{
  Serial.print("ESP8266 command => ");
  Serial.println(command);
  
  String response = ""; // a String to hold incoming data
  esp8266.println(command);
  delay(50);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      response += esp8266.readString(); // Read the answer of ESP8266
    }   
  }

  Serial.print("ESP8266 response => ");
  Serial.println(response);   
  delay(200);

  return response;
} 


  
