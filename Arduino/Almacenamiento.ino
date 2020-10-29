#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int verde = D8;  
int rojo = D6;  
int inPin = D7;    
int val = 0;      

int ultimo = 0;

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
  
  val = digitalRead(inPin);  
  if(val== 1 && ultimo == 0) {
    ultimo =1; 
     digitalWrite(verde , HIGH);   
     digitalWrite(rojo , LOW); 
     post("true");
  }else if(val == 0 && ultimo ==1 ){
    ultimo =0;
    digitalWrite(verde , LOW); 
    digitalWrite(rojo , HIGH); 
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
