#include "BluetoothSerial.h"

BluetoothSerial BluetoothSerial;

int waardeP = 0;
int waardeI = 0;
int waardeD = 0;
String laatstecommando = String();
String geencommando = "geen commando";

void setup() {
  Serial.begin(115200);
  BluetoothSerial.begin("LijnvolgerArnout");
  BluetoothSerial.print("geef een getal of gebruik de knoppen: ");
  laatstecommando = geencommando;
}

void loop() {
  if (BluetoothSerial.available()){
    laatstecommando = BluetoothSerial.readString();
    laatstecommando.trim();
  }
  Serial.println(laatstecommando);
  
  if (laatstecommando == geencommando){ 
  }
  else if (laatstecommando == "waarde"){
    zendeningesteldewaardes();
  }
  else {
    BluetoothSerial.println("dit is geen geldig commando");
    laatstecommando = geencommando;
  }
}

void zendeningesteldewaardes() {
  BluetoothSerial.println("waardes: ");
  BluetoothSerial.print("waarde P: ");
  BluetoothSerial.println(waardeP);
  BluetoothSerial.print("waarde I: ");
  BluetoothSerial.println(waardeI);
  BluetoothSerial.print("waarde D: ");
  BluetoothSerial.println(waardeD);
  laatstecommando = geencommando;
}