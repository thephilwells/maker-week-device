String outerLetters[7] = {"O","M","A","D","B","R"};
String outerLetterString = "OMADBR";
String wordList[49];

int possibleScore = 188;
int playerScore = 0;
int wordsFound = 0;
String alert;

String centerLetter = "T";
String northwestLetter = outerLetters[0];
String northeastLetter = outerLetters[1];
String eastLetter = outerLetters[2];
String southeastLetter = outerLetters[3];
String southwestLetter = outerLetters[4];
String westLetter = outerLetters[5];

const char string_0[] PROGMEM = "ABBOT";
const char string_1[] PROGMEM = "ABORT";
const char string_2[] PROGMEM = "AORTA";
const char string_3[] PROGMEM = "ATOM";
const char string_4[] PROGMEM = "ATTAR";
const char string_5[] PROGMEM = "BOAT";
const char string_6[] PROGMEM = "BOOT";
const char string_7[] PROGMEM = "BOTTOM";
const char string_8[] PROGMEM = "BRAT";
const char string_9[] PROGMEM = "DART";
const char string_10[] PROGMEM = "DARTBOARD";
const char string_11[] PROGMEM = "DATA";
const char string_12[] PROGMEM = "DOORMAT";
const char string_13[] PROGMEM = "DOTARD";
const char string_14[] PROGMEM = "DRAT";
const char string_15[] PROGMEM = "MARMOT";
const char string_16[] PROGMEM = "MART";
const char string_17[] PROGMEM = "MATADOR";
const char string_18[] PROGMEM = "MOAT";
const char string_19[] PROGMEM = "MOOT";
const char string_20[] PROGMEM = "MORTAR";
const char string_21[] PROGMEM = "MOTOR";
const char string_22[] PROGMEM = "MOTORBOAT";
const char string_23[] PROGMEM = "MOTTO";
const char string_24[] PROGMEM = "ORATOR";
const char string_25[] PROGMEM = "RATATAT";
const char string_26[] PROGMEM = "ROBOT";
const char string_27[] PROGMEM = "ROOT";
const char string_28[] PROGMEM = "ROTATOR";
const char string_29[] PROGMEM = "ROTO";
const char string_30[] PROGMEM = "ROTOR";
const char string_31[] PROGMEM = "TABARD";
const char string_32[] PROGMEM = "TABOO";
const char string_33[] PROGMEM = "TABOR";
const char string_34[] PROGMEM = "TARO";
const char string_35[] PROGMEM = "TAROT";
const char string_36[] PROGMEM = "TART";
const char string_37[] PROGMEM = "TARTAR";
const char string_38[] PROGMEM = "TATTOO";
const char string_39[] PROGMEM = "TOAD";
const char string_40[] PROGMEM = "TOMATO";
const char string_41[] PROGMEM = "TOMB";
const char string_42[] PROGMEM = "TOOT";
const char string_43[] PROGMEM = "TORO";
const char string_44[] PROGMEM = "TORT";
const char string_45[] PROGMEM = "TRAM";
const char string_46[] PROGMEM = "TROD";
const char string_47[] PROGMEM = "TROT";
const char string_48[] PROGMEM = "MORTARBOARD";

const static char* const dictionary_table[] PROGMEM = {string_0,string_1,string_2,string_3,string_4,string_5,string_6,string_7,string_8,string_9,string_10,string_11,string_12,string_13,string_14,string_15,string_16,string_17,string_18,string_19,string_20,string_21,string_22,string_23,string_24,string_25,string_26,string_27,string_28,string_29,string_30,string_31,string_32,string_33,string_34,string_35,string_36,string_37,string_38,string_39,string_40,string_41,string_42,string_43,string_44,string_45,string_46,string_47,string_48};

char pangram[12] = "MORTARBOARD";

class Button
{
  int pin;                         // Arduino address
  unsigned long previousPress;    // last time button was pressed
  int state;                       // stores current pin state
  int debounce_threshold;              // how long to wait between debounces

  public:
  // constructor
  // call once in setup()
  Button(int pinInput)
  {
    // initialize variables
    pin = pinInput;
    previousPress = millis(); // records time of last known button press
    state = HIGH;
    debounce_threshold = 200;

    // initialize hardware
    pinMode(pin, INPUT_PULLUP);
  }

  // call this frequently, in loop()
  // updates the button variables 
  // returns true if a new button-press should be registered
  bool Update()
  {
    bool returnPress = false;
    int currentState = digitalRead(pin);

    bool buttonHasBeenPressed = (currentState != state);
    int timeSinceLastPress = (millis() - previousPress);
    bool debounceThresholdHasBeenPassed = (timeSinceLastPress > debounce_threshold);
    
    if (buttonHasBeenPressed && debounceThresholdHasBeenPassed)
    {
      returnPress = (currentState == LOW);
      state = currentState;
    }

    if (returnPress){
      previousPress = millis();
      return true;
    } else {
      return false;
    }
  }

};

