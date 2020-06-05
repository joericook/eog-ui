//pins to read analog input
int potPinX = A0; 
int potPinY = A1;
const int PIEZO_PIN = A2;

//Variables:
int Xvalue;       
int Xmin = 1023;
int Xmax = 0;

int Yvalue;
int Ymin = 1023;
int Ymax = 0;

void setup(){
  Serial.begin (115200);

  pinMode(13, OUTPUT);
  
  pinMode(potPinX, INPUT); 
  pinMode(potPinY, INPUT);

  while (millis() < 10000) {             //Begin calibration period

    digitalWrite(13, HIGH);             //Turn LED on at start of calibration
    
    Xvalue = analogRead(potPinX);
    Yvalue = analogRead(potPinY);

    //Record the new maximum value for X
    if (Xvalue > Xmax) {
      Xmax = Xvalue;
    }

    //Record the new minimum value for X
    if (Xvalue < Xmin) {
      Xmin = Xvalue;
    }
    
    //Record the new maximum value for Y
    if (Yvalue > Ymax) {
      Ymax = Yvalue;
    }

    //Record the new minimum value for Y
    if (Yvalue < Ymin) {
      Ymin = Yvalue;
    }
  }                                     //Calibration ends
  digitalWrite(13, LOW);                //Turn LED off at end of calibration
}

void loop()
{ 
  //Read X-axis value 
  Xvalue = analogRead(potPinX);                     

  //Apply calibration
  Xvalue = map(Xvalue, Xmin, Xmax, 0, 600);

  //If value is outside calibrated range
  Xvalue = constrain(Xvalue, 0, 600);

  //Read Y-axis value
  Yvalue = analogRead(potPinY);
  
  //Apply calibration
  Yvalue = map(Yvalue, Ymin, Ymax, 0, 600);

  //If value is outside calibrated range
  Yvalue = constrain(Yvalue, 0, 600);

  int piezoADC = analogRead(PIEZO_PIN);
  float piezoV = piezoADC / 1023.0 * 5;

  //Print values in Arduino2Max format
  Serial.print(Xvalue);
  Serial.print(" ");
  Serial.print(Yvalue);
  Serial.print(" ");
  Serial.print(piezoV);
  Serial.println();
  delay(5);                          //Small delay
}

