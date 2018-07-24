int buttonApin = 9;
int buttonBpin = 8;
int buttonCpin = 10;

int buttonAState = HIGH;
int buttonBState = HIGH;
int buttonCState = HIGH;

int lastButtonAState = HIGH;
int lastButtonBState = HIGH;
int lastButtonCState = HIGH;

char outerLetters[7] = "DMRABO";
char centerLetter[2] = "T";
char allLetters[8]   = "DMRABOT";

void setup() 
{
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() 
{
  buttonAState = digitalRead(buttonApin);
  buttonBState = digitalRead(buttonBpin);
  buttonCState = digitalRead(buttonCpin);
    if (buttonAState != lastButtonAState)
    {
      Serial.println("Pressed Button A");
      lastButtonAState = buttonAState;
      delay(50);
    }

    if (buttonBState != lastButtonBState)
    {
      Serial.println("Pressed Button B");
      lastButtonBState = buttonBState;
      delay(50);
    }

    if (buttonCState != lastButtonCState)
    {
      Serial.println("Pressed Button C");
      lastButtonCState = buttonCState;
      delay(50);
    }
}