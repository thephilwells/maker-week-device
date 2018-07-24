int buttonApin = 9;
int buttonBpin = 8;
int buttonCpin = 10;

int buttonAState = HIGH;
int buttonBState = HIGH;
int buttonCState = HIGH;

int lastButtonAState = HIGH;
int lastButtonBState = HIGH;
int lastButtonCState = HIGH;

char allLetters[8]   = "TDMRABO";

String dictionary[48] = {"ABBOT","ABORT","AORTA","ATOM","ATTAR","BOAT","BOOT","BOTTOM","BRAT","DART","DARTBOARD","DATA","DOORMAT","DOTARD","DRAT","MARMOT","MART","MATADOR","MOAT","MOOT","MORTAR","MOTOR","MOTORBOAT","MOTTO","ORATOR","RATATAT","ROBOT","ROOT","ROTATOR","ROTO","ROTOR","TABARD","TABOO","TABOR","TARO","TAROT","TART","TARTAR","TATTOO","TOAD","TOMATO","TOMB","TOOT","TORO","TORT","TRAM","TROD","TROT"};

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
