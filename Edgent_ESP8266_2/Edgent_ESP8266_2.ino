#define BLYNK_TEMPLATE_ID "TMPLDXWzgHtB"
#define BLYNK_DEVICE_NAME "Proyecto IoT"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#include "BlynkEdgent.h"

#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11



const int led = D3;
const int reley = D1;
const int LDR = A0;

float t;
float h;
float f;
int valor;

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client; 

BLYNK_WRITE(V0){
  int V0Data=param.asInt();
  digitalWrite(led,V0Data);
}

BLYNK_WRITE(V3){
  int V3Data=param.asInt();
  digitalWrite(reley,V3Data);
  Serial.print(V3Data);
  Serial.println(" reley");
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(reley,OUTPUT);
  pinMode(LDR,INPUT);
  BlynkEdgent.begin();
  Serial.println(F("DHTxx test!"));
  dht.begin();
  
}

void loop()
{
  Blynk.run();
  delay(200);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
    
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.println(f);

  
  int a = analogRead(LDR);
  //Serial.println(a);
  valor = map(a, 0, 268, 0, 100); 
  Serial.print(valor); 
  Serial.println(" % de luz");
    
  
  Blynk.virtualWrite(V1,h);
  Blynk.virtualWrite(V2,t);
  Blynk.virtualWrite(V4,valor);
}
