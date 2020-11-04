#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int verde = D8;  // LED connected to digital pin 13
int rojo = D6;  // LED connected to digital pin 13
int inPin = D5;    
int inPin2 = D4;
int val = 0;
int val2 = 0;      

int ultimo = 0;

//Server
String server = "http://almacenamiento.herokuapp.com/api/sensor";



void setup() {
  Serial.begin(115200);    //iniciar puerto serie
  pinMode(verde, OUTPUT); 
  pinMode(rojo, OUTPUT); 
  pinMode(inPin, INPUT);    //In
  pinMode(inPin2, INPUT);    //In

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
  
  val = digitalRead(inPin);   // 
  val2 = digitalRead(inPin2);   // 
  if(val== 1 && val2== 0 && ultimo == 0) {
     ultimo =1; 
     encender();
     post("true");
  }else if(val == 0 && val2 ==1 && ultimo ==1 ){
    ultimo =0;
    apagado();
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

void apagado(){
    digitalWrite(verde , LOW); 
    digitalWrite(rojo , HIGH); 
}

void encender(){
    digitalWrite(verde , HIGH);   // poner el Pin en HIGH 
    digitalWrite(rojo , LOW); 
}

