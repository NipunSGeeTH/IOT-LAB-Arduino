/*
Name: K.M.N.Sangeeth Kariyapperuma
Index Number: 230317J
Task: 8-Key Tone Generator + 7-Segment Display
*/

const int buzzerPin = 8;


const int buttonPins[8] = {2, 3, 4, 5, 6, 7, 9, 10};


const int frequencies[8] = {300, 400, 500, 600, 700, 800, 900, 1000};


const int segPins[7] = {11, 12, 13, A0, A1, A2, A3};


const byte digits[9][7] = {
  {0,0,0,0,0,0,0}, // 0 
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}  // 8
};

unsigned long lastSwitch = 0;
int displayIndex = 0;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}

void loop() {
  int totalFreq = 0;

  int pressedKeys[8];
  int count = 0;


  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      totalFreq += frequencies[i];
      pressedKeys[count++] = i + 1; 
    }
  }


  if (count > 0) {
    tone(buzzerPin, totalFreq);
  } else {
    noTone(buzzerPin);
  }

  if (count == 1) {
    displayDigit(pressedKeys[0]);
  } 
  else if (count > 1) {
    if (millis() - lastSwitch >= 500) {
      lastSwitch = millis();
      displayIndex++;
      if (displayIndex >= count) displayIndex = 0;
    }
    displayDigit(pressedKeys[displayIndex]);
  } 
  else {
  
    for (int i = 0; i < 7; i++) {
      digitalWrite(segPins[i], LOW);
    }
  }
}