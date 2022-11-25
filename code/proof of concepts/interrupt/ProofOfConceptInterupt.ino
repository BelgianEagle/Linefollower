int buttonpress = 0;

void setup() {
 pinMode(12, INPUT);
 attachInterrupt(12, ButtonPush, RISING);
  Serial.begin(115200);
}

void loop() {
  Serial.println(buttonpress);
  delay(1000);
}

void ButtonPush() {
  buttonpress = buttonpress + 1;
  Serial.println("interupt");
}
