int buttonApin = 9;
int buttonBpin = 8;
int buttonCpin = 10;

int buttonAState = HIGH;
int buttonBState = HIGH;
int buttonCState = HIGH;

int lastButtonAState = HIGH;
int lastButtonBState = HIGH;
int lastButtonCState = HIGH;

String outerLetters[7] = {"D","M","R","A","B","O"};

String input[20];
int possibleScore = 0;

String centerLetter = "T";
String northwestLetter = outerLetters[0];
String northeastLetter = outerLetters[1];
String eastLetter = outerLetters[2];
String southeastLetter = outerLetters[3];
String southwestLetter = outerLetters[4];
String westLetter = outerLetters[5];

const String dictionary[49] = {"ABBOT","ABORT","AORTA","ATOM","ATTAR","BOAT","BOOT","BOTTOM","BRAT","DART","DARTBOARD","DATA","DOORMAT","DOTARD","DRAT","MARMOT","MART","MATADOR","MOAT","MOOT","MORTAR","MOTOR","MOTORBOAT", "MORTARBOARD", "MOTTO","ORATOR","RATATAT","ROBOT","ROOT","ROTATOR","ROTO","ROTOR","TABARD","TABOO","TABOR","TARO","TAROT","TART","TARTAR","TATTOO","TOAD","TOMATO","TOMB","TOOT","TORO","TORT","TRAM","TROD","TROT"};
String pangram = "MOTORBOAT";

void setup()
{
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
  Serial.begin(9600);
  calculateTotalPoints();
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

void calculateTotalPoints()
{
  for (int i=0; i < 49; i++) {
    String word = dictionary[i];
    if (word == pangram)
    {
      possibleScore += word.length() + 7;
      Serial.println("Added "+pangram+". New possible score: "+possibleScore);
    }
    else
    {
      if (word.length() == 4)
      {
        possibleScore += 1;
      }
      else
      {
        possibleScore += word.length();
      }
      Serial.println("Added "+word+". New possible score: "+possibleScore);
    }
  }
}

