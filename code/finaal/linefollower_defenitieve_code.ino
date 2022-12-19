//libraries toevoegen aan programma
  #include <SerialCommand.h>
  #include <EEPROM.h>
  #include <EEPROMAnything.h>
  #include <BluetoothSerial.h>

//defenities van alle pinnen
  //input
    //sensor
      #define sensor1 34
      #define sensor2 35
      #define sensor3 32
      #define sensor4 33
      #define sensor5 25
      #define sensor6 26
      #define sensor7 27
      #define sensor8 14

    //knop
      #define knop 22

  //output
    //HBrug
      #define aIn1 19
      #define aIn2 18
      #define bIn1 17
      #define bIn2 5
    //led
      #define led 23

//defenities van constanten
  BluetoothSerial serialBT;
  #define SerialPort serialBT
  #define Baudrate 115200
  #define EEPROM_SIZE 4000

//Serial communicatie
  SerialCommand sCmd(SerialPort);

//constanten
  bool debug;
  unsigned long previous, calculationTime;
  const int sensor[] = {sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7, sensor8};
  bool run;
  int debugnormalised[8];
  float debugPosition;
  int debugIndex;
  float iTerm;
  float Lasterr;
//EEPROM
  struct param_t
  {
    unsigned long cycleTime;
    int black[8];
    int white[8];
    float kp;
    float ki;
    float kd;
    long power;
    float diff;
    //andere waardes voor in eeprom hier toevoegen
  } params;

void setup() {
  //SerialPort.begin(Baudrate);
  EEPROM.begin(EEPROM_SIZE);
  serialBT.begin("lijnvolger");

  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("calibrate", onCalibrate);  
  sCmd.addCommand("start", onStart);
  sCmd.addCommand("stop", onStop);
  sCmd.setDefaultHandler(onUnknownCommand);

  EEPROM_readAnything(0, params);

  //sensor pinnen
    for (int i=0; i<8; i++)
    {
      pinMode(sensor[i],INPUT);
    }

  //knop pin
    pinMode(knop, INPUT);
    // is eruit gehaald wegens problemen met de knop of soldeer fout
   // attachInterrupt(knop, buttonPush, RISING);

  //H-brug pinnen
    pinMode(aIn1, OUTPUT);
    pinMode(aIn2, OUTPUT);
    pinMode(bIn1, OUTPUT);
    pinMode(bIn2, OUTPUT);

  //led pin
    pinMode(led, OUTPUT);

  run = false;
  serialBT.println("ready");
}

void loop() {
  
  sCmd.readSerial();
  
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;

    //cyclische code

    // normaliseren en interpoleren sensor
      int normalised[8];

      for (int i = 0; i < 8; i++){
        normalised[i] = map(analogRead(sensor[i]),params.black[i],params.white[i], 0, 4096);
      }

      int index = 0;
      for (int i = 1; i<8; i++ ) if(normalised[i] < normalised[index]) index = i;

      float position;
      for(int i = 0; i<8; i++){
        debugnormalised[i] = normalised[i];
      }


      //if (normalised[index]  3000) run = false;

      if (index == 0) position = -50;
      else if (index == 7) position = 50;
      else{
        int sNul = normalised[index];
        int sMinEen = normalised[index-1];
        int sPlusEen = normalised[index+1];

        float b = (sPlusEen - sMinEen);
        b = b/2;

        float a = sPlusEen - b - sNul;

        position = -b / (2*a);
        position += index;
        position -= 3.5;

        position *= 15;
      }

      debugPosition = position;
      debugIndex = index;
    
      int powerLeft = 0;
      int powerRight = 0;

    //pid regeling
    if (run){
      float error = -position;

      //p
      float output = error* params.kp;
      
      //i
      iTerm += error * params.ki;
      iTerm = constrain(iTerm, -510, 510);
      output += iTerm;

      //d
      output += params.kd * (error - Lasterr);
      Lasterr = error;

      output = constrain(output, -510, 510);

       if (output >= 0){
        powerLeft = constrain(params.power + params.diff * output, -255,255);
        powerRight = constrain(powerLeft - output, -255,255);
        powerLeft = powerRight + output;
      }
      else{
        powerRight = constrain(params.power + params.diff * output, -255,255);
        powerLeft = constrain(powerRight + output, -255,255);
        powerRight = powerLeft - output;
      }
       }
      else  {
        iTerm = 0;
        powerLeft = 0;
        powerRight = 0;
      }

        
       

    //aansturen motoren
    
       analogWrite(bIn2, powerLeft > 0 ? powerLeft : 0);
       analogWrite(bIn1, powerLeft < 0 ? -powerLeft : 0);
       analogWrite(aIn1, powerRight > 0 ? powerRight : 0);
       analogWrite(aIn2, powerRight < 0 ? -powerRight : 0);
  }

  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}

