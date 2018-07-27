#include <epd2in7.h>
#include <fonts.h>
#include <epdpaint.h>
#include <epdif.h>
#include <SPI.h>

#define COLORED     0
#define UNCOLORED   1

//String outerLetters[7] = {"O","M","A","D","B","R"};
char outerLetterString[7] = "OMADBR";
String wordList[49];

int possibleScore = 188;
int playerScore = 0;
int wordsFound = 0;
char alertX[50] = "BEE impressed!\0";

char centerLetter[2] = "T";
char northwestLetter =  outerLetterString[0];
char northLetter = outerLetterString[1];
char northeastLetter = outerLetterString[2];
char southeastLetter = outerLetterString[3];
char southLetter = outerLetterString[4];
char southwestLetter = outerLetterString[5];

// set up logic variables
char currentWord[50];
int currentWordIndex = 0;


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

const static char* const dictionary_table[] PROGMEM = {string_0,string_1,string_2,string_3,string_4,string_5,string_6,string_7,string_8,string_9,string_10,string_11,string_12,string_13,string_14,string_15,string_16,string_17,string_18,string_19,string_20,string_21,string_22,string_23,string_24,string_25,string_26,string_27,string_28,string_29,string_30,string_31,string_32,string_33,string_34,string_35,string_36,string_37,string_38,string_39,string_40,string_41,string_42,string_43,string_44,string_45,string_46,string_47,string_48, "\0"};

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
Button btnShuffle(5);
Button btnDelete(4);

// set up hex buttons
int hexButtonCount = 1;
Button btnsHex[1] = {3};
Button centerHex(6);

Epd epd;

void setup()
{
  Serial.begin(9600);
  Serial.println(outerLetterString);
  Serial.println(centerLetter[0]);
  
  if (epd.Init() != 0) {
    Serial.print("e-Paper init failed");
    return;
  }

  redraw(outerLetterString);
}

void loop()
{
  // check hex button presses
  for (int i = 0; i < hexButtonCount; i++){
    bool pressed = btnsHex[i].Update();
    if (pressed){
//      currentWord += outerLetterString[i];
      currentWord[currentWordIndex] = outerLetterString[i];
      currentWordIndex++;
      Serial.println(currentWord);
      redraw(outerLetterString);
    }
  }

  bool centerPressed = centerHex.Update();
  if (centerPressed)
  {
    currentWord[currentWordIndex] = centerLetter[0];
    currentWordIndex++;
    Serial.println(currentWord);
    redraw(outerLetterString);
  }

  bool deletePressed = btnDelete.Update();
  if (deletePressed)
  {
    if (currentWord[0] == NULL)
    {
      // do nothing
      Serial.println(currentWord);
    }
    else
    {
      currentWord[currentWordIndex] = NULL;
      currentWordIndex--;
      Serial.println(currentWord);
      redraw(outerLetterString);
    }
  }

  bool shufflePressed = btnShuffle.Update();
  if (shufflePressed)
  {
    Serial.println("Shuffling..");
    shuffle();
    Serial.println("Outer letters: "+String(outerLetterString[0])+String(outerLetterString[1])+String(outerLetterString[2]));
    Serial.println("Center letter: "+centerLetter[0]);
  }

  bool pressed = btnSubmit.Update();
  if (pressed){
    submit(currentWord);
    memset(currentWord, 0, sizeof(currentWord));
//    currentWord = "";
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
  
      strcpy_P(buffer, (char*)pgm_read_word(&(dictionary_table[i])));
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
          String tmp = "PANGRAM! +" + String(wordValue) + " ("+submission+")\0";
          tmp.toCharArray(alertX, 50);
        }
        else
        {
          String alert = _mapWordValueToMessage(wordValue)+" +" + wordValue + " ("+submission+")\0";
          alert.toCharArray(alertX, 50);
        }
        // re-draw screen
  
        break;
      }
    }
  }
  if (inDictionary == false)
  {
    String alert = submission+" not in word list.\0";
    alert.toCharArray(alertX, 50);
  }
  redraw(outerLetterString);
}

