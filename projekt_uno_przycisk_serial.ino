
unsigned long prevMilPom = 0;
unsigned long prevMilPod = 0;
const long inter = 3000;

boolean stateOfInp = false;
boolean prevPom = false;
boolean prevPod = false;
boolean boolOutIO = false;
boolean valIn = false;

boolean pinPod = false;
boolean pinPom = false;
byte sumOfInp = 0;
word sumOfByte;
const int pod = 8;
const int pom = 9;


String inData = "";
String finalString = "";
String inDataState = "";

void setup() {
  Serial.begin(115200);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  sumOfByte = 0;
}

void loop() {
  checkButtonPom();
  checkButtonPod();
  readSerial();
  
  if(boolOutIO)
    outputIO(finalString, inDataState);
}


void readSerial(){
  if(Serial.available() >0){   
      char inChar = Serial.read();   

      if(inChar == '\n' && valIn){       
        inData.trim();
        finalString = String(inData[0]) + String(inData[1]) + String(inData[2]);
        inDataState = inData[4];
        inData = "";
        boolOutIO = true;
        valIn = false;   
      }      
          
      if(inChar != '\n' && inChar != '\r' && valIn)
        inData += inChar; 

      if(inChar == '$'){
      valIn = true;
      }
  }
}

void outputIO(String loc, String outVal){
    const int val = outVal.toInt();
    
    if(loc == "pod"){
    digitalWrite(pod, val);  
    }

    if(loc == "pom"){
    digitalWrite(pom, val);  
    }

    Serial.println(loc + "=" + val);
    finalString = "";
    boolOutIO = false;
}

void checkButtonPod(){
  int pinIn = 4;
  int pinOut = 8;
  unsigned long curMil = millis();
  String finStr = "pod";

  if(digitalRead(pinIn) && curMil > prevMilPod){
      if(curMil - prevMilPod >= 10){
        finalString = finStr;
        if(!digitalRead(pinOut)){
          inDataState = "1";
        }else if(digitalRead(pinOut)){
          inDataState = "0";
        }   
      boolOutIO = true; 
      prevMilPod = curMil + 100000;      
    }
    }else if(!digitalRead(4)){
      prevMilPod = curMil;     
    }
}

void checkButtonPom(){
  int pinIn = 5;
  int pinOut = 9;
  unsigned long curMil = millis();
  String finStr = "pom";

  if(digitalRead(pinIn) && curMil > prevMilPom){
      if(curMil - prevMilPom >= inter){
        finalString = finStr;
        if(!digitalRead(pinOut)){
          inDataState = "1";
        }else if(digitalRead(pinOut)){
          inDataState = "0";
        }   
      boolOutIO = true;       
     prevMilPom = curMil + 100000; 
    }
    }else if(!digitalRead(4)){
      prevMilPom = curMil;     
    }
}
