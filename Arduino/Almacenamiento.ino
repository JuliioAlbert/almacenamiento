#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int verde = D8;  // LED connected to digital pin 13
int rojo = D6;  // LED connected to digital pin 13
int inPin = D7;    // pushbutton connected to digital pin 7
int val = 0;      // variable to store the read value

int ultimo = 0;
int actual = 0;
int inicial = 0;
//Server
String server = "http://almacenamiento.herokuapp.com/api/sensor";



void setup() {
  Serial.begin(115200);    //iniciar puerto serie
  pinMode(verde, OUTPUT); 
  pinMode(rojo, OUTPUT); 
  pinMode(inPin, INPUT);    //Interruptor

  //Conexion a la Red Wifi
   WiFi.begin("julio", "huevos2020");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}



void loop() {
  
  val = digitalRead(inPin);   // read the input pin
  actual = val;
  if(actual== 1 && ultimo == 0) {
    ultimo =1; 
     digitalWrite(verde , HIGH);   // poner el Pin en HIGH 
     digitalWrite(rojo , LOW); 
     post("true");
  }else if(actual == 0 && ultimo ==1 ){
    ultimo =0;
    digitalWrite(verde , LOW); 
    digitalWrite(rojo , HIGH); 
     //Serial.println("GET");
    post("false");
  }
}
  
  void post(String estado) {
 
  HTTPClient http;
  String json;
  StaticJsonDocument<200> doc;
  doc["estado"] = estado;
  serializeJson(doc, json);
  Serial.println(json);
  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
}
