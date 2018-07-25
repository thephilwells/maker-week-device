#include <SpellingBeeGame.h>

SpellingBeeGame game;

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
Button btnSubmit(4);
//Button btnShuffle(8);
//Button btnDelete(9);
//Button btnReset(10)

// set up hex buttons
int hexButtonCount = 2;
Button btnsHex[2] = {5,6};

// set up logic variables
String currentWord = "";


void setup()
{
  Serial.begin(9600);
  game.submit("TOOT");
}

void loop()
{
  // check hex button presses
  for (int i = 0; i < hexButtonCount; i++){
    bool pressed = btnsHex[i].Update();
    if (pressed){
      currentWord += i;
      Serial.println(currentWord);
    }
  }

  bool pressed = btnSubmit.Update();
  if (pressed){
    Serial.println("submit");
  }
}

