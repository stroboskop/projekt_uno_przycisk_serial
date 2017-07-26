boolean stateOfInp = false;
unsigned long prevMil = 0;
const long inter = 50;
bool prevPom = false;
bool prevOsw = false;
bool podworko = false;

String inData = "";
String finalString = "";
String inDataState = "";

void setup() {
  Serial.begin(115200);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(8, OUTPUT);

}

void loop() {
  checkButtons();
  readSerial();
  outputIO();
}

void outputIO(){
  if(finalString == "pod" && inDataState == "1"){
    podworko = true;
  }
  if(finalString == "pod" && inDataState == "0"){
    podworko = false;
  }

  if(podworko == true){
    digitalWrite(8, HIGH);
  }
  if(podworko == false){
    digitalWrite(8, LOW);
  }
}


void readSerial(){
  if(Serial.available() >0){   
      char inChar = Serial.read();   

      if(inChar == '\n'){
        //Serial.println("i mamy stringa:  " + inData);
        inData.trim();
        finalString = String(inData[6]) + String(inData[7]) + String(inData[8]);
        inDataState = inData[10];
        //Serial.println("nasz final: " + finalString);
        //Serial.println("nasz stan: " + inDataState);
        inData = "";
         
      }     
      if(inChar != '\n' && inChar != '\r')
        inData += inChar; 
}
}

void checkButtons(){
  unsigned long curMil = millis();
  if(curMil - prevMil >= inter){
    if(prevPom != digitalRead(5) || prevOsw != digitalRead(4)){
      stateOfInp = true;   
    }
    prevMil = curMil;
  }
  
  if(digitalRead(4) != prevOsw && stateOfInp == true){
    Serial.println("pod," + String(digitalRead(4)));
    prevOsw = digitalRead(4);
    stateOfInp = false;
  }
  if(digitalRead(5) != prevPom && stateOfInp == true){
    Serial.println("pom," + String(digitalRead(5)));
    prevPom = digitalRead(5);
    stateOfInp = false;
  }
}

