#define BIN1 12
#define BIN2 14
#define AIN1 27
#define AIN2 26

void setup() {
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
motorstop();
delay(1000);
motorversnelt(AIN1);
motorstop();
delay(1000);
motorversnelt(AIN2);
motorstop();
delay(1000);
motorversnelt(BIN1);
motorstop();
delay(1000);
motorversnelt(BIN2);
}

void motorstop(){
analogWrite(AIN1, 0);
analogWrite(AIN2, 0);
analogWrite(BIN1, 0);
analogWrite(BIN2, 0);
}

void motorversnelt(int uit){
  for (int i=0; i<256; i++){
      analogWrite(uit,i);
      delay(100);
  }
}