void onUnknownCommand(char *command) {
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void onSet(){ 
  char* param = sCmd.next();
  char* value = sCmd.next();

  SerialPort.println(param);
  SerialPort.println(value);

  if (strcmp(param, "cycle") == 0){
    long newCycleTime = atol(value);
    float ratio = ((float) newCycleTime) /  ((float) params.cycleTime);
    params.ki *= ratio;
    params.cycleTime = newCycleTime;
  }
  if (strcmp(param, "ki") == 0){
    float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
    params.ki = atof(value) * cycleTimeInSec;
  } 
  if (strcmp(param, "kd") == 0){
    float cycleTimeInSec = ((float)params.cycleTime)/1000000;
    params.kd = atof(value) / cycleTimeInSec;
  }

  //parameters een nieuwe waarde geven
  if (strcmp(param, "kp") == 0) params.kp = atof(value);
  if (strcmp(param, "power") == 0) params.power = atol(value);
  if (strcmp(param, "diff") == 0) params.diff = atof(value);
  
  EEPROM_writeAnything(0, params);
  EEPROM.commit();
}

void onDebug(){
  //cycle time
    SerialPort.print("cycle time: ");
    SerialPort.println(params.cycleTime);

  // param weergeven met debug
  //zwart 
    SerialPort.print("black: ");
    for (int i = 0; i < 8; i++)
    {
      SerialPort.print(params.black[i]);
      SerialPort.print(" / ");
    }
    SerialPort.println();

    //wit
    SerialPort.print("wit: ");
    for (int i = 0; i < 8; i++)
    {
      SerialPort.print(params.white[i]);
      SerialPort.print(" / ");
    }
    SerialPort.println();

    SerialPort.print("normalised: ");
    for (int i = 0; i < 8; i++)
    {
      SerialPort.print(debugnormalised[i]);
      SerialPort.print(" / ");
    }
    SerialPort.println();

    SerialPort.print("index: ");
    SerialPort.println(debugIndex);

    SerialPort.print("positie");
    SerialPort.println(debugPosition);

  //kp,ki,kd
    SerialPort.print("kp: ");
    SerialPort.println(params.kp);

    float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
    
    float ki = params.ki/cycleTimeInSec;
    SerialPort.print("Ki: ");
    SerialPort.println(ki);

    float kd = params.kd * cycleTimeInSec;
    SerialPort.print("kd: ");
    SerialPort.println(kd);

    SerialPort.print("power: ");
    SerialPort.println(params.power);

    SerialPort.print("diff: ");
    SerialPort.println(params.diff);

    SerialPort.print("run: ");
    SerialPort.println(run);

  //calculation time
    SerialPort.print("calculation time: ");
    SerialPort.println(calculationTime);
    calculationTime = 0;
}

void onCalibrate(){
  char* param = sCmd.next();

  if (strcmp(param, "black") == 0)
  {
    SerialPort.print("start calibrating black...");
    for (int i = 0; i < 8; i++) params.black[i] = analogRead(sensor[i]);
    SerialPort.println("done");
  }

  if (strcmp(param, "white") == 0)
  {
    SerialPort.print("start calibrating white...");
    for (int i = 0; i < 8; i++) params.white[i] = analogRead(sensor[i]);
    SerialPort.println("done");
  }

  EEPROM_writeAnything(0, params);
  EEPROM.commit();
}

void onStart(){
  run = true;
  SerialPort.println("gestart");
  digitalWrite(led, run);
}

void onStop(){
  run = false;
  SerialPort.println("gestopt");
  digitalWrite(led, run);
}

void buttonPush(){
  SerialPort.println("button push");
  if (run == false){
    run = true;
    SerialPort.println("gestart");
  }
  else {
    run = false;
    SerialPort.println("gestopt");
  }
  digitalWrite(led, run);
}