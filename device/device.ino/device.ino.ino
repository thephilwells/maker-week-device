/*
Adafruit Arduino - Lesson 6. Inputs
*/

int ledPin = 5;
int buttonApin = 9;
int buttonBpin = 8;
int buttonCpin = 10;
int onOff = 0;

int buttonAState = HIGH;
int buttonBState = HIGH;
int buttonCState = HIGH;

int lastButtonAState = HIGH;
int lastButtonBState = HIGH;
int lastButtonCState = HIGH;

byte leds = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
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

//    
//    if (digitalRead(buttonBpin) == LOW)
//    {
//      digitalWrite(ledPin, LOW);
//      Serial.println("blorp");
//    }
//    
//    if (digitalRead(buttonCpin) == LOW)
//    {
//      Serial.println("ahooga");
//    }
}
