#include <ESP8266WiFi.h>

#include <WiFiClient.h>

#include <ESP8266WebServer.h>

const char* ssid = "crz";

const char* password = "02505";

float ldr = 0;

float ldrValue;

ESP8266WebServer server(80);

//root page can be accessed only if authentification is ok

void handleRoot() {

//Serial.println("Enter handleRoot");

String header;

server.sendHeader("Access-Control-Allow-Origin", "*");

server.sendHeader("Cache-Control", "no-cache");

//String content = "<html><body><H2>hello, you successfully connected to StarWay!</H2><br>";

String content = String(ldrsensor()) + ";" + String(ldrsensor());

server.send(200, "text/plain", content);

}

void setup(void) {

Serial.begin(9600);

WiFi.mode(WIFI_STA);

WiFi.begin(ssid, password);

Serial.println("");

pinMode(ldr, INPUT);

ldrValue = 0;

// Wait for connection

while (WiFi.status() != WL_CONNECTED) {

delay(500);

Serial.print(".");

}

Serial.println("");

Serial.print("Connected to ");

Serial.println(ssid);

Serial.print("IP address: ");

Serial.println(WiFi.localIP());

server.on("/", handleRoot);

// server.on("/login", handleLogin);

server.on("/inline", []() {

server.send(200, "text/plain", "this works without need of authentification");

});

//here the list of headers to be recorded

const char * headerkeys[] = {"User-Agent", "Cookie"} ;

size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);

//ask server to track these headers

server.collectHeaders(headerkeys, headerkeyssize );

server.begin();

Serial.println("HTTP server started");

}

void loop(void) {

server.handleClient();

}

float ldrsensor() {

ldrValue = analogRead(ldr);

//Serial.println(ldrValue);

return ldrValue;

}