// set up control buttons
Button btnSubmit(12);
//Button btnShuffle(8);
//Button btnDelete(9);
//Button btnReset(10)

// set up hex buttons
int hexButtonCount = 3;
Button btnsHex[3] = {3, 4, 5};
Button centerHex(6);

// set up logic variables
String currentWord = "";


void setup()
{
  Serial.begin(9600);
  Serial.println("Outer letters: "+outerLetters[0]+outerLetters[1]+outerLetters[2]);
  Serial.println("Center letter: "+centerLetter);
}

void loop()
{
  // check hex button presses
  for (int i = 0; i < hexButtonCount; i++){
    bool pressed = btnsHex[i].Update();
    if (pressed){
      currentWord += outerLetters[i];
      Serial.println(currentWord);
    }
  }

  bool centerPressed = centerHex.Update();
  if (centerPressed)
  {
    currentWord += centerLetter;
    Serial.println(currentWord);
  }

  bool pressed = btnSubmit.Update();
  if (pressed){
    submit(currentWord);
    currentWord = "";
  }
}

void submit(String submission)
{
  // check for word in dictionary
  char buffer[12];
  bool inDictionary;
  bool isError = _validateSubmission(submission);
  if (isError == true)
  {
    inDictionary = true; // otherwise we'll get 'not in word list' alert
  }
  else
  {
    for (int i=0; i < 49; i++) {
      inDictionary = false;
  
      strcpy_P(buffer, (char*)pgm_read_word(&dictionary_table[i]));
      String buffString = String(buffer);
      if (submission == buffString)
      {
        inDictionary = true;
        // add word to list of found words
        wordList[wordsFound++] = submission;
      
        // add word value to player's score
        int wordValue = _calculateWordValue(submission);
        playerScore += wordValue;
      
        // set alert
        if (submission == String(pangram))
        {
          alert = "PANGRAM! +" + String(wordValue) + " ("+submission+")";
        }
        else
        {
          alert = _mapWordValueToMessage(wordValue)+" +" + wordValue + " ("+submission+")";
        }
        // re-draw screen
  
        break;
      }
    }
  }
  if (inDictionary == false)
  {
    alert = submission+" not in word list.";
  }
  Serial.println(alert);
}

bool _validateSubmission(String submission)
{
  /// too short
  if (submission.length()<4)
  {
    alert = "Too short! ("+submission+")";
    return true;
  }

  /// bad letters
  for (int i=0; i < submission.length(); i++)
  {
    String letter = String(submission.charAt(i));
    if (outerLetterString.indexOf(String(letter)) == -1)
    {
      if (letter != centerLetter)
      {
        alert = "Bad letters! ("+submission+")";
        return true;
      }
    }
  }

  /// missing center letter
  bool hasCenterLetter = false;
  for (int j=0; j < submission.length(); j++)
  {
    String letter = String(submission.charAt(j));
    if (letter == centerLetter)
    {
      hasCenterLetter = true;
      break;
    }
  }
  if (hasCenterLetter == false)
  {
    alert = "Missing key letter! ("+submission+")";
    return true;
  }

  // already found
  for (int k=0; k < 49; k++)
  {
    if (submission == wordList[k])
    {
      alert = "Already found! ("+submission+")";
      return true;
    }
  }
  
  return false;
}

int _calculateWordValue(String submission)
{
  if (submission == String(pangram))
  {
    return String(pangram).length() + 7;
  }
  if (submission.length() == 4)
  {
    return 1;
  }
  return submission.length();
}

String _mapWordValueToMessage(int value)
{
  if (value <= 4)
  {
    return "Good!";
  }
  if (value > 4 && value <=6)
  {
    return "Nice!";
  }
  return "Awesome!";
}

void shuffle()
{
  Serial.println("Before shuffle: "+outerLetterString);
  for (int i=0; i < 6; i++)
  {
    int n = random(0, 6);
    String temp = outerLetters[n];
    outerLetters[n] = outerLetters[i];
    outerLetters[i] = temp;
  }
  northwestLetter = outerLetters[0];
  northeastLetter = outerLetters[1];
  eastLetter = outerLetters[2];
  southeastLetter = outerLetters[3];
  southwestLetter = outerLetters[4];
  westLetter = outerLetters[5];
  outerLetterString = outerLetters[0] + outerLetters[1] + outerLetters[2] + outerLetters[3] + outerLetters[4] + outerLetters[5] + outerLetters[6];
  Serial.println("After shuffle: "+outerLetterString);
}

