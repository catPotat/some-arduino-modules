#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
const char* ssid     = "MitNa"; 
const char* password = "987654321a";
const char* host     = "192.168.0.200"; // Your domain  
String path          = "/roomcontrol/light.json";
const int pin        = 2;
IPAddress ip(192, 168, 0, 199);
char lightOld = '_';

void setup() {
    pinMode(pin, OUTPUT);
    pinMode(pin, HIGH);
    Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
    Serial.println("IP address: " + WiFi.localIP());
}

void loop() {
    //Serial.print("connecting to ");
  //Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    //Serial.println("connection failed");
    return;
  }
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +               "Host: " + host + "\r\n" +                "Connection: keep-alive\r\n\r\n");
  delay(250); // wait for server to respond
  // read response  
String section="header";

  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);    // we’ll parse the HTML body here
    if (section=="header") { // headers..
      //Serial.print(".");
      if (line=="\n") { // skips the empty space at the beginning
         section="json";
      }
    }
    else if (section=="json") {  // print the good stuff
      section="ignore";
      String result = line.substring(1);      // Parse JSON
      int size = result.length() + 1;
      char jsonMessage[size];
      result.toCharArray(jsonMessage, size);
      
      StaticJsonBuffer<200> JSONBuffer;   //Memory pool
      JsonObject& parsed = JSONBuffer.parseObject(jsonMessage); //Parse message
 
      if (!parsed.success()) {
        Serial.println("Parsing failed");
        delay(10000);
        return;
      }
      
      const char *light = parsed["light"];
      const char data = *light;
      if (data!=lightOld) {
        if (data!='_') {
          digitalWrite(pin, HIGH);
          Serial.println(data);
          delay(300);
          digitalWrite(pin, LOW);
        }
        lightOld=data;
      }
    }
  }
  //Serial.println("closingconnection");
}
