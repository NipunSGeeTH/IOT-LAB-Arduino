/*
Name: Sangeeth Kariyapperuma
Index Number:
Task: 8-Key Tone Generator
*/

const int buzzerPin = 8;


const int buttonPins[8] = {2, 3, 4, 5, 6, 7, 9, 10};

const int frequencies[8] = {300, 400, 500, 600, 700, 800, 900, 1000};


bool prevState[8];

unsigned long pressTime = 0;
bool shortToneActive = false;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    prevState[i] = HIGH;
  }
}

void loop() {
  int totalFrequency = 0;
  bool anyPressed = false;


  for (int i = 0; i < 8; i++) {
    bool currState = digitalRead(buttonPins[i]);


    if (prevState[i] == HIGH && currState == LOW) {
      pressTime = millis();
      shortToneActive = true;
    }

    if (currState == LOW) {
      totalFrequency += frequencies[i];
      anyPressed = true;
    }

    prevState[i] = currState;
  }

  if (shortToneActive) {
    if (millis() - pressTime <= 20) {
      if (anyPressed) {
        tone(buzzerPin, totalFrequency);
      }
    } else {
      shortToneActive = false;
    }
  } 
  else {

    if (anyPressed) {
      tone(buzzerPin, totalFrequency);
    } else {
      noTone(buzzerPin);
    }
  }
}