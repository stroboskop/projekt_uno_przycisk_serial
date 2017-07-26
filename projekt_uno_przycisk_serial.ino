
unsigned long prevMil = 0;
const long inter = 3000;

boolean stateOfInp = false;
boolean prevPom = false;
boolean prevPod = false;
boolean boolOutIO = false;
boolean valIn = false;

boolean pinPod = false;
boolean pinPom = false;

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
}

void loop() {
  checkButtonsNew();
  readSerial();
  
  if(boolOutIO)
    outputIO(finalString, inDataState);
}


void readSerial(){
  if(Serial.available() >0){   
      char inChar = Serial.read();   

      if(inChar == '\n' && valIn == true){       
        inData.trim();
        finalString = String(inData[0]) + String(inData[1]) + String(inData[2]);
        inDataState = inData[4];
        inData = "";
        boolOutIO = true;
        valIn = false;   
      }      
          
      if(inChar != '\n' && inChar != '\r' && valIn == true)
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
    Serial.println(finalString + "=" + val);
    finalString = "";
    boolOutIO = false;
    }

    if(loc == "pom"){
    digitalWrite(pom, val);  
    Serial.println(finalString + "=" + val);
    finalString = "";
    boolOutIO = false;
    }
}


void checkButtonsNew(){
  unsigned long curMil = millis();
  if(curMil - prevMil >= inter){
    if(digitalRead(5) || digitalRead(4)){
      stateOfInp = true;   
    }
    prevMil = curMil;
  }
  
  if(digitalRead(4) && stateOfInp == true){
      if(prevPod == false){
          finalString = "pod";
          inDataState = "1";
          boolOutIO = true;
          prevPod = true;
          Serial.println("false ");
      }else if(prevPod == true){
          finalString = "pod";
          inDataState = "0";
          boolOutIO = true;
          prevPod = false;
          Serial.println("true ");
      }
    Serial.println("i jestesmy ");
    stateOfInp = false;
  }
  if(digitalRead(5) && stateOfInp == true){

    //outputIO("pom", readPin);
    Serial.println("i jestesmy");
    stateOfInp = false;
  }
}


