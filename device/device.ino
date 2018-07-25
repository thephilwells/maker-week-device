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
String outerLetterString = "DMRABO";
String wordList[49];

String input[20];
int possibleScore = 0;
int playerScore = 0;
int wordsFound = -1;
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

void setup()
{
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
  Serial.begin(9600);
  calculateTotalPoints();
  submit("TOOT");
  submit("TOTOTO");
  submit("FART");
  submit("TOO");
}

void loop() 
{

}

void calculateTotalPoints()
{
  char buffer[12];
  for (int i=0; i < 49; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&dictionary_table[i]));
//    Serial.println(buffer);
    String buffString = String(buffer);
    if (buffer == pangram)
    {
      possibleScore += buffString.length() + 7;
    }
    else
    {
      if (buffString.length() == 4)
      {
        possibleScore += 1;
      }
      else
      {
        possibleScore += buffString.length();
      }
    }
    delay(20);
  }
//  Serial.println("New possible score: ");
//  Serial.println(possibleScore);
}

void submit(String submission)
{
  // check for word in dictionary
  char buffer[12];
  bool inWordList;
  for (int i=0; i < 49; i++) {
    inWordList = false;
    bool isError = validateSubmission(submission);
    if (isError == true)
    {
      inWordList = true; // otherwise we'll get 'not in word list' alert
      break;
    }
    strcpy_P(buffer, (char*)pgm_read_word(&dictionary_table[i]));
    String buffString = String(buffer);
    if (submission == buffString)
    {
      inWordList = true;
      // add word to list of found words
      wordList[wordsFound++] = submission;
    
      // add word value to player's score
      int wordValue = calculateWordValue(submission);
      playerScore += wordValue;
    
      // set alert
      alert = mapWordValueToMessage(wordValue)+" +" + wordValue + " ("+submission+")";
      // re-draw screen

      break;
    }
  }
  if (inWordList == false)
  {
    alert = submission+" not in word list.";
  }
  Serial.println(alert);
}

bool validateSubmission(String submission)
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
  return false;
}

int calculateWordValue(String submission)
{
  // TODO: return calculated word value
  return 5;
}

String mapWordValueToMessage(int value)
{
  // TODO: map word value to message
  return "Nice!";
}

