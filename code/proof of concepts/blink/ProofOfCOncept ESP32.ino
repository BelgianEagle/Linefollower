int ronde = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2,OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  Serial.print("loop: ");
  Serial.println(ronde);
  delay(1000);
  ronde++;
}

