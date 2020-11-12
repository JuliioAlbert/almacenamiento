#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int verde = D7;  // LED connected to digital pin 13
int rojo = D8;  // LED connected to digital pin 13
int izq = D1;    
int der = D2;
int d = 0;
int i = 0;      

int ultimo = 0;
int a= 0;
int b=0;


//Server
String server = "http://almacenamiento.herokuapp.com/api/sensor";



void setup() {
  Serial.begin(115200);    //iniciar puerto serie
  pinMode(verde, OUTPUT); 
  pinMode(rojo, OUTPUT); 
  pinMode(der, INPUT);    //In
  pinMode(izq, INPUT);    //In

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
  
  d = digitalRead(der);   // 
  i = digitalRead(izq);   //
 
  if(d == 0 && i == 0 && ultimo == 0  ){
    post("false");
    apagado();
    Serial.println("Apagado");
    b=1;
    a=1;
    ultimo=1;
  }else if(d == 1 && i == 0   && b==1){
    post("true");
    encender();
    Serial.println("ED");
    a=1;
    b=0;
    ultimo=0;
  }else if(i == 1 && d== 0 && a==1 ){
    post("true");
    Serial.println("EI");
    encender();
    b=1;
    a=0;
    ultimo=0;
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