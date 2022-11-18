#define Sensor1 34 
#define Sensor2 35
#define Sensor3 32
#define Sensor4 33
#define Sensor5 25
#define Sensor6 26
#define Sensor7 27
#define Sensor8 14

int waarde1, waarde2, waarde3, waarde4, waarde5, waarde6, waarde7, waarde8;

void setup() {
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);
  pinMode(Sensor5, INPUT);
  pinMode(Sensor6, INPUT);
  pinMode(Sensor7, INPUT);
  pinMode(Sensor8, INPUT);

  Serial.begin(115200);
}

void loop() {
  waarde1 = analogRead(Sensor1);
  waarde2 = analogRead(Sensor2);
  waarde3 = analogRead(Sensor3);
  waarde4 = analogRead(Sensor4);
  waarde5 = analogRead(Sensor5);
  waarde6 = analogRead(Sensor6);
  waarde7 = analogRead(Sensor7);
  waarde8 = analogRead(Sensor8);

  Serial.print(waarde1);
  Serial.print("/");
  Serial.print(waarde2);
  Serial.print("/");
  Serial.print(waarde3);
  Serial.print("/");
  Serial.print(waarde4);
  Serial.print("/");
  Serial.print(waarde5);
  Serial.print("/");
  Serial.print(waarde6);
  Serial.print("/");
  Serial.print(waarde7);
  Serial.print("/");
  Serial.println(waarde8);
  delay(1000);
}
