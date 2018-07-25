/*
  SpellingBeeGame.h - Library for portable spelling bee device's game logic
*/

#ifndef SpellingBeeGame_h
#define SpellingBeeGame_h

#include "Arduino.h"

class SpellingBeeGame
{
  public:
    void submit(String);
    void shuffle();
    String wordList[49];
    int possibleScore;
    int playerScore;
    int wordsFound;
    String alert;
    String outerLetters[7];
    String centerLetter;
    String northwestLetter;
    String northeastLetter;
    String eastLetter;
    String southeastLetter;
    String southwestLetter;
    String westLetter;
  private:
    bool _validateSubmission(String);
    int _calculateWordValue(String);
    String _mapWordValueToMessage(int);
};

#endif