bool _validateSubmission(String submission)
{
  /// too short
  if (submission.length()<4)
  {
    String alert = "Too short! ("+submission+")\0";
    alert.toCharArray(alertX, 50);
    return true;
  }

  /// bad letters
  for (int i=0; i < submission.length(); i++)
  {
    char letter = submission.charAt(i);
    if (strstr(outerLetterString, letter) == NULL)
    {
      if (letter != centerLetter)
      {
        String alert = "Bad letters! ("+submission+")\0";
        alert.toCharArray(alertX, 50);
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
    String alert = "Missing key letter! ("+submission+")\0";
    alert.toCharArray(alertX, 50);
    return true;
  }

  // already found
  for (int k=0; k < 49; k++)
  {
    if (submission == wordList[k])
    {
      String alert = "Already found! ("+submission+")\0";
      alert.toCharArray(alertX, 50);
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
  for (int i=0; i < 6; i++)
  {
    int n = random(0, 6);
//    String temp = String(outerLetterString[n]);
//    String(outerLetterString[n]) = String(outerLetterString[i]);
//    String(outerLetterString[i]) = temp;
  }
  northwestLetter = outerLetterString[0];
  northLetter = outerLetterString[1];
  northeastLetter = outerLetterString[2];
  southeastLetter = outerLetterString[3];
  southLetter = outerLetterString[4];
  southwestLetter = outerLetterString[5];
}

char* str2char(String s)
{
  int n = s.length();
  char char_array[n+1];
  strcpy(char_array, s.c_str());
  return char_array;
}

void redraw(char* OLS)
{
    unsigned char image[1024];
    epd.ClearFrame();
  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */
  
  Paint paint(image, 32, 176);    //width should be the multiple of 8 
  
  paint.SetRotate(ROTATE_90);
  
  // northwest letter
  paint.Clear(UNCOLORED);
  OLS[0] = outerLetterString[0];
  OLS[1] = outerLetterString[1];
  OLS[2] = outerLetterString[2];
  OLS[3] = outerLetterString[3];
  OLS[4] = outerLetterString[4];
  OLS[5] = outerLetterString[5];
  char quack = northwestLetter;
  paint.DrawCharAt(0, 0, quack, &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 96, 32, paint.GetWidth(), paint.GetHeight());

  // center letter
  paint.Clear(UNCOLORED);
  paint.DrawCharAt(0, 0, centerLetter[0], &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 80, 60, paint.GetWidth(), paint.GetHeight());
  
  // north letter
  paint.Clear(UNCOLORED);
  paint.DrawCharAt(0, 0, northLetter, &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 115, 60, paint.GetWidth(), paint.GetHeight());

  // northeast letter
  paint.Clear(UNCOLORED);
  paint.DrawCharAt(0, 0, northeastLetter, &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 96, 88, paint.GetWidth(), paint.GetHeight());

  // southwest letter
  paint.Clear(UNCOLORED);
  paint.DrawCharAt(0, 0, southwestLetter, &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 65, 32, paint.GetWidth(), paint.GetHeight());

  // southeast letter
  paint.Clear(UNCOLORED);
  paint.DrawCharAt(0, 0, southeastLetter, &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 65, 88, paint.GetWidth(), paint.GetHeight());

  // south letter
  paint.Clear(UNCOLORED);
  paint.DrawCharAt(0, 0, southLetter, &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 50, 60, paint.GetWidth(), paint.GetHeight());

  // score
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(9, 0, "0 / 188", &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 119, 120, paint.GetWidth(), paint.GetHeight());

  // input
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(9, 0, currentWord, &Font16, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 65, 120, paint.GetWidth(), paint.GetHeight());

  // alert
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 6, alertX, &Font12, COLORED);
  epd.TransmitPartialData(paint.GetImage(), 10, 60, paint.GetWidth(), paint.GetHeight());

  /* This displays the data from the SRAM in e-Paper module */
  epd.DisplayFrame();
  Serial.println("Ready..");

  /* Deep sleep */
//  epd.Sleep();
}